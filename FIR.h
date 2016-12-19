#ifndef __FIR_FILTER__HEADER__
#define __FIR_FILTER__HEADER__

#define FILTERTAPS 30
class FIR {

  private:
    float values[FILTERTAPS];
    float coeffs[FILTERTAPS];
    //declare gain coefficient to scale the output back to normal
    float gain; // set to 1 and input unity to see what this needs to be
    int k; // k stores the index of the current array read to create a circular memory through the array

  public:

    void setGain(float newGain);
    void setCoefficients(float* newCoeffs);
    void setCoefficient(float newCoeff, int index);
    int firProcess(int* input, int sizeOfInput);

    FIR();
    FIR(float newGain, float* newCoeffs);
};
#endif // __FIR_FILTER_HEADER__
