#include <stdio.h>
FILE *fptr;

int main() {
  // Will be used to keep track of available resources as they are read in 
  int availResources[3] = {10,5,7};
  // Used to keep track of process's resource allocation
  int processes[5][3];
  int maxAlloc[5][3]; 

  // Opening up file and reading data into structs
  ////////////////////////////////////////////////////////////
  fptr = fopen("inputData.txt", "r");
  
  // while not at end of file, read in new lines
  int cnt;
  for(cnt=0; cnt<5; ++cnt){
    char fileArr[20];
    fgets(fileArr, 20, fptr);
    printf("Input Data Line: ");
    printf("%s", fileArr);
    int i = 0;  // tracks index of character array for this line
    int j = 0;  // tracks number of integers read in
    while (j < 6){
      //printf("\n");
      if (j<3 && fileArr[i]>= 48) {
        processes[cnt][j] = (fileArr[i]-48);
        availResources[j] -= (fileArr[i]-48);
        /* // Testing for allocation assignments to processes
        printf("%i", (fileArr[i]-48)); 
        printf("  ");
        */
      }
      else maxAlloc[cnt][j-3] = (fileArr[i]-48);
      if (fileArr[i] == ',' || fileArr[i] == ';') ++j;
      ++i;
    }
  }
  fclose(fptr);
  /* Testing available resources counting
  printf("%i", availResources[0]); printf("/");
  printf("%i", availResources[1]); printf("/");
  printf("%i", availResources[2]); printf("\n");
  */

  // Implementing Banker's Algorithm
  ///////////////////////////////////////////////////////


  printf("Safe sequence: ");
  return 0;
}
