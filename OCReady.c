#include "Segmentation/main.h"
#include "Reseau_de_Neuronne/main.h"

int main(int argc, char const *argv[]) {
  if (argc < 2) {return 1;}
  int nbcharacters;
  float **mats = decoupe((char*)argv[1], &nbcharacters);


/*  char c = 97;
  for (size_t j = 0; j<10; j++){
    for (int i = 0; i<nbcharacters; i++){
      if (mats[i][0] != -2){
        learn(mats[i], c);
        c += 1;
      }
    }
    c = 97;
  }*/

  for (int i = 0; i<nbcharacters; i++){
    printf("%c-\n", result(mats[i]));
  }
  free(mats);
  return 0;
}
