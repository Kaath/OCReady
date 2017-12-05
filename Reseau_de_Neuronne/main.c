# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <err.h>

# include "operations.h"

void print_matrix(float mat[], size_t lines, size_t cols)
{
  for (size_t i = 0; i<lines; i++)
  {
    for (size_t j = 0; j<cols; j++)
    {
      printf("%.4f   ", mat[i*cols +j]);
    }
    printf("\n");
  }
  printf("\n");
}

float **forward(float weightsInput[], float weightsOutput[], float inputs[], size_t HiddenUnits) {
  size_t size = HiddenUnits;
  float *hiddenlayersum = mul(inputs, weightsInput, 1, 10, HiddenUnits);
  float *hiddenlayerresult = apply(sigmoid, hiddenlayersum, size);
  float *outputsum = mul(hiddenlayerresult, weightsOutput, 1, HiddenUnits, 10);
  float *outputresult = apply(sigmoid, outputsum, 10);

  float **forwardresults = malloc(4 * sizeof(float*));
  forwardresults[0] = hiddenlayersum;
  forwardresults[1] = hiddenlayerresult;
  forwardresults[2] = outputsum;
  forwardresults[3] = outputresult;
  return forwardresults;
}


float **backward(float weightsInput[], float weightsOutput[], float LearningRate, float *forwardresults[], size_t HiddenUnits, float inputs[]){
  float expectedoutputs[] = {1,0,1,0,1};
  float *outputerror = substract(expectedoutputs, forwardresults[3], 1, 5);

  float *apforout = apply(sigmoidprime, forwardresults[2], 5);
  float *deltaoutputerror = dot(apforout, outputerror, 1, 5);

  float *transfor = transpose(forwardresults[1], 1, HiddenUnits);
  float *multransdelta = mul(transfor, deltaoutputerror, HiddenUnits, 1, 5);
  float *hiddenoutputchanges = scalar(multransdelta, LearningRate, HiddenUnits, 1);

  float *transweiOut = transpose(weightsOutput, HiddenUnits, 5);
  float *muldeltranweiOut = mul(deltaoutputerror, transweiOut, 1, 5, HiddenUnits);
  float *deltahiddenerror = dot(muldeltranweiOut, apply(sigmoidprime, forwardresults[0], HiddenUnits), 1, HiddenUnits);
  float *multransinde = mul(transpose(inputs, 1, 10), deltahiddenerror, 10, 1, HiddenUnits);
  float *inputhiddenchanges = scalar(multransinde, LearningRate, 10, HiddenUnits);

  weightsInput = add(weightsInput, inputhiddenchanges, 10, HiddenUnits);
  weightsOutput = add(weightsOutput, hiddenoutputchanges, HiddenUnits, 5);


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
    float inputs[] = {1,0,0,0,0,0,0,0};
    float weightsInput[10*HiddenUnits];
    float weightsOutput[5*HiddenUnits];

    FILE *r = fopen("weightsIn", "rb");
    if (r != NULL) {
        fread(weightsInput, sizeof(float), 10*HiddenUnits, r);
        fclose(r);
        printf("file 1 read\n");
    }

    FILE *r2 = fopen("weightsOut", "rb");
    if (r2 != NULL) {
        fread(weightsOutput, sizeof(float), 5*HiddenUnits, r2);
        fclose(r2);
        printf("file 2 read\n");
    }
    
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < 10*HiddenUnits; i++) {
      weightsOutput[i] = (float)rand()/(float)RAND_MAX;
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
        printf("Inputs 1,1 -> Output = %f\n", forwardresults[3][3]);
        printf("Inputs 1,1 -> Output = %f\n\n", forwardresults[3][4]);

      }
    }

  FILE *f = fopen("weightsIn", "wb");
  fwrite(weightsInput, sizeof(float), 10*HiddenUnits, f);
  fclose(f);

  FILE *f2 = fopen("weightsOut", "wb");
  fwrite(weightsOutput, sizeof(float), 5*HiddenUnits, f2);
  fclose(f2);
  return 0;
  }
}
