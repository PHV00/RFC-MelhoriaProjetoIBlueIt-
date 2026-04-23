#pragma once

#include <stdbool.h>

#include "app/app_types.h"
#include "sensing/sample_buffer.h"

bool signal_quality_evaluate(const sample_buffer_t *buffer, signal_quality_t *out_quality);