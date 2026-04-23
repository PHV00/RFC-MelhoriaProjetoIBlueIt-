#include "processing/spo2_estimator.h"

bool spo2_estimator_compute(const sample_buffer_t *buffer, const signal_quality_t *quality, spo2_result_t *out_spo2) {
    (void)buffer;

    if (quality == NULL || out_spo2 == NULL) {
        return false;
    }

    out_spo2->valid = false;
    out_spo2->spo2 = 0.0f;

    if (!quality->signal_present || quality->quality_score < 0.55f) {
        return false;
    }

    /* TODO:
       Implementar cálculo real de SpO2 com razão RED/IR e calibração.
       Nesta primeira fase, a função só prepara a arquitetura.
    */
    return false;
}