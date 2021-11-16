# kissFFT Adaptation for the ESP32 microcontroller
This is a personal adaptation for the ESP32 microcontroller of the well known kissFFT library.

# FFTProcessor Class

## Usage example:
Invoke a instance of the FFTProcessor class.

```cpp
- FFTProcessor *FFT = new FFTProcessor(AUDIO_LENGTH, WINDOW_SIZE);
```

This software works perfect when AUDIO_LENGHT and WINDOW_SIZE are equal and less than 1300.

Test the code with a sine wave. First create a sine wave of frecuency "freq" and Number of samples equal to AUDIO_LENGTH.

```cpp
float *sin_200 = FFT->sin_wave(freq, AUDIO_LENGTH);
```

(Take in mind that freq has to be < AUDIO_LENGTH/2). For example, if AUDIO_LENGTH = 1200 -> freq < 600.

### Compute the FFT of the signal:
```cpp
-  FFT->computeFFT(sin_200);
```
You can then see the output with various functions (I'll be adding more when i have the time):

```cpp
- FFT->print_energy_python(); -> prints the FFT result in a python array style.
- FFT->print_energy();        -> prints the absolute value of each frecuency.
- FFT->print_complex();       -> prints the result for each frecuency in their complex format ( real + i*imag )
```
### Output of ESP32 FFT of the 200Hz sine wave.

![ESP32 200Hz Sine Wave Output](https://user-images.githubusercontent.com/41343686/141880593-dbdc7860-5839-47ea-8fc9-f233378e2fec.png)


## Testing with a real EMG signal:

![real emg signal](https://user-images.githubusercontent.com/41343686/141880111-489c5ef0-1dd4-4f3f-ae1e-01655095f136.png)

                                 (You can find this signal in 'data.h')

After applyig the FFT to the signal, we can compare the output of the spectral density generated by the ESP32 with the result generated by the python FFT algorithm.

![Python FFT Output](https://user-images.githubusercontent.com/41343686/141881084-264a54ba-27c4-4bb9-9542-89b73d5f7a7e.png) ![ESP32 FFT Output](https://user-images.githubusercontent.com/41343686/141881090-4b2a7351-6ed9-488d-86c2-aa9667845a6d.png)



