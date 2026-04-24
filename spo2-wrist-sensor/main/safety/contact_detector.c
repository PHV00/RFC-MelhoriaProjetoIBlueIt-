#include "safety/contact_detector.h"

#include <math.h>

void contact_detector_init(contact_detector_t *det, uint32_t stable_required_ms) {
    if (det == NULL) {
        return;
    }

    det->ir_dc = 0.0f;
    det->red_dc = 0.0f;
    det->ir_dev = 0.0f;
    det->red_dev = 0.0f;

    det->stable_start_ms = 0;
    det->stable_required_ms = stable_required_ms;

    det->stable_window_open = false;
    det->present = false;
}

bool contact_detector_update(
    contact_detector_t *det,
    uint32_t timestamp_ms,
    uint32_t ir_raw,
    uint32_t red_raw
) {
    if (det == NULL) {
        return false;
    }

    const float irf = (float)ir_raw;
    const float redf = (float)red_raw;

    det->ir_dc += CONTACT_ALPHA_DC * (irf - det->ir_dc);
    det->red_dc += CONTACT_ALPHA_DC * (redf - det->red_dc);

    const float ir_abs_dev = fabsf(irf - det->ir_dc);
    const float red_abs_dev = fabsf(redf - det->red_dc);

    det->ir_dev += CONTACT_ALPHA_DEV * (ir_abs_dev - det->ir_dev);
    det->red_dev += CONTACT_ALPHA_DEV * (red_abs_dev - det->red_dev);

    const float ir_motion_ratio = det->ir_dev / fmaxf(det->ir_dc, 1.0f);
    const float red_motion_ratio = det->red_dev / fmaxf(det->red_dc, 1.0f);

    const bool dc_ok =
        (det->ir_dc > CONTACT_IR_DC_MIN) &&
        (det->red_dc > CONTACT_RED_DC_MIN);

    const bool not_saturated =
        (irf < CONTACT_RAW_MAX) &&
        (redf < CONTACT_RAW_MAX);

    const bool not_chaotic =
        (ir_motion_ratio < CONTACT_MOTION_RATIO_MAX) &&
        (red_motion_ratio < CONTACT_MOTION_RATIO_MAX);

    const bool sample_ok = dc_ok && not_saturated && not_chaotic;

    if (sample_ok) {
        if (!det->stable_window_open) {
            det->stable_window_open = true;
            det->stable_start_ms = timestamp_ms;
        }

        if ((timestamp_ms - det->stable_start_ms) >= det->stable_required_ms) {
            det->present = true;
        }
    } else {
        det->stable_window_open = false;
        det->stable_start_ms = 0;
        det->present = false;
    }

    return det->present;
}

bool contact_detector_is_present(const contact_detector_t *det) {
    if (det == NULL) {
        return false;
    }

    return det->present;
}