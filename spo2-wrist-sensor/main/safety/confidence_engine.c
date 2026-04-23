#include "safety/confidence_engine.h"

bool confidence_engine_build_frame(
    const signal_quality_t *quality,
    const hr_result_t *hr,
    const spo2_result_t *spo2,
    health_frame_t *out_frame
) {
    if (quality == NULL || hr == NULL || spo2 == NULL || out_frame == NULL) {
        return false;
    }

    out_frame->finger_present = quality->signal_present;
    out_frame->confidence = quality->quality_score;
    out_frame->quality = *quality;
    out_frame->hr = *hr;
    out_frame->spo2 = *spo2;

    out_frame->valid =
        quality->signal_present &&
        (quality->quality_score >= 0.35f);

    return true;
}