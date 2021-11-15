#include <stdlib.h>
#include <algorithm>
#include <Arduino.h>
#include "FFTProcessor.h"
#include "HammingWindow.h"

#define EPSILON 1e-6

FFTProcessor::FFTProcessor(int audio_length, int window_size)
{
    m_audio_length = audio_length;
    m_window_size = window_size;
    m_fft_size = 1;
 
    m_fft_size = window_size;
    m_fft_input = static_cast<float *>(malloc(sizeof(float) * m_fft_size));
    m_energy_size = m_fft_size / 2 + 1;

    m_fft_output = static_cast<kiss_fft_cpx *>(malloc(sizeof(kiss_fft_cpx) * m_energy_size));
    m_energy = static_cast<float *>(malloc(sizeof(float) * m_energy_size));
    m_chn_n = static_cast<float *>(malloc(sizeof(float) * window_size));

    // initialise kiss fftr
    m_cfg = kiss_fftr_alloc(m_fft_size, false, 0, 0);

}

FFTProcessor::~FFTProcessor()
{
    free(m_cfg);
    free(m_fft_input);
    free(m_fft_output);
    free(m_energy);
    free(m_chn_n);
}


void FFTProcessor::get_FFT_segnment()
{
    kiss_fftr(
        m_cfg,
        m_fft_input,
        reinterpret_cast<kiss_fft_cpx *>(m_fft_output));
    // pull out the magnitude squared values
    for (int i = 0; i < m_energy_size; i++)
    {
        const float real = m_fft_output[i].r;
        const float imag = m_fft_output[i].i;
        const float mag_squared = sqrtf((real * real) + (imag * imag));
        m_energy[i] = mag_squared;

    }
}

void FFTProcessor::computeFFT(float *data){

    normalize(data, m_chn_n);
    m_fft_input = m_chn_n;
    //m_hamming_window->applyWindow(m_fft_input);

    // compute the spectrum for the window of samples and write it to the output
    get_FFT_segnment();

}

void FFTProcessor::get_spectrogram(float *reader)
{
// read samples from the reader into the fft input normalising them by subtracting the mean and dividing by the absolute max
        for (int i = 0; i < m_window_size; i++)
        {
            m_fft_input[i] = reader[i];
        }
        // compute the spectrum for the window of samples and write it to the output
        get_FFT_segnment();
        
    return; 
}

void FFTProcessor::get_spectrogram(uint16_t *chn)
{
        // read samples from the reader into the fft input normalising them by subtracting the mean and dividing by the absolute max
        normalize(chn, m_chn_n);
        m_fft_input = m_chn_n;
        //m_hamming_window->applyWindow(m_fft_input);

        // compute the spectrum for the window of samples and write it to the output
        get_FFT_segnment();
        
    return; 
}

void FFTProcessor::print_energy()
{
    for (int i = 0; i < m_energy_size; i++)
        {
            Serial.printf("Frecuencia %i: %.05f \n",i, m_energy[i]);
            // Serial.println(m_energy[i]);
        }
}

void FFTProcessor::print_energy_python()
{
    for (int i = 0; i < m_energy_size; i++)
        {
            Serial.print(m_energy[i]);
            Serial.print(',');
        }
}

void FFTProcessor::print_energy_serialplot()
{
    for (int i = 0; i < m_energy_size; i++)
    {
        Serial.print(m_energy[i]);
    }
}

void FFTProcessor::print_complex()
{
    for (int i = 0; i < m_energy_size; i++)
        {
        const float real = m_fft_output[i].r;
        const float imag = m_fft_output[i].i;

        Serial.printf("Frecuencia %i: %.05f + i%.05f\n",i, real, imag);
        }
}

int FFTProcessor::getEnergySize(){
    return m_energy_size;
}

float FFTProcessor::get_mean(uint16_t *data, int data_length)
{
  float mean = 0;
  for (int i = 0; i < data_length; i++)
    {
        mean += data[i];
    }
  return mean /= data_length;
}

float FFTProcessor::get_mean(float *data, int data_length)
{
  float mean = 0;
  for (int i = 0; i < data_length; i++)
    {
        mean += data[i];
    }
  return mean /= data_length;
}

float FFTProcessor::get_max(uint16_t *data, int data_length, float mean)
{
  float max = 0;
    for (int i = 0; i < data_length; i++)
    {
        float value = fabsf((float)data[i] - mean);
        max = std::max(max, value);
    }

    return max;
}

float FFTProcessor::get_max(float *data, int data_length, float mean)
{
  float max = 0;
    for (int i = 0; i < data_length; i++)
    {
        float value = fabsf((float)data[i] - mean);
        max = std::max(max, value);
    }

    return max;
}

void FFTProcessor::normalize(uint16_t *chn, float *chn_n)
{
    float mean = get_mean(chn, m_window_size);

    float max = get_max(chn, m_window_size, mean);

    for (int i = 0; i < m_window_size; i++)
         chn_n[i] = (chn[i] - mean) / max;
}

void FFTProcessor::normalize(float *chn, float *chn_n)
{
    float mean = get_mean(chn, m_window_size);

    float max = get_max(chn, m_window_size, mean);

    for (int i = 0; i < m_window_size; i++)
         chn_n[i] = (chn[i] - mean) / max;
}

float* FFTProcessor::sin_wave(int frecuency, int wave_lenth){

    float *my_sin = (float*) malloc(wave_lenth * sizeof(float));

    for ( int i = 1; i < wave_lenth ; i++)
    {
        my_sin[i] = (float)(sin(frecuency*2*PI*i/wave_lenth));
        // Serial.println(frecuency*2*PI*1/i);
    }
    return my_sin;
}