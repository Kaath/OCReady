#ifndef _MAIN_H_
#define _MAIN_H_


// main code functions

float *forward(float weightsInput[], float weightsOutput[], float inputs[], size_t HiddenUnits)

float *backward(float weightsInput[], float weightsOutput[], float LearningRate, float forwardresults[], size_t HiddenUnits, float inputs[])


#endif
