#ifndef __FIR_FILTER__HEADER__
#define __FIR_FILTER__HEADER__

#define FILTERTAPS 30

template<const int filterTaps>
class FIR {

  private:
    float values[filterTaps];
    float coeffs[filterTaps];               
    float gain; //declare gain coefficient to scale the output back to normal
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
