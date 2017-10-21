# include <stdio.h>
# include <stdlib.h>

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
  float expectedoutputs[4] = {0,1,1,0};
  float *outputerror = substract(expectedoutputs, forwardresults[3], 4, 1);

  float *apforout = apply(sigmoidprime, forwardresults[2], 4);
  float *deltaoutputerror = dot(apforout, outputerror, 4, 1);

  float *transfor = transpose(forwardresults[1], 4, HiddenUnits);
  float *multransdelta = mul(transfor, deltaoutputerror, HiddenUnits, 4, 1);
  float *hiddenoutputchanges = scalar(multransdelta, LearningRate, 4, 1);

  float *transweiOut = transpose(weightsOutput, HiddenUnits, 1);
  float *muldeltranweiOut = mul(deltaoutputerror, transweiOut, 4, 1, HiddenUnits);
  float *deltahiddenerror = dot(muldeltranweiOut, apply(sigmoidprime, forwardresults[0], 4*HiddenUnits), 4, HiddenUnits);
  float *inputhiddenchanges = scalar(mul(transpose(inputs, 8, 2), deltahiddenerror, 2, 4, HiddenUnits), LearningRate, 2, 1);

  weightsInput = add(weightsInput, inputhiddenchanges, 2, HiddenUnits); //est-ce que ça marche? pas sur
  weightsOutput = add(weightsOutput, hiddenoutputchanges, HiddenUnits, 1);

  float **backwardresults = malloc(2 * sizeof(float*));
  backwardresults[0] = deltahiddenerror;
  backwardresults[1] = deltaoutputerror;
  return backwardresults;
}


int main(int argc, char *argv[])
{
  float LearningRate = atof(argv[0]);
  size_t Iterations = (size_t)argv[1];
  size_t HiddenUnits = (size_t)argv[2];
  float inputs[8] = {0,0,0,1,1,0,1,1};
  float weightsInput[2*HiddenUnits]; // mettre des valeurs flottantes random entre 0 et 1
  float weightsOutput[HiddenUnits]; // mettre des valeurs flottantes random entre 0 et 1

  for (size_t i = 0; i < Iterations; i++){
    float** forwardresults = forward(weightsInput, weightsOutput, inputs, HiddenUnits); //Vérifier que les weights sont bien en reference et seront modifiés
    float** backwardresults = backward(weightsInput, weightsOutput, LearningRate, forwardresults, HiddenUnits , inputs);
    // ajouter ce qu'on veut print pendant la soutenance, genre le résultat pour chaque input à chaque itération et l'écart du résultat optenu.
  }


  return 0;
}
