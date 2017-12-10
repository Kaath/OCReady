# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "operations.h"

float sigmoid(float x){
  return 1 / (1 + exp(-x));
}


float sigmoidprime(float x){
  return sigmoid(x)*(1-sigmoid(x));
}

float *mul(float inputs[], float weights[], size_t n, size_t m, size_t p){
  float *res = malloc((n*p) * sizeof(float));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < p; j++) {
      res[j + i*p] = 0;
      for (size_t k = 0; k < m; k++) {
        res[j + i*p] += inputs[k + i*m] * weights[j + k*p];
      }
    }
  }
  return res;
}


float *apply(func_t f, float values[], size_t size){
  float *res = malloc(size * sizeof(float));
  for (size_t i = 0; i < size; i++) {
    res[i] = f(values[i]);
  }
  return res;
}


float *substract(float output[] , float outputresult[], size_t lines, size_t cols){
  float *res = malloc((lines*cols) * sizeof(float));
  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < cols; j++) {
      res[j + i*cols] = output[j + i*cols] - outputresult[j + i*cols];
    }
  }
  return res;
}


float *add(float output[] , float outputresult[], size_t lines, size_t cols){
  float *res = malloc((lines*cols) * sizeof(float));
  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < cols; j++) {
      res[j + i*cols] = output[j + i*cols] + outputresult[j + i*cols];
    }
  }
  return res;
}


float *transpose(float mat[], size_t lines, size_t cols){
  float *res = malloc((lines*cols) * sizeof(float));
  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < cols; j++) {
      res[i + j*lines] = mat[j + i*cols];
    }
  }
  return res;
}


float *scalar(float mat[], float LearningRate, size_t lines, size_t cols){
  float *res = malloc((lines*cols) * sizeof(float));
  for (size_t i = 0; i < lines*cols; i++) {
      res[i] = mat[i] * LearningRate;
  }
  return res;
}


float *dot(float prime[] , float error[], size_t lines, size_t cols){
  float *res = malloc((lines*cols) * sizeof(float));
  for (size_t i = 0; i < lines; i++) {
    for (size_t j = 0; j < cols; j++) {
      res[j + i*cols] = prime[j + i*cols] * error[j + i*cols];
    }
  }
  return res;
}
