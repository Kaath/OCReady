#include "main.h"

static size_t sizeout = 26;
static size_t sizein = 784;
static size_t HiddenUnits = 100;

char treatment(float output[]){
  size_t x = 0;
  for (size_t i = 0; i<sizeout; i++){
  //  printf("%f  ", output[i]);
    if (output[i] > output[x]){
      x = i;
    }
  }
//  printf("\n");
  return x + 97;
}

float **forward(float weightsInput[], float weightsOutput[], float inputs[]) {
  float *hiddenlayersum = mul(inputs, weightsInput, 1, sizeout, HiddenUnits);
  float *hiddenlayerresult = apply(sigmoid, hiddenlayersum, HiddenUnits);
  float *outputsum = mul(hiddenlayerresult, weightsOutput, 1, HiddenUnits, sizeout);
  float *outputresult = apply(sigmoid, outputsum, sizeout);

  float **forwardresults = malloc(4 * sizeof(float*));
  forwardresults[0] = hiddenlayersum;
  forwardresults[1] = hiddenlayerresult;
  forwardresults[2] = outputsum;
  forwardresults[3] = outputresult;
  return forwardresults;
}


float **backward(float weightsInput[], float weightsOutput[], float LearningRate, float *forwardresults[], size_t HiddenUnits, float inputs[], float output[]){
  float *outputerror = substract(output, forwardresults[3], 1, sizeout);

  float *apforout = apply(sigmoidprime, forwardresults[2], sizeout);
  float *deltaoutputerror = dot(apforout, outputerror, 1, sizeout);

  float *transfor = transpose(forwardresults[1], 1, HiddenUnits);
  float *multransdelta = mul(transfor, deltaoutputerror, HiddenUnits, 1, sizeout);
  float *hiddenoutputchanges = scalar(multransdelta, LearningRate, HiddenUnits, sizeout);

  float *transweiOut = transpose(weightsOutput, HiddenUnits, sizeout);
  float *muldeltranweiOut = mul(deltaoutputerror, transweiOut, 1, sizeout, HiddenUnits);
  float *deltahiddenerror = dot(muldeltranweiOut, apply(sigmoidprime, forwardresults[0], HiddenUnits), 1, HiddenUnits);
  float *multransinde = mul(transpose(inputs, 1, sizein), deltahiddenerror, sizein, 1, HiddenUnits);
  float *inputhiddenchanges = scalar(multransinde, LearningRate, sizein, HiddenUnits);

  weightsInput = add(weightsInput, inputhiddenchanges, sizein, HiddenUnits);
  weightsOutput = add(weightsOutput, hiddenoutputchanges, HiddenUnits, sizeout);

  float **backwardresults = malloc(2 * sizeof(float*));
  backwardresults[0] = weightsInput;
  backwardresults[1] = weightsOutput;

  free(outputerror);
  free(apforout);
  free(deltaoutputerror);
  free(transfor);
  free(multransdelta);
  free(hiddenoutputchanges);
  free(transweiOut);
  free(muldeltranweiOut);
  free(deltahiddenerror);
  free(multransinde);
  free(inputhiddenchanges);
  return backwardresults;
}


void learn(float inputs[], char expectedoutput)
{
  float output[sizeout];
  for (int i = 0; i<(int)sizeout; i++){
    if (i + 97 == expectedoutput){
      output[i] = 1;
    }
    else {
      output[i] = 0;
    }
  }

  float LearningRate = 0.7;
  float weightsInput[sizein*HiddenUnits];
  float weightsOutput[sizeout*HiddenUnits];

  FILE *r = fopen("weightsIn", "rb");
  if (r != NULL) {
      if (fread(weightsInput, sizeof(float), sizein*HiddenUnits, r)){
        fclose(r);
      }
  }

  FILE *r2 = fopen("weightsOut", "rb");
  if (r2 != NULL) {
      if (fread(weightsOutput, sizeof(float), sizeout*HiddenUnits, r2)){
        fclose(r2);
      }
  }
  else{
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < sizeout*HiddenUnits; i++) {
      weightsOutput[i] = (float)rand()/(float)RAND_MAX/4;
    }
    for (size_t i = 0; i < sizein*HiddenUnits; i++) {
      weightsInput[i] = (float)rand()/(float)RAND_MAX/4;
    }
  }

  float** forwardresults = forward(weightsInput, weightsOutput, inputs);

  float** backwardresults = backward(weightsInput, weightsOutput, LearningRate, forwardresults, HiddenUnits , inputs, output);
  for (size_t i = 0; i < sizein*HiddenUnits; i++) {
    if (i < sizeout*HiddenUnits) {
      weightsOutput[i] = backwardresults[1][i];
    }
    weightsInput[i] = backwardresults[0][i];
  }

  FILE *f = fopen("weightsIn", "wb");
  fwrite(weightsInput, sizeof(float), sizein*HiddenUnits, f);
  fclose(f);

  FILE *f2 = fopen("weightsOut", "wb");
  fwrite(weightsOutput, sizeof(float), sizeout*HiddenUnits, f2);
  fclose(f2);
  //printf("%c -> %c\n", result, expectedoutput );
  for (size_t i = 0; i<4; i++){
    free(forwardresults[i]);
    if (i<2) {free(backwardresults[i]);}
  }
}

char result(float inputs[]){
  if (inputs[0] == -1){
    return *" ";
  }
  if (inputs[0] == -2){
    return *"\n";
  }
  float weightsInput[sizein*HiddenUnits];
  float weightsOutput[sizeout*HiddenUnits];

  FILE *r = fopen("weightsIn", "rb");
  if (r != NULL) {
      if (fread(weightsInput, sizeof(float), sizein*HiddenUnits, r)){
        fclose(r);
      }
  }

  FILE *r2 = fopen("weightsOut", "rb");
  if (r2 != NULL) {
      if (fread(weightsOutput, sizeof(float), sizeout*HiddenUnits, r2)){
        fclose(r2);
      }
  }

  float** forwardresults = forward(weightsInput, weightsOutput, inputs);


  return treatment(forwardresults[3]);
}
