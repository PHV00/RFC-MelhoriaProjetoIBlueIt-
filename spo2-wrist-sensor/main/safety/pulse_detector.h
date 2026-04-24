#pragma once

#include <stdbool.h>
#include <stdint.h>

#define PULSE_LP_ALPHA              0.25f
#define PULSE_ENV_ALPHA             0.10f

#define PULSE_BPM_MIN               40.0f
#define PULSE_BPM_MAX               180.0f

#define PULSE_ENV_MIN               80.0f
#define PULSE_PEAK_FACTOR           0.55f

#define PULSE_REFRACTORY_MS         300
#define PULSE_TIMEOUT_MS            2500
#define PULSE_PERIOD_TOLERANCE      0.20f

typedef struct {
    float filt;
    float env;

    float prev2;
    float prev1;

    uint32_t prev2_ts_ms;
    uint32_t prev1_ts_ms;

    uint32_t last_peak_ts_ms;
    float last_interval_ms;

    float bpm;
    uint8_t good_intervals;

    bool valid;
} pulse_detector_t;

void pulse_detector_init(pulse_detector_t *det);
void pulse_detector_reset(pulse_detector_t *det);

bool pulse_detector_update(
    pulse_detector_t *det,
    uint32_t timestamp_ms,
    float ir_ac_sample
);

bool pulse_detector_is_valid(const pulse_detector_t *det);
float pulse_detector_get_bpm(const pulse_detector_t *det);