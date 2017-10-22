# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <err.h>

# include "operations.h"

float **forward(float weightsInput[], float weightsOutput[], float inputs[], size_t HiddenUnits) {
  size_t size = 4*HiddenUnits;
  float *hiddenlayersum = mul(inputs, weightsInput, 4, 2, HiddenUnits);
  float *hiddenlayerresult = apply(sigmoid, hiddenlayersum, size);
  float *outputsum = mul(hiddenlayerresult, weightsOutput, 4, HiddenUnits, 1);
  float *outputresult = apply(sigmoid, outputsum, 4);

  float **forwardresults = malloc(4 * sizeof(float*));
  forwardresults[0] = hiddenlayersum;
  forwardresults[1] = hiddenlayerresult;
  forwardresults[2] = outputsum;
  forwardresults[3] = outputresult;
  return forwardresults;
}


float **backward(float weightsInput[], float weightsOutput[], float LearningRate, float *forwardresults[], size_t HiddenUnits, float inputs[]){
  float expectedoutputs[] = {0,1,1,0};
  float *outputerror = substract(expectedoutputs, forwardresults[3], 4, 1);

  float *apforout = apply(sigmoidprime, forwardresults[2], 4);
  float *deltaoutputerror = dot(apforout, outputerror, 4, 1);

  float *transfor = transpose(forwardresults[1], 4, HiddenUnits);
  float *multransdelta = mul(transfor, deltaoutputerror, HiddenUnits, 4, 1);
  float *hiddenoutputchanges = scalar(multransdelta, LearningRate, 4, 1);

  float *transweiOut = transpose(weightsOutput, HiddenUnits, 1);
  float *muldeltranweiOut = mul(deltaoutputerror, transweiOut, 4, 1, HiddenUnits);
  float *deltahiddenerror = dot(muldeltranweiOut, apply(sigmoidprime, forwardresults[0], 4*HiddenUnits), 4, HiddenUnits);
  float *multransinde = mul(transpose(inputs, 4, 2), deltahiddenerror, 2, 4, HiddenUnits);
  float *inputhiddenchanges = scalar(multransinde, LearningRate, 2, HiddenUnits);

  weightsInput = add(weightsInput, inputhiddenchanges, 2, HiddenUnits);
  weightsOutput = add(weightsOutput, hiddenoutputchanges, HiddenUnits, 1);


  float **backwardresults = malloc(2 * sizeof(float*));
  backwardresults[0] = weightsInput;
  backwardresults[1] = weightsOutput;

  return backwardresults;
}


int main(int argc, char *argv[])
{
  if (argc != 4){
    errx(1, "Wrong number of arguments, %d given, 4 expected", argc);
  }
  else{
    float LearningRate = atof(argv[1]);
    size_t Iterations = (size_t)atoi(argv[2]);
    size_t HiddenUnits = (size_t)atoi(argv[3]);
    float inputs[] = {0,0,0,1,1,0,1,1};
    float weightsInput[2*HiddenUnits];
    float weightsOutput[HiddenUnits];

    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < 2*HiddenUnits; i++) {
      if (i < HiddenUnits) {
        weightsOutput[i] = (float)rand()/(float)RAND_MAX;
      }
      weightsInput[i] = (float)rand()/(float)RAND_MAX;
    }
    for (size_t i = 0; i < Iterations; i++){
      float** forwardresults = forward(weightsInput, weightsOutput, inputs, HiddenUnits);
      float** backwardresults = backward(weightsInput, weightsOutput, LearningRate, forwardresults, HiddenUnits , inputs);
      for (size_t i = 0; i < 2*HiddenUnits; i++) {
        if (i < HiddenUnits) {
            weightsOutput[i] = backwardresults[1][i];
          }
          weightsInput[i] = backwardresults[0][i];
        }
      if ((i%1000 == 999) || (i == 0)) {
        printf("For %zu iterations :\n", i+1);
        printf("Inputs 0,0 -> Output = %f\n", forwardresults[3][0]);
        printf("Inputs 0,1 -> Output = %f\n", forwardresults[3][1]);
        printf("Inputs 1,0 -> Output = %f\n", forwardresults[3][2]);
        printf("Inputs 1,1 -> Output = %f\n\n", forwardresults[3][3]);
      }
    }
  return 0;
  }
}
