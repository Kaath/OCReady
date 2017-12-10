#include "Segmentation/main.h"
#include "Reseau_de_Neuronne/main.h"

int main(int argc, char const *argv[]) {
  if (argc < 2) {return 1;}
  float **mats = decoupe((char*)argv[1]);

  /*char c = 97;
  for (size_t j = 0; j<100; j++){
    printf("Iteration %zu :\n", j);
    for (size_t i = 0; i<26; i++){
      learn(mats[i], c);
      c += 1;
    }
    c = 97;
  }*/

  for (size_t i = 0; i<26; i++){
    printf("%c->%c\n",(int)i + 97, result(mats[i]));
  }
  /*mats[0][0] = -1;
  printf("space->%c!\n", result(mats[0]));
  mats[0][0] = -2;
  printf("newline->%c!\n", result(mats[0]));*/
  free(mats);
  return 0;
}
