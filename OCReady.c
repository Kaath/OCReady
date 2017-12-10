#include "Segmentation/main.h"
#include "Reseau_de_Neuronne/main.h"

int main(int argc, char const *argv[]) {
  if (argc < 2) {return 1;}
  int nbcharacters;
  float **mats = decoupe((char*)argv[1], &nbcharacters);


  /*char c = 97;
  int x = 0;
  for (size_t j = 0; j<100; j++){
    printf("Iteration %zu :\n", j);
    for (size_t i = 0; i<26; i++){
      if (learn(mats[i], c)){
        printf("%c\n", c);
        x += 1;
      }
      c += 1;
    }
    printf("%d Success\n", x);
    x = 0;
    c = 97;
  }*/
  for (size_t i = 0; i<26; i++){
    printf("%c->%c\n",(int)i + 97, result(mats[i]));
  }
  return 0;
}
