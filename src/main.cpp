#include <Arduino.h>
#include <data.h>
#include <FFTProcessor.h>

#define WINDOW_SIZE 1200
#define AUDIO_LENGTH 1200


float *my_sin;
int freq = 500;

FFTProcessor *FFT = new FFTProcessor(AUDIO_LENGTH, WINDOW_SIZE);

void setup() {
  Serial.begin(115200);

  // No olvidarse liberar la memoria pedida por my_sin
  my_sin = FFT->sin_wave(freq, AUDIO_LENGTH);

}

void loop() {

  unsigned long time = micros();

  FFT->computeFFT(my_sin);

  // Serial.print("Tiempo total de computo FFT:");
  // Serial.println(micros()-time);
      Serial.println("");
      Serial.println("-------------------------------");

  FFT->print_energy_python();

  Serial.println("");
  // FFTProcessor->print_energy();
  vTaskDelay(5000);
}