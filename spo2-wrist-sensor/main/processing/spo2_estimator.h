#pragma once

#include <stdbool.h>

#include "app/app_types.h"
#include "sensing/sample_buffer.h"

bool spo2_estimator_compute(const sample_buffer_t *buffer, const signal_quality_t *quality, spo2_result_t *out_spo2);