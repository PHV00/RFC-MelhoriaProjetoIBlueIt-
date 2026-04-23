#include "drivers/max3010x_driver.h"

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "drivers/i2c_bus.h"

#define REG_INTR_STATUS_1     0x00
#define REG_INTR_STATUS_2     0x01
#define REG_INTR_ENABLE_1     0x02
#define REG_INTR_ENABLE_2     0x03
#define REG_FIFO_WR_PTR       0x04
#define REG_OVF_COUNTER       0x05
#define REG_FIFO_RD_PTR       0x06
#define REG_FIFO_DATA         0x07
#define REG_FIFO_CONFIG       0x08
#define REG_MODE_CONFIG       0x09
#define REG_SPO2_CONFIG       0x0A
#define REG_LED1_PA           0x0C
#define REG_LED2_PA           0x0D
#define REG_PART_ID           0xFF

#define MODE_RESET_BIT        0x40
#define MODE_SPO2_EN          0x03

static esp_err_t write_reg(max3010x_t *dev, uint8_t reg, uint8_t value) {
    return i2c_bus_write(dev->i2c_addr, reg, &value, 1);
}

static esp_err_t read_reg(max3010x_t *dev, uint8_t reg, uint8_t *value) {
    return i2c_bus_read(dev->i2c_addr, reg, value, 1);
}

esp_err_t max3010x_init(max3010x_t *dev, uint8_t i2c_addr) {
    if (dev == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    memset(dev, 0, sizeof(*dev));
    dev->i2c_addr = i2c_addr;
    dev->initialized = true;

    return ESP_OK;
}

esp_err_t max3010x_reset(max3010x_t *dev) {
    if (dev == NULL || !dev->initialized) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t err = write_reg(dev, REG_MODE_CONFIG, MODE_RESET_BIT);
    if (err != ESP_OK) {
        return err;
    }

    vTaskDelay(pdMS_TO_TICKS(20));
    return ESP_OK;
}

esp_err_t max3010x_config_default(max3010x_t *dev) {
    if (dev == NULL || !dev->initialized) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t err;

    err = write_reg(dev, REG_INTR_ENABLE_1, 0x00);
    if (err != ESP_OK) return err;

    err = write_reg(dev, REG_INTR_ENABLE_2, 0x00);
    if (err != ESP_OK) return err;

    err = write_reg(dev, REG_FIFO_WR_PTR, 0x00);
    if (err != ESP_OK) return err;

    err = write_reg(dev, REG_OVF_COUNTER, 0x00);
    if (err != ESP_OK) return err;

    err = write_reg(dev, REG_FIFO_RD_PTR, 0x00);
    if (err != ESP_OK) return err;

    err = write_reg(dev, REG_FIFO_CONFIG, 0x0F);
    if (err != ESP_OK) return err;

    err = write_reg(dev, REG_MODE_CONFIG, MODE_SPO2_EN);
    if (err != ESP_OK) return err;

    err = write_reg(dev, REG_SPO2_CONFIG, 0x27);
    if (err != ESP_OK) return err;

    err = write_reg(dev, REG_LED1_PA, 0x24);
    if (err != ESP_OK) return err;

    err = write_reg(dev, REG_LED2_PA, 0x24);
    if (err != ESP_OK) return err;

    return ESP_OK;
}

esp_err_t max3010x_read_sample(max3010x_t *dev, ppg_sample_t *sample) {
    if (dev == NULL || sample == NULL || !dev->initialized) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t raw[6] = {0};
    esp_err_t err = i2c_bus_read(dev->i2c_addr, REG_FIFO_DATA, raw, sizeof(raw));
    if (err != ESP_OK) {
        return err;
    }

    uint32_t red = ((uint32_t)raw[0] << 16) | ((uint32_t)raw[1] << 8) | raw[2];
    uint32_t ir  = ((uint32_t)raw[3] << 16) | ((uint32_t)raw[4] << 8) | raw[5];

    sample->red = red & 0x3FFFF;
    sample->ir = ir & 0x3FFFF;

    return ESP_OK;
}
