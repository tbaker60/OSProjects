#include <stdio.h>
#include <stdbool.h>
FILE *fptr;
const int n = 5;  // num of processes
const int m = 3;  // num of resources

int main() {
  // Will be used to keep track of available resources as they are read in 
  int availResources[3] = {10,5,7};
  // Used to keep track of processes' resource allocation
  int procAlloc[n][m];
  int maxAlloc[n][m]; 

  // Opening up file and reading data into structs
  ////////////////////////////////////////////////////////////
  fptr = fopen("inputData.txt", "r");
  
  // while not at end of file, read in new lines
  for(int cnt=0; cnt<n; ++cnt){ // cnt tracks which process/line of input file we're on
    char fileArr[20];
    fgets(fileArr, 20, fptr);
    //printf("Input Data Line: ");
    //printf("%s", fileArr);
    int i = 0;  // tracks index of character array for this line
    int j = 0;  // tracks number of integers read in

    while (j < (2*m)){  // while reading a number less than the width of the matrix(2*m)
      //printf("\n");
      if (j<m && fileArr[i]>= 48) { // if reading from first half of the input line (actual allocation data)
        procAlloc[cnt][j] = (fileArr[i]-48);  // populate process's allocation data
        availResources[j] -= (fileArr[i]-48); // decrease availability based on what is being used

        /* // Testing for allocation assignments to processes
        printf("%i", (fileArr[i]-48)); 
        printf("  ");
        */
      }
      // else reading from second half of input line (max allocation data)
      else maxAlloc[cnt][j-m] = (fileArr[i]-48);

      if (fileArr[i] == ',' || fileArr[i] == ';') ++j;  // if reading a delimiter, increment j to signify we're on a new piece of data
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
  int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }
    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            need[i][j] = maxAlloc[i][j] - procAlloc[i][j];
    }
    int y = 0;
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
 
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > availResources[j]){
                        flag = 1;
                         break;
                    }
                }
 
                if (flag == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++)
                        availResources[y] += procAlloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }
   
      bool safe = true;
       
      for(int i=0;i<n;i++)
    {
      if(f[i] == 0)
      {
        safe = false;
         printf("This system is not safe\n");
        break;
      }
    }
     
      if(safe == true)
    {
      printf("Safe sequence: ");
      for (int i = 0; i < n - 1; i++)
        printf(" P%d ->", ans[i]);
      printf(" P%d", ans[n - 1]);
      printf("\n");
    }

  return 0;
}
