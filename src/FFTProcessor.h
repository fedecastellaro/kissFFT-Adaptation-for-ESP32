#ifndef FFT_Processor
#define FFT_Processor

#include <stdlib.h>
#include <stdint.h>
#include "../lib/kissfft/tools/kiss_fftr.h"


class FFTProcessor
{
private:
    int m_audio_length;
    int m_window_size;

    size_t m_fft_size;
    float *m_fft_input;
    int m_energy_size;

    float *m_energy;
    kiss_fft_cpx *m_fft_output;
    kiss_fftr_cfg m_cfg;

    float *m_chn_n;

    void get_FFT_segnment();

    float get_mean(uint16_t *data, int data_length);
    float get_mean(float *data, int data_length);
    float get_max(uint16_t *data, int data_length, float mean);
    float get_max(float *data, int data_length, float mean);

    void normalize(uint16_t *chn, float *chn_n);
    void normalize(float *chn, float *chn_n);


public:
    FFTProcessor(int audio_length, int window_size);
    ~FFTProcessor();
    void get_spectrogram(float *reader, float *output_spectrogram);
    void get_spectrogram(float *reader);
    void get_spectrogram(uint16_t *chn);

    float* sin_wave(int frecuency, int wave_lenth);

    void computeFFT(float *reader);

    void print_energy();
    void print_complex();
    void print_energy_python();
    void print_energy_serialplot();
    int getEnergySize();
};

#endif