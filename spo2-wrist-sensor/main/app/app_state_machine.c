#include "app/app_state_machine.h"

static app_state_t g_state = APP_STATE_BOOT;

void app_state_machine_set(app_state_t state) {
    g_state = state;
}

app_state_t app_state_machine_get(void) {
    return g_state;
}

const char *app_state_machine_to_string(app_state_t state) {
    switch (state) {
        case APP_STATE_BOOT: return "BOOT";
        case APP_STATE_SELF_TEST: return "SELF_TEST";
        case APP_STATE_IDLE: return "IDLE";
        case APP_STATE_SAMPLING: return "SAMPLING";
        case APP_STATE_TRACKING: return "TRACKING";
        case APP_STATE_LOW_CONFIDENCE: return "LOW_CONFIDENCE";
        case APP_STATE_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}