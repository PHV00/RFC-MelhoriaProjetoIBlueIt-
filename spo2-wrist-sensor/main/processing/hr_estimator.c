#include "processing/hr_estimator.h"

bool hr_estimator_compute(const sample_buffer_t *buffer, const signal_quality_t *quality, hr_result_t *out_hr) {
    (void)buffer;

    if (quality == NULL || out_hr == NULL) {
        return false;
    }

    out_hr->valid = false;
    out_hr->bpm = 0.0f;

    if (!quality->signal_present || quality->quality_score < 0.45f) {
        return false;
    }

    /* TODO:
       Implementar estimativa real de FC a partir do PPG do punho.
       Nesta primeira fase, a função apenas informa que a estrutura existe.
    */
    return false;
}