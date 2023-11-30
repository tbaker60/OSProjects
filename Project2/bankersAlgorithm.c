#include "structs.h"
FILE *fptr;

int main() {
  // Will be used to keep track of available resources as they are read in 
  int availResources[3] = [10,5,7];
  Process *processes[5]; 

  // Opening up file and reading data
  fptr = fopen("inputData.txt", "r");
  int cnt = 0;
  // while not at end of file, read in new lines
  while (!feof(stdin)){
    char fileArr[20];
    fgets(fileArr, 20, fptr);
    printf("Input Data Line: ", "%s", fileArr);
    int i = 0;  // tracks index of character array for this line
    int j = 0;  // tracks number of integers read in
    while (j < 6){
      if (j<3) {
        processes[cnt]->alloc[j];
        availResources[j] -= fileArr[i];
      }
      else processes[cnt]->maxAlloc[j-3];
      if (fileArr[i] == ',' || fileArr[i] == ';') ++j;
      ++i;
    }
    ++cnt;  // incrementing line counter. Each input line is process data
  }
  fclose(fptr);

  // Everything else
 
  printf("Safe sequence: ");
  return;
}
