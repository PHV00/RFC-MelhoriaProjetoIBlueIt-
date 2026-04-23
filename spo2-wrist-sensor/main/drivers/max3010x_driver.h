#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "esp_err.h"
#include "app/app_types.h"

typedef struct {
    uint8_t i2c_addr;
    bool initialized;
} max3010x_t;

esp_err_t max3010x_init(max3010x_t *dev, uint8_t i2c_addr);
esp_err_t max3010x_reset(max3010x_t *dev);
esp_err_t max3010x_config_default(max3010x_t *dev);
esp_err_t max3010x_read_sample(max3010x_t *dev, ppg_sample_t *sample);