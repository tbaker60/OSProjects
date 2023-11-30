struct Process {
// Arrays for storing allocation values
// first index is allocations for A, second is B, etc.
  int alloc[3];
  int maxAlloc[3];
  
};

struct Resource {
  int count;
  int max;
};
