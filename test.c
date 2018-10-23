#include "test.h"
#include <math.h>
#include <stdlib.h>

BYTE * sieve_factors(int l, BYTE * a, int f) {
  for(int i = f; i < l; i+=f) {
    a[i] = 1;
  }
  return a;
}

BYTE * zero_mem(BYTE * a, int l) {
  for(int i = 0; i<l; i++) {
    a[i] = 0;
  }
  return a;
}

int sieve(int n) {
  int l = n > 5000 ? (int) (1.15 * n * log(n)) : (int) (1.3 * n * log(n) + 10);
  BYTE * nums = malloc(l);
  zero_mem(nums, l);
  int i = 2;
  int curr;
  while(n) {
    while(nums[i]) {
      i++;
    }
    curr = i;
    sieve_factors(l, nums, curr); 
    i++;
    n--;
  }
  free(nums);
  return curr;
}

int main(){
printf("%d\n", sieve(1000000));
return 0;
}
