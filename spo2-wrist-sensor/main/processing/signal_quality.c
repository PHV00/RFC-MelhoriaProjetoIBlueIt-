#include "processing/signal_quality.h"

static float clamp01(float x) {
    if (x < 0.0f) return 0.0f;
    if (x > 1.0f) return 1.0f;
    return x;
}

bool signal_quality_evaluate(const sample_buffer_t *buffer, signal_quality_t *out_quality) {
    if (buffer == NULL || out_quality == NULL) {
        return false;
    }

    size_t count = sample_buffer_count(buffer);
    if (count < 20) {
        return false;
    }

    ppg_sample_t sample;
    uint32_t min_ir = 0xFFFFFFFF;
    uint32_t max_ir = 0;
    uint32_t min_red = 0xFFFFFFFF;
    uint32_t max_red = 0;
    double sum_ir = 0.0;
    double sum_red = 0.0;

    for (size_t i = 0; i < count; i++) {
        if (!sample_buffer_get_oldest_first(buffer, i, &sample)) {
            return false;
        }

        if (sample.ir < min_ir) min_ir = sample.ir;
        if (sample.ir > max_ir) max_ir = sample.ir;
        if (sample.red < min_red) min_red = sample.red;
        if (sample.red > max_red) max_red = sample.red;

        sum_ir += sample.ir;
        sum_red += sample.red;
    }

    float dc_ir = (float)(sum_ir / (double)count);
    float dc_red = (float)(sum_red / (double)count);
    float ac_ir = (float)(max_ir - min_ir);
    float ac_red = (float)(max_red - min_red);

    float perfusion_index = 0.0f;
    if (dc_ir > 0.0f) {
        perfusion_index = ac_ir / dc_ir;
    }

    float noise = 0.0f;
    if (dc_ir > 0.0f) {
        noise = ac_red / dc_ir;
    }

    bool signal_present = (dc_ir > 1000.0f) && (ac_ir > 50.0f);

    float score_from_pi = clamp01(perfusion_index * 40.0f);
    float score_from_noise = clamp01(1.0f - (noise * 10.0f));
    float quality_score = 0.6f * score_from_pi + 0.4f * score_from_noise;

    out_quality->signal_present = signal_present;
    out_quality->dc_ir = dc_ir;
    out_quality->dc_red = dc_red;
    out_quality->ac_ir = ac_ir;
    out_quality->ac_red = ac_red;
    out_quality->noise = noise;
    out_quality->perfusion_index = perfusion_index;
    out_quality->quality_score = signal_present ? clamp01(quality_score) : 0.0f;

    return true;
}