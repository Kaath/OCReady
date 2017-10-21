# include <stdio.h>
# include <stdlib.h>

# include "operations.h"
# include "main.h"


float *forward(float weightsInput[], float weightsOutput[], float inputs[], size_t HiddenUnits){
  size_t = 4*HiddenUnits;
  float hiddenlayersum[size] = mul(inputs, weightsInput, 4, 2, HiddenUnits);
  float hiddenlayerresult[size] = apply(sigmoid, hiddenlayersum, size);
  float outputsum[4] = mul(hiddenlayerresult, weightsOutput, 4, HiddenUnits, 1);
  float outputresult[4] = apply(sigmoid, outputsum, 4);

  float *forwardresults[4] = {hiddenlayersum, hiddenlayerresult, outputsum, outputresult};
  return forwardresults;
}


float *backward(float weightsInput[], float weightsOutput[], float LearningRate, float forwardresults[], size_t HiddenUnits, float inputs[]){
  float expectedoutputs[4] = {0,1,1,0};
  float outputerror[4] = substract(expectedoutputs, *forwardresults[3], 4, 1);
  float deltaoutputerror = dot(apply(prime, *forwardresults[2], 4), outputerror, 4, 1);
  float hiddenoutputchanges = scalar(multiply(transpose(forwardresults[1], 4, HiddenUnits), deltaoutputerror, HiddenUnits, 4, 1), LearningRate);
  float deltahiddenerror = dot(multiply(deltaoutputerror, transpose(weightsOutput, HiddenUnits, 1), 4, 1, HiddenUnits), sigmoidprime(*forwardresults[0], 4*HiddenUnits), 4, HiddenUnits);
  float inputhiddenchanges = scalar(multiply(transpose(inputs, 8), deltahiddenerror, 2, 4, HiddenUnits), LearningRate);

  weightsInput = add(weightsInput, inputhiddenchanges, 2, HiddenUnits); //est-ce que ça marche? pas sur
  weightsOutput = add(weightsOutput, hiddenoutputchanges, HiddenUnits, 1);

  float *backwardresults[2] = {deltahiddenerror, deltaoutputerror};
  }
}


int main(int argc, char *argv[])
{
  float LearningRate = argv[0];
  size_t Iterations = argv[1];
  size_t HiddenUnits = argv[2];
  float inputs[8] = {0,0,0,1,1,0,1,1};
  float weightsInput[2*HiddenUnits]; // mettre des valeurs flottantes random entre 0 et 1
  float weightsOutput[HiddenUnits]; // mettre des valeurs flottantes random entre 0 et 1

  for (size_t i = 0; i < Iterations; i++){
    float* forwardresults = forward(weightsInput, weightsOutput, inputs, HiddenUnits); //Vérifier que les weights sont bien en reference et seront modifiés
    float* backwardresults = backward(weightsInput, weightsOutput, LearningRate, forwardresults, HiddenUnits , inputs);
    // ajouter ce qu'on veut print pendant la soutenance, genre le résultat pour chaque input à chaque itération et l'écart du résultat optenu.
  }

  return 0;
}
