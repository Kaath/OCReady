# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <err.h>

# include "operations.h"

char treatment(float output[]){
  size_t x = 0;
  for (size_t i = 0; i<26; i++){
    if (output[i] > output[x]){
      x = i;
    }
  }
  return x + 97;
}

float **forward(float weightsInput[], float weightsOutput[], float inputs[], size_t HiddenUnits) {
  size_t size = HiddenUnits;
  float *hiddenlayersum = mul(inputs, weightsInput, 1, 784, HiddenUnits);
  float *hiddenlayerresult = apply(sigmoid, hiddenlayersum, size);
  float *outputsum = mul(hiddenlayerresult, weightsOutput, 1, HiddenUnits, 26);
  float *outputresult = apply(sigmoid, outputsum, 26);

  float **forwardresults = malloc(4 * sizeof(float*));
  forwardresults[0] = hiddenlayersum;
  forwardresults[1] = hiddenlayerresult;
  forwardresults[2] = outputsum;
  forwardresults[3] = outputresult;
  return forwardresults;
}


float **backward(float weightsInput[], float weightsOutput[], float LearningRate, float *forwardresults[], size_t HiddenUnits, float inputs[], float output[]){
  float *outputerror = substract(output, forwardresults[3], 1, 26);

  float *apforout = apply(sigmoidprime, forwardresults[2], 26);
  float *deltaoutputerror = dot(apforout, outputerror, 1, 26);

  float *transfor = transpose(forwardresults[1], 1, HiddenUnits);
  float *multransdelta = mul(transfor, deltaoutputerror, HiddenUnits, 1, 26);
  float *hiddenoutputchanges = scalar(multransdelta, LearningRate, HiddenUnits, 1);

  float *transweiOut = transpose(weightsOutput, HiddenUnits, 26);
  float *muldeltranweiOut = mul(deltaoutputerror, transweiOut, 1, 26, HiddenUnits);
  float *deltahiddenerror = dot(muldeltranweiOut, apply(sigmoidprime, forwardresults[0], HiddenUnits), 1, HiddenUnits);
  float *multransinde = mul(transpose(inputs, 1, 784), deltahiddenerror, 784, 1, HiddenUnits);
  float *inputhiddenchanges = scalar(multransinde, LearningRate, 784, HiddenUnits);

  weightsInput = add(weightsInput, inputhiddenchanges, 784, HiddenUnits);
  weightsOutput = add(weightsOutput, hiddenoutputchanges, HiddenUnits, 26);

  float **backwardresults = malloc(2 * sizeof(float*));
  backwardresults[0] = weightsInput;
  backwardresults[1] = weightsOutput;

  return backwardresults;
}


int learn(float inputs[], char expectedoutput)
{
  float output[26];
  for (int i = 0; i<26; i++){
    if (i + 97 == expectedoutput){
      output[i] = 1;
    }
    else {
      output[i] = 0;
    }
  }

  float LearningRate = 0.7;
  size_t HiddenUnits = 50;
  float weightsInput[784*HiddenUnits];
  float weightsOutput[26*HiddenUnits];

  FILE *r = fopen("weightsIn", "rb");
  if (r != NULL) {
      if (fread(weightsInput, sizeof(float), 784*HiddenUnits, r)){
        fclose(r);
        printf("file 1 read\n");
      }
  }

  FILE *r2 = fopen("weightsOut", "rb");
  if (r2 != NULL) {
      if (fread(weightsOutput, sizeof(float), 26*HiddenUnits, r2)){
        fclose(r2);
        printf("file 2 read\n");
      }
  }
  else{
      srand((unsigned int)time(NULL));

      for (size_t i = 0; i < 26*HiddenUnits; i++) {
        weightsOutput[i] = (float)rand()/(float)RAND_MAX;
      }
      for (size_t i = 0; i < 784*HiddenUnits; i++) {
        weightsInput[i] = (float)rand()/(float)RAND_MAX;
      }
  }

  float** forwardresults = forward(weightsInput, weightsOutput, inputs, HiddenUnits);
  char result = treatment(forwardresults[3]);

  float** backwardresults = backward(weightsInput, weightsOutput, LearningRate, forwardresults, HiddenUnits , inputs, output);
  for (size_t i = 0; i < 784*HiddenUnits; i++) {
    if (i < 26*HiddenUnits) {
      weightsOutput[i] = backwardresults[1][i];
    }
    weightsInput[i] = backwardresults[0][i];
  }
  free(forwardresults);
  free(backwardresults);
  FILE *f = fopen("weightsIn", "wb");
  fwrite(weightsInput, sizeof(float), 10*HiddenUnits, f);
  fclose(f);

  FILE *f2 = fopen("weightsOut", "wb");
  fwrite(weightsOutput, sizeof(float), 5*HiddenUnits, f2);
  fclose(f2);

  return result==expectedoutput;
}

char result(float inputs[]){
  size_t HiddenUnits = 50;
  float weightsInput[784*HiddenUnits];
  float weightsOutput[26*HiddenUnits];

  FILE *r = fopen("weightsIn", "rb");
  if (r != NULL) {
      if (fread(weightsInput, sizeof(float), 784*HiddenUnits, r)){
        fclose(r);
        printf("file 1 read\n");
      }
  }

  FILE *r2 = fopen("weightsOut", "rb");
  if (r2 != NULL) {
      if (fread(weightsOutput, sizeof(float), 26*HiddenUnits, r2)){
        fclose(r2);
        printf("file 2 read\n");
      }
  }

  float** forwardresults = forward(weightsInput, weightsOutput, inputs, HiddenUnits);
  return treatment(forwardresults[3]);
  free(forwardresults);
}
