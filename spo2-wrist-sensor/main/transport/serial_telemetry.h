#pragma once

#include "app/app_types.h"

void serial_telemetry_print_sample(const ppg_sample_t *sample);
void serial_telemetry_print_frame(const char *state_str, const health_frame_t *frame);
void serial_telemetry_print_message(const char *tag, const char *msg);