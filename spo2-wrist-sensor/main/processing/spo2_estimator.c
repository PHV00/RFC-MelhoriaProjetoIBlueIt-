#include "processing/spo2_estimator.h"

#include <math.h>
#include <stddef.h>

static float clampf(float x, float lo, float hi) {
    if (x < lo) return lo;
    if (x > hi) return hi;
    return x;
}

bool spo2_estimator_compute(const sample_buffer_t *buffer, const signal_quality_t *quality, spo2_result_t *out_spo2) {
    if (buffer == NULL || quality == NULL || out_spo2 == NULL) {
        return false;
    }

    out_spo2->valid = false;
    out_spo2->spo2 = 0.0f;

    size_t count = sample_buffer_count(buffer);
    if (count < 40) {
        return false;
    }

    if (!quality->signal_present || quality->quality_score < 0.45f) {
        return false;
    }

    double sum_red = 0.0;
    double sum_ir = 0.0;

    ppg_sample_t s = {0};
    for (size_t i = 0; i < count; i++) {
        if (!sample_buffer_get_oldest_first(buffer, i, &s)) {
            return false;
        }
        sum_red += s.red;
        sum_ir += s.ir;
    }

    double dc_red = sum_red / (double)count;
    double dc_ir = sum_ir / (double)count;

    if (dc_red <= 0.0 || dc_ir <= 0.0) {
        return false;
    }

    double sq_red = 0.0;
    double sq_ir = 0.0;

    for (size_t i = 0; i < count; i++) {
        if (!sample_buffer_get_oldest_first(buffer, i, &s)) {
            return false;
        }

        double red_ac = (double)s.red - dc_red;
        double ir_ac = (double)s.ir - dc_ir;

        sq_red += red_ac * red_ac;
        sq_ir += ir_ac * ir_ac;
    }

    double ac_red_rms = sqrt(sq_red / (double)count);
    double ac_ir_rms = sqrt(sq_ir / (double)count);

    if (ac_red_rms <= 0.0 || ac_ir_rms <= 0.0) {
        return false;
    }

    double r = (ac_red_rms / dc_red) / (ac_ir_rms / dc_ir);

    /* aproximação experimental */
    float spo2 = (float)(104.0 - 17.0 * r);
    spo2 = clampf(spo2, 0.0f, 100.0f);

    /* com MAX30105, trate como estimativa experimental */
    if (spo2 < 70.0f || spo2 > 100.0f) {
        return false;
    }

    out_spo2->valid = true;
    out_spo2->spo2 = spo2;
    return true;
}