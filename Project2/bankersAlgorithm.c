FILE *fptr;

int main() {

  fptr = fopen("inputData.txt", "r");
  char fileArr[100];
  fgets(fileArr, 100, fptr);
  printf("Input Data: ", "%s", fileArr);
  fclose(fptr);
  printf("Safe sequence: ");
  return;
}
