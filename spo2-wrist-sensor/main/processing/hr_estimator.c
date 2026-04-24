#include "processing/hr_estimator.h"

#include <stddef.h>

static float average_u32(const uint32_t *v, size_t n) {
    if (v == NULL || n == 0) {
        return 0.0f;
    }

    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
        sum += v[i];
    }

    return (float)(sum / (double)n);
}

bool hr_estimator_compute(const sample_buffer_t *buffer, const signal_quality_t *quality, hr_result_t *out_hr) {
    if (buffer == NULL || quality == NULL || out_hr == NULL) {
        return false;
    }

    out_hr->valid = false;
    out_hr->bpm = 0.0f;

    size_t count = sample_buffer_count(buffer);
    if (count < 40) {
        return false;
    }

    if (!quality->signal_present || quality->quality_score < 0.35f) {
        return false;
    }

    uint32_t ir[SAMPLE_BUFFER_SIZE] = {0};
    uint32_t ts[SAMPLE_BUFFER_SIZE] = {0};

    ppg_sample_t s = {0};
    for (size_t i = 0; i < count; i++) {
        if (!sample_buffer_get_oldest_first(buffer, i, &s)) {
            return false;
        }
        ir[i] = s.ir;
        ts[i] = s.timestamp_ms;
    }

    uint32_t min_ir = ir[0];
    uint32_t max_ir = ir[0];
    for (size_t i = 1; i < count; i++) {
        if (ir[i] < min_ir) min_ir = ir[i];
        if (ir[i] > max_ir) max_ir = ir[i];
    }

    float mean_ir = average_u32(ir, count);
    float amplitude = (float)(max_ir - min_ir);

    if (amplitude < 20.0f) {
        return false;
    }

    /* suavização simples 5-pontos */
    float sm[SAMPLE_BUFFER_SIZE] = {0};
    for (size_t i = 0; i < count; i++) {
        int start = (i < 2) ? 0 : (int)i - 2;
        int end = ((i + 2) >= count) ? (int)count - 1 : (int)i + 2;

        double acc = 0.0;
        int n = 0;
        for (int j = start; j <= end; j++) {
            acc += (double)ir[j];
            n++;
        }
        sm[i] = (float)(acc / (double)n);
    }

    float threshold = mean_ir + amplitude * 0.20f;

    uint32_t peak_ts[SAMPLE_BUFFER_SIZE] = {0};
    size_t peak_count = 0;
    uint32_t last_peak_ts = 0;

    for (size_t i = 1; i + 1 < count; i++) {
        bool is_peak =
            (sm[i] > sm[i - 1]) &&
            (sm[i] >= sm[i + 1]) &&
            (sm[i] > threshold);

        if (!is_peak) {
            continue;
        }

        uint32_t now_ts = ts[i];

        /* período refratário: ignora picos muito próximos */
        if (peak_count > 0 && (now_ts - last_peak_ts) < 300) {
            continue;
        }

        peak_ts[peak_count++] = now_ts;
        last_peak_ts = now_ts;
    }

    if (peak_count < 2) {
        return false;
    }

    double interval_sum_ms = 0.0;
    size_t interval_count = 0;

    for (size_t i = 1; i < peak_count; i++) {
        uint32_t dt = peak_ts[i] - peak_ts[i - 1];

        /* faixa plausível ~30 a 200 bpm */
        if (dt >= 300 && dt <= 2000) {
            interval_sum_ms += dt;
            interval_count++;
        }
    }

    if (interval_count == 0) {
        return false;
    }

    double avg_interval_ms = interval_sum_ms / (double)interval_count;
    float bpm = (float)(60000.0 / avg_interval_ms);

    if (bpm < 35.0f || bpm > 220.0f) {
        return false;
    }

    out_hr->valid = true;
    out_hr->bpm = bpm;
    return true;
}