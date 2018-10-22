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
      next = 2 * num;
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

int lTn(int l) {
  if(l%2 == 0)
    return 5 + 3 * l;
  else
    return 4 + 3 * l;
}

//number to location in arrayThird
int nTl(int n) {
  return (n - 4) / 3;
}

int fastsieve(int targetPrime) {
  //special small stuff
  if(targetPrime < 1)
    return -1;
  if(targetPrime == 1)
    return 2;
  if(targetPrime == 2)
    return 3;
  int locLimit; //onethird of actual limit
  //diff k value for magnitudes SET ZONES??
  if(targetPrime < 1000)
    locLimit = targetPrime * (int)log(targetPrime);
  else if(targetPrime < 1000)
    locLimit = .5 * targetPrime * (int)log(targetPrime);
  else
    locLimit = .4 * targetPrime * (int)log(targetPrime);

  int exit = (int)sqrt(locLimit)/ 1.73; //sqrt 3
  char *arrayThird = calloc(locLimit,sizeof(char));
  int locPrime = 0;//represents number 5
  int size = 3;//5 is the 3rd prime
  for(locPrime; locPrime < exit; locPrime++) {
    if(*(arrayThird + locPrime) == 0) {
      size++;
      int numPrime = lTn(locPrime);
      int locComposite = nTl(numPrime * numPrime);
      //getting incremental rates for multiples of numPrime
      int t = 2 * numPrime;
      int m;
      if((locComposite - locPrime) % 2 == 0) //determines initial increment
	m = numPrime -  (numPrime + 1) / 3;
      else
	m = numPrime +  (numPrime + 1) / 3;
      //removing multiples
      for(locComposite; locComposite < locLimit; locComposite += m) {
	*(arrayThird + locComposite) = 1;
	m = t - m;
      }
    }
  }
  //counting up the rest of primes after sqrtlimit aka exit
  //potential to turn into segmented sieve from here, saves on mem
  for(locPrime; size <= targetPrime;locPrime++)
    if(*(arrayThird + locPrime) == 0)
      size++;
  return  lTn(locPrime - 1);
}

int main(){
  printf("%d\n", fastsieve(1000000));
  return 0;
}
