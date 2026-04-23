#pragma once

#include "app/app_types.h"

bool confidence_engine_build_frame(
    const signal_quality_t *quality,
    const hr_result_t *hr,
    const spo2_result_t *spo2,
    health_frame_t *out_frame
);