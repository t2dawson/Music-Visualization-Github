<<<<<<< HEAD
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
    float firProcess(float input[], int sizeOfInput);

    FIR();
    FIR(float newGain, float* newCoeffs);
};
#endif // __FIR_FILTER_HEADER__
=======
#ifndef __FIR_HEADER__
#define __FIR_HEADER__

#define FILTERTAPS 30



class FIR {

    int values[FILTERTAPS];
    float coeffs[FILTERTAPS];
    float gain; // to set gain to normal after filtering - adjust gain according to your needs
    int k;  // stores index of ring buffer used in filtering

public:

void setGain(float gain);
void setCoefficients (float * newCoeffs);
void setCoeff ( int index, float newCoef);
FIR(float *coeffs, float gain );
int process (int input);
};

#endif //__FIR_HEADER_

>>>>>>> origin/Tahir_develop
