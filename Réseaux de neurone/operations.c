# include <stdio.h>
# include <stdlib.h>

# include "operations.h"

float sigmoid(float x){
  return 1 / (1 + exp(-x));
}


float sigmoidprime(float x){
  return -(exp(x)/((1+exp(x))*(1+exp(x))));
}

float *mul(float inputs, float weights, size_t n, size_t m, size_t p){
  float res[lines*cols];
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < p; j++) {
      for (size_t k = 0; k < m; k++) {
        res[j + i*p] += m1[k + i*m] * m2[j + k*p];
      }
    }
  }
  return res;
}


float *apply(func_t f, float values[], size_t size){
  float res[size];
  for (size_t i = 0; i < size; i++) {
    res[i] = f(values[i]);
  }
  return res;
}


float *substract(float output[] , float outputresult[], size_t lines, size_t cols){
  float res[lines*cols];
  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < cols; j++) {
      res[j + i*cols] = mat1[j + i*cols] - mat2[j + i*cols];
    }
  }
  return res;
}


float *add(float output[] , float outputresult[], size_t lines, size_t cols){
  float res[lines*cols];
  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < cols; j++) {
      res[j + i*cols] = mat1[j + i*cols] + mat2[j + i*cols];
    }
  }
  return res;
}


float *transpose(float mat[], size_t lines, size_t cols){
  float res[lines*cols];
  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < cols; j++) {
      res[j + i*lines] = mat[i + j*cols];
    }
  }
  return res;
}


float *scalar(float mat[], float LearningRate){
  float res[lines*cols];
  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < cols; j++) {
      res[i] = mat[i] * LearningRate;
    }
  }
  return res;
}


float *dot(float prime[] , float error[], size_t lines, size_t cols){
  float res[lines*cols];
  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < cols; j++) {
      res[j + i*cols] = mat1[j + i*cols] * mat2[j + i*cols];
    }
  }
  return res;
}
