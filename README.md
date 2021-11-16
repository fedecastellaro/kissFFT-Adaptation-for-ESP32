# kissFFT Adaptation for the ESP32 microcontroller
This is a personal adaptation for the ESP32 microcontroller of the well known kissFFT library.

## FFTProcessor Class

# Example of implementation:

- FFTProcessor *FFT = new FFTProcessor(AUDIO_LENGTH, WINDOW_SIZE);

This software works perfect when AUDIO_LENGHT and WINDOW_SIZE are equal and less than 1300.

# Usage example:

Test the code with a sine wave. First create a sine wave of frecuency "freq" and Number of samples equal to AUDIO_LENGTH.

- float *sin_200 = FFT->sin_wave(freq, AUDIO_LENGTH);

(Take in mind that freq has to be < AUDIO_LENGTH/2). For example, if AUDIO_LENGTH = 1200 -> freq < 600.

Compute the FFT of the signal:

-  FFT->computeFFT(sin_200);

You can then see the output with various functions (I'll be adding more when i have the time):

- FFT->print_energy_python(); -> prints the FFT result in a python array style.
- FFT->print_energy();        -> prints the absolute value of each frecuency.
- FFT->print_complex();       -> prints the result for each frecuency in their complex format ( real + i*imag )

## Output and comparison of the example.


