#include "Segmentation/main.h"
#include "Reseau_de_Neuronne/main.h"

int main(int argc, char const *argv[]) {
  if (argc < 2) {return 1;}
  float **mats = decoupe((char*)argv[1]);
  //learn(mats[0],'a');
  return 0;
}
