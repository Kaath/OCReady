#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

typedef float func_t(float);

// operations functions

float sigmoid(float x);

float sigmoidprime(float x);

float *mul(float inputs[], float weights[], size_t n, size_t m, size_t p);

float *apply(func_t f, float values[], size_t size);

float *substract(float output[], float outputresult[], size_t lines, size_t cols);

float *add(float output[] , float outputresult[], size_t lines, size_t cols);

float *transpose(float mat[], size_t lines, size_t cols);

float *scalar(float mat[], float LearningRate, size_t lines, size_t cols);

float *dot(float prime[] , float error[], size_t lines, size_t cols);

#endif
