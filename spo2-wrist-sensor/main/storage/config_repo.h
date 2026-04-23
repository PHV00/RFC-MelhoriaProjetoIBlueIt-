#pragma once

#include <stdint.h>

typedef struct {
    uint8_t sensor_i2c_addr;
    int i2c_sda_gpio;
    int i2c_scl_gpio;
    uint32_t i2c_freq_hz;
    uint32_t sample_interval_ms;
} system_config_t;

const system_config_t *config_repo_get(void);