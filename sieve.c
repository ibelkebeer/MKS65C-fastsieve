#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sieve.h"

int potentialPrime(int i){
  if(i % 2 == 0){
    return 5 + 3 * i;
  }
  return 4 + 3 * i;
}

int ptoi(int i){
  return (i-4) / 3;
}

int sieve(int targetPrime){
  if(!(targetPrime ^ 1)){
    return 2;
  }
  if(!(targetPrime ^ 2)){
    return 3;
  }
  int len;
  if(targetPrime < 1000){
    len = .5 * targetPrime * (int)log(targetPrime);
  }else{
    len = .4 * targetPrime * (int)log(targetPrime);
  }
  int* cur = calloc(len / 32, sizeof(int));
  int index = 0;
  int i = 3;
  int num;
  int square;
  int next;
  int range;
  int limit = (int)sqrt(len) / 1.73;
  while(index < limit){
    if(!(cur[index / 32] & (1 << (index & 31)))){
      num = potentialPrime(index);
      square = ptoi(num * num);
      next = num << 1;
      if((square - index) & 1){
        range = num + (num+1) / 3;
      }else{
        range = num - (num+1) / 3;
      }
      while(square < len){
        cur[square / 32] |= (1 << (square & 31));
        range = next - range;
        square += range;
      }
      i++;
    }
    index++;
  }
  while(i ^ targetPrime){
    if(!(cur[index / 32] & (1 << (index & 31)))){
      i++;
    }
    index++;
  }
  while(cur[index / 32] & (1 << (index & 31))){
    index++;
  }
  return potentialPrime(index);
}

int main(){
  printf("%d\n", sieve(1000000));
  return 0;
}
