#include "FIR.h"
#include "Arduino.h"

<<<<<<< HEAD
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

float FIR::firProcess(float input[], int sizeOfInput) {
  float out = 0; // out is the return variable. It is set to 0 every time we call the filter!
  for (int j = 0; j < sizeOfInput; j++) {
    values[k] = input[j];                                            // store the input of the routine (contents of the 'in' variable) in the array at the current pointer position
    for (int i = 0; i < FILTERTAPS; i++)  {                         // we step through the array
      out += coeffs[i] * values[(i + k) % FILTERTAPS];             // ... and add and multiply each value to accumulate the output
                                                                  //  (i + k) % filterTaps creates a cyclic way of getting through the array
    }
    out /= gain;                                                // We need to scale the output (unless the coefficients provide unity gain in the passband)
    k = (k + 1) % FILTERTAPS;                                  // k is increased and wraps around the filterTaps, so next time we will overwrite the oldest saved sample in the array
  }
  return out;                                                // we send the output value back to whoever called the routine
}


=======

FIR::FIR(float * newCoeffs,float newGain){

memset(values,0,FILTERTAPS);

setGain(newGain);
setCoefficients(newCoeffs);

  k = 0;
}


void FIR::setGain(float newGain){

  gain = newGain;
}

void FIR:: setCoefficients(float * newCoeffs){
  for (int i =0; i < FILTERTAPS; i++){
    coeffs[i] = newCoeffs[i];
  }
}
void FIR::setCoeff(int index,float newCoef){
    coeffs[index] = newCoef;
}

int FIR::process (int input){
  
  float out = 0;
  values[k] = input;

  for (int i = 0; i < FILTERTAPS; i++){
    out +=(coeffs[i] * values[(i + k) % FILTERTAPS]);
  }
  out /= gain;

  k = (k+1)% FILTERTAPS;

  return (int)out;
}


>>>>>>> origin/Tahir_develop
