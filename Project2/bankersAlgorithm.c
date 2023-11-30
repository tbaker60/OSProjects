#include "structs.h"
FILE *fptr;

int main() {
  // Will be used to keep track of available resources as they are read in 
  int availResources[3];
  
  // Opening up file and reading data
  fptr = fopen("inputData.txt", "r");
  char fileArr[100];
  fgets(fileArr, 100, fptr);
  printf("Input Data: ", "%s", fileArr);
  fclose(fptr);

  // Everything else
 
  printf("Safe sequence: ");
  return;
}
