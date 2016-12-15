#include "FIR.h"
#include "RGBControl.h"
#include "Setup.h"

#define BUFFER 20

long Time2 = 0;
long Time1 = 0;
long timeDT = 0;


int mic_NoFilt[BUFFER];

RGBControl RCtrl(3, 50, 20), GCtrl(5, 50, 7), BCtrl(7, 50, 2);
FIR firR, firG, firB;

void setup()  {
  setupADC();
  RCtrl.setMinMax(0,10);
  GCtrl.setMinMax(0,10);
  BCtrl.setMinMax(0,10);
  
  Serial.begin(115200);
  memset(mic_NoFilt, 0, sizeof(int)*BUFFER);
  if (SENDSERIAL) {
    Serial.begin(115200);
  }
  float Rcoef[FILTERTAPS] = {0.021987, 0.024035, 0.026037, 0.027974, 0.029828, 0.03158, 0.033212, 0.034709, 0.036054, 0.037234, 0.038238, 0.039053, 0.039672, 0.040089, 0.040298, 0.040298, 0.040089, 0.039672, 0.039053, 0.038238, 0.037234, 0.036054, 0.034709, 0.033212, 0.03158, 0.029828, 0.027974, 0.026037, 0.024035, 0.021987};
  //{0.030352,0.03572,0.04093,0.045848,0.050345,0.054301,0.057606,0.06017,0.061921,0.062808,0.062808,0.061921,0.06017,0.057606,0.054301,0.050345,0.045848,0.04093,0.03572,0.030352};
  //{0.0070018,0.0094086,0.016214,0.026914,0.040488,0.055516,0.070343,0.083292,0.092868,0.097955,0.097955,0.092868,0.083292,0.070343,0.055516,0.040488,0.026914,0.016214,0.0094086,0.0070018};
  float Bcoef[FILTERTAPS]  = { -0.011762, -0.038701, 0.0050889, 0.056559, 0.015417, -0.034795, -0.0098747, -0.011244, -0.051569, 0.030127, 0.14934, 0.018955, -0.22001, -0.12084, 0.20886, 0.20886, -0.12084, -0.22001, 0.018955, 0.14934, 0.030127, -0.051569, -0.011244, -0.0098747, -0.034795, 0.015417, 0.056559, 0.0050889, -0.038701, -0.011762};
  //{-0.0059583,0.010091,-0.011563,0.0090001,0.080684,0.06634,-0.085756,-0.18041,-0.040071,0.18015,0.18015,-0.040071,-0.18041,-0.085756,0.06634,0.080684,0.0090001,-0.011563,0.010091,-0.0059583};
  //{0.0039218,0.0041651,-0.0017636,-0.024773,-0.064743,-0.096112,-0.078892,0.0056742,0.12672,0.2157,0.2157,0.12672,0.0056742,-0.078892,-0.096112,-0.064743,-0.024773,-0.0017636,0.0041651,0.0039218};
  float Gcoef[FILTERTAPS] = {0.014581, 0.015791, -0.017186, -0.018813, 0.020738, 0.023056, -0.025904, -0.029495, 0.034171, 0.040525, -0.049674, -0.064014, 0.089775, 0.1498, -0.44965, 0.44965, -0.1498, -0.089775, 0.064014, 0.049674, -0.040525, -0.034171, 0.029495, 0.025904, -0.023056, -0.020738, 0.018813, 0.017186, -0.015791, -0.014581};
  //{-0.0063113,0.030439,0.034878,-0.0095334,-0.057106,-0.039805,0.051455,0.12769,0.042445,-0.54343,0.54343,-0.042445,-0.12769,-0.051455,0.039805,0.057106,0.0095334,-0.034878,-0.030439,0.0063113};
  //{0.0012888,-0.0014432,-0.007129,-0.0119,-0.0030922,0.027927,0.065647,0.063596,-0.04974,-0.57121,0.57121,0.04974,-0.063596,-0.065647,-0.027927,0.0030922,0.0119,0.007129,0.0014432,-0.0012888};
  firR.setCoefficients(Rcoef);
  firR.setGain(1);
  firB.setCoefficients(Bcoef);
  firB.setGain(2);
  firG.setCoefficients(Gcoef);
  firG.setGain(0.5);
  //if you want to add other things to setup(), do it here
}

void loop()  {

  int Buff = 0;

  while (Buff < BUFFER) {
    Time2 = micros();
    if (  Time2 - Time1 >= 56) {
      Time2 = micros();
      mic_NoFilt[Buff] = ADCH;//analogRead(micPin);
     // Serial.println(mic_NoFilt[Buff]);
      timeDT = Time2 - Time1;
      Time1 = micros();
      Buff++;
    }
  }
  for(Buff =0; Buff < BUFFER; Buff++){
  RCtrl.micVal = (int)(firR.firProcess(mic_NoFilt[Buff]));
  GCtrl.micVal = (int)(firG.firProcess(mic_NoFilt[Buff]));
  BCtrl.micVal = (int)(firB.firProcess(mic_NoFilt[Buff]));
  }
  //Serial.println(RCtrl.micVal);
  if ( RCtrl.calcDC() && GCtrl.calcDC() && BCtrl.calcDC()) {
    if (SENDSERIAL) {
      Serial.print("  TIME: ");
      Serial.print(timeDT);
      Serial.print("  NoFiltVal: ");
      Serial.print(mic_NoFilt[BUFFER - 1]);
      Serial.print("  Val:  R = ");
      Serial.print(RCtrl.micVal);
      Serial.print("  G = ");
      Serial.print(GCtrl.micVal);
      Serial.print("  B = ");
      Serial.print(BCtrl.micVal);
    }

    RCtrl.micVal2Brightness();
    GCtrl.micVal2Brightness();
    BCtrl.micVal2Brightness();
    
    if (SENDSERIAL) {
      Serial.print("  MinMax:  R = ");
      Serial.print(RCtrl.micMin); Serial.print(","); Serial.print(RCtrl.micMax);
      Serial.print("  G = ");
      Serial.print(GCtrl.micMin); Serial.print(","); Serial.print(GCtrl.micMax);
      Serial.print("  B = ");
      Serial.print(BCtrl.micMin); Serial.print(","); Serial.print(BCtrl.micMax);
      Serial.print("  Bright:  R = ");
      Serial.print(RCtrl.brightness);
      Serial.print("  G = ");
      Serial.print(GCtrl.brightness);
      Serial.print("  B = ");
      Serial.print(BCtrl.brightness);
    }
    RCtrl.writeBright();
    BCtrl.writeBright();
    GCtrl.writeBright();
   
    if (SENDSERIAL){
          Serial.print("  LastBright:  R = ");
          Serial.print(RCtrl.lastBrightness);
          Serial.print("  G = ");
          Serial.print(GCtrl.lastBrightness); 
          Serial.print("  B = ");
          Serial.println(BCtrl.lastBrightness); 
    }
  }
}



