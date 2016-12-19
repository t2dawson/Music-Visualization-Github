#include "FIR.h"
#include "Arduino.h"

FIR::FIR() {
  k = 0; //initialize so that we start to read at index 0
  memset(values, 0, sizeof(float)*FILTERTAPS);
  //TODO calculate default gain?
  //TODO calculate default coefs?
}

FIR::FIR(float newGain, float* newCoeffs) {
  k = 0; //initialize so that we start to read at index 0
  setGain(newGain);
  memset(values, 0, sizeof(float)* FILTERTAPS);
  setCoefficients(newCoeffs);
}

void FIR::setGain(float newGain) {
  gain = newGain;
}

void FIR::setCoefficients(float* newCoeffs) {
  for (int i = 0; i < FILTERTAPS; i++) {
    coeffs[i] = newCoeffs[i];
  }
}

void FIR::setCoefficient(float newCoeff, int index) {
  coeffs[index] = newCoeff;
}

int FIR::firProcess(int* input, int sizeOfInput) {
  float out = 0 ; // out is the return variable. It is set to 0 every time we call the filter!
  for (int i = 0; i < sizeOfInput; i++) {

    values[k] = (float)input[i];      // store the input of the routine (contents of the 'in' variable) in the array at the current pointer position
    if (i == (sizeOfInput - 1)) {

      for (int j = 0; j < FILTERTAPS; j++)  {
        // we step through the array
        out += (coeffs[j] * values[(j + k) % FILTERTAPS]);             // ... and add and multiply each value to accumulate the output                                                            //  (i + k) % filterTaps creates a cyclic way of getting through the array
      }
    }                                                  // We need to scale the output (unless the coefficients provide unity gain in the passband)
    k = (k + 1) % FILTERTAPS;                                  // k is increased and wraps around the filterTaps, so next time we will overwrite the oldest saved sample in the array
  }
  return (int)(out / gain);                                // we send the output value back to whoever called the routine
}


