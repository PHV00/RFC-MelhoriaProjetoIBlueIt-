#pragma once

#include <stdbool.h>

#include "drivers/max3010x_driver.h"
#include "sensing/sample_buffer.h"

typedef struct {
    max3010x_t *sensor;
    sample_buffer_t *buffer;
    uint32_t seq;
} ppg_sampler_t;

void ppg_sampler_init(ppg_sampler_t *sampler, max3010x_t *sensor, sample_buffer_t *buffer);
bool ppg_sampler_step(ppg_sampler_t *sampler);