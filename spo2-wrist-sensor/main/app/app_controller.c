#include "app/app_controller.h"

#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c.h"

#include "app/app_state_machine.h"
#include "drivers/i2c_bus.h"
#include "drivers/max3010x_driver.h"
#include "processing/hr_estimator.h"
#include "processing/signal_quality.h"
#include "processing/spo2_estimator.h"
#include "safety/confidence_engine.h"
#include "sensing/ppg_sampler.h"
#include "sensing/sample_buffer.h"
#include "storage/config_repo.h"
#include "transport/serial_telemetry.h"

static const char *TAG = "APP";

static void i2c_scan(void);

static max3010x_t g_sensor;
static sample_buffer_t g_buffer;
static ppg_sampler_t g_sampler;
static uint32_t g_step_counter = 0;

void app_controller_init(void) {
    const system_config_t *cfg = config_repo_get();

    app_state_machine_set(APP_STATE_BOOT);
    ESP_LOGI(TAG, "Inicializando sistema...");

    ESP_ERROR_CHECK(i2c_bus_init(cfg->i2c_sda_gpio, cfg->i2c_scl_gpio, cfg->i2c_freq_hz));
    ESP_ERROR_CHECK(max3010x_init(&g_sensor, cfg->sensor_i2c_addr));

    ESP_ERROR_CHECK(max3010x_reset(&g_sensor));
    ESP_ERROR_CHECK(max3010x_config_default(&g_sensor));

    i2c_scan();

    sample_buffer_init(&g_buffer);
    ppg_sampler_init(&g_sampler, &g_sensor, &g_buffer);

    app_state_machine_set(APP_STATE_IDLE);
    ESP_LOGI(TAG, "Sistema inicializado.");
}

void app_controller_step(void) {
     ppg_sample_t latest = {0};

    if (!ppg_sampler_step(&g_sampler)) {
        app_state_machine_set(APP_STATE_ERROR);
        serial_telemetry_print_message("APP", "Falha em ppg_sampler_step");
        return;
    }

    if (sample_buffer_latest(&g_buffer, &latest)) {
        serial_telemetry_print_sample(&latest);
    }
    app_state_machine_set(APP_STATE_IDLE);
}

static void i2c_scan(void) {
    for (uint8_t addr = 1; addr < 127; addr++) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);

        esp_err_t err = i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(100));
        i2c_cmd_link_delete(cmd);

        if (err == ESP_OK) {
            ESP_LOGI("I2C_SCAN", "Dispositivo encontrado em 0x%02X", addr);
        }
    }
}