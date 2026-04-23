#pragma once

#include "app/app_types.h"

void app_state_machine_set(app_state_t state);
app_state_t app_state_machine_get(void);
const char *app_state_machine_to_string(app_state_t state);