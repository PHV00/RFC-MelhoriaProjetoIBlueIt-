#pragma once

#include <stdbool.h>
#include <stdint.h>

#define CONTACT_ALPHA_DC             0.02f
#define CONTACT_ALPHA_DEV            0.05f

#define CONTACT_IR_DC_MIN            20000.0f
#define CONTACT_RED_DC_MIN           8000.0f
#define CONTACT_RAW_MAX              260000.0f

#define CONTACT_MOTION_RATIO_MAX     0.35f

typedef struct {
    float ir_dc;
    float red_dc;

    float ir_dev;
    float red_dev;

    uint32_t stable_start_ms;
    uint32_t stable_required_ms;

    bool stable_window_open;
    bool present;
} contact_detector_t;

void contact_detector_init(contact_detector_t *det, uint32_t stable_required_ms);

bool contact_detector_update(
    contact_detector_t *det,
    uint32_t timestamp_ms,
    uint32_t ir_raw,
    uint32_t red_raw
);

bool contact_detector_is_present(const contact_detector_t *det);