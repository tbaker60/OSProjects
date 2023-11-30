#include <stdio.h>
#include <stdbool.h>
FILE *fptr;
const int n = 5;  // num of processes
const int m = 3;  // num of resources

int main() {
  // Will be used to keep track of available resources as they are read in 
  int availResources[m] = {10,5,7};
  // Used to keep track of process's resource allocation
  int processes[n][m];
  int maxAlloc[n][m]; 

  // Opening up file and reading data into structs
  ////////////////////////////////////////////////////////////
  fptr = fopen("inputData.txt", "r");
  
  // while not at end of file, read in new lines
  for(int cnt=0; cnt<n; ++cnt){
    char fileArr[20];
    fgets(fileArr, 20, fptr);
    printf("Input Data Line: ");
    printf("%s", fileArr);
    int i = 0;  // tracks index of character array for this line
    int j = 0;  // tracks number of integers read in
    while (j < (2*m)){
      //printf("\n");
      if (j<m && fileArr[i]>= 48) {
        processes[cnt][j] = (fileArr[i]-48);
        availResources[j] -= (fileArr[i]-48);
        /* // Testing for allocation assignments to processes
        printf("%i", (fileArr[i]-48)); 
        printf("  ");
        */
      }
      else maxAlloc[cnt][j-m] = (fileArr[i]-48);
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
  int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (k = 0; k < 5; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
 
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]){
                        flag = 1;
                         break;
                    }
                }
 
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
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
         printf("The following system is not safe");
        break;
      }
    }
     
      if(safe == true)
    {
      printf("Safe sequence: ");
      for (i = 0; i < n - 1; i++)
        printf(" P%d ->", ans[i]);
      printf(" P%d", ans[n - 1]);
    }





  
  return 0;
}
