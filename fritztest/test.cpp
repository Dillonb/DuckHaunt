#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <wiringPi.h>

// gpio load i2c //load i2c drivers into kernal
// gcc -Wall -o test test.c -lwiringPi
// sudo ./test

int main (void){
  wiringPiSetup () ;
  pinMode (1, OUTPUT) ;
  for (;;){
  	printf("loop\n");
    digitalWrite (1, HIGH) ; delay (500) ;
    digitalWrite (1,  LOW) ; delay (500) ;
  }
  return 0 ;
}