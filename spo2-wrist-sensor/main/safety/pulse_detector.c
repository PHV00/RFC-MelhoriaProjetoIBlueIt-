#include "safety/pulse_detector.h"

#include <math.h>

void pulse_detector_init(pulse_detector_t *det) {
    if (det == NULL) {
        return;
    }

    det->filt = 0.0f;
    det->env = 0.0f;

    det->prev2 = 0.0f;
    det->prev1 = 0.0f;

    det->prev2_ts_ms = 0;
    det->prev1_ts_ms = 0;

    det->last_peak_ts_ms = 0;
    det->last_interval_ms = 0.0f;

    det->bpm = 0.0f;
    det->good_intervals = 0;
    det->valid = false;
}

void pulse_detector_reset(pulse_detector_t *det) {
    pulse_detector_init(det);
}

bool pulse_detector_update(
    pulse_detector_t *det,
    uint32_t timestamp_ms,
    float ir_ac_sample
) {
    if (det == NULL) {
        return false;
    }

    det->filt += PULSE_LP_ALPHA * (ir_ac_sample - det->filt);
    det->env += PULSE_ENV_ALPHA * (fabsf(det->filt) - det->env);

    const float peak_threshold = fmaxf(PULSE_ENV_MIN, det->env * PULSE_PEAK_FACTOR);

    const bool local_peak =
        (det->prev1 > det->prev2) &&
        (det->prev1 >= det->filt) &&
        (det->prev1 > peak_threshold);

    if (local_peak) {
        const uint32_t peak_ts_ms = det->prev1_ts_ms;

        if (
            (det->last_peak_ts_ms == 0) ||
            ((peak_ts_ms - det->last_peak_ts_ms) >= PULSE_REFRACTORY_MS)
        ) {
            if (det->last_peak_ts_ms != 0) {
                const float interval_ms = (float)(peak_ts_ms - det->last_peak_ts_ms);
                const float bpm = 60000.0f / interval_ms;

                const bool bpm_plausible =
                    (bpm >= PULSE_BPM_MIN) &&
                    (bpm <= PULSE_BPM_MAX);

                bool periodic = true;
                if (det->last_interval_ms > 0.0f) {
                    const float rel_diff =
                        fabsf(interval_ms - det->last_interval_ms) / det->last_interval_ms;
                    periodic = (rel_diff <= PULSE_PERIOD_TOLERANCE);
                }

                const bool amplitude_ok = (det->env >= PULSE_ENV_MIN);

                if (bpm_plausible && periodic && amplitude_ok) {
                    det->good_intervals++;
                    det->bpm = bpm;
                } else {
                    det->good_intervals = 0;
                    det->bpm = 0.0f;
                }

                det->last_interval_ms = interval_ms;
                det->valid = (det->good_intervals >= 2);
            }

            det->last_peak_ts_ms = peak_ts_ms;
        }
    }

    if (
        (det->last_peak_ts_ms != 0) &&
        ((timestamp_ms - det->last_peak_ts_ms) > PULSE_TIMEOUT_MS)
    ) {
        det->valid = false;
        det->good_intervals = 0;
        det->bpm = 0.0f;
        det->last_interval_ms = 0.0f;
    }

    det->prev2 = det->prev1;
    det->prev2_ts_ms = det->prev1_ts_ms;

    det->prev1 = det->filt;
    det->prev1_ts_ms = timestamp_ms;

    return det->valid;
}

bool pulse_detector_is_valid(const pulse_detector_t *det) {
    if (det == NULL) {
        return false;
    }

    return det->valid;
}

float pulse_detector_get_bpm(const pulse_detector_t *det) {
    if (det == NULL) {
        return 0.0f;
    }

    return det->bpm;
}