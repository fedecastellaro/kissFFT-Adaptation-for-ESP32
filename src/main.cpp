#include <Arduino.h>
#include <data.h>
#include <FFTProcessor.h>

#define WINDOW_SIZE 1200
#define AUDIO_LENGTH 1200


float *sin_200;
int freq = 200;

FFTProcessor *FFT = new FFTProcessor(AUDIO_LENGTH, WINDOW_SIZE);

void setup() {
  Serial.begin(115200);

  // No olvidarse liberar la memoria pedida por my_sin
  sin_200 = FFT->sin_wave(freq, AUDIO_LENGTH);

}

void loop() {

  // unsigned long time = micros();
  Serial.println("200Hz signal FFT Test: ");

  FFT->computeFFT(sin_200);

  FFT->print_energy_python();

  Serial.println("");
  Serial.println("");

  FFT->computeFFT(chn1);

  Serial.println("Sample signal FFT Test: ");

  FFT->print_energy_python();

  Serial.println("");
  Serial.println("");


  vTaskDelay(10000);
}