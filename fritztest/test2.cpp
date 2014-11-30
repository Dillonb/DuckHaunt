#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <wiringPi.h>

// gpio load i2c //load i2c drivers into kernal
// g++ -Wall -o test test2.cpp -lwiringPi && sudo ./test

int main (void){
  wiringPiSetup ();
  pinMode (0, INPUT);
  pinMode (1, OUTPUT);
  for(;;){
    if ( digitalRead(0) ){
      digitalWrite (1,  HIGH) ; delay (500) ;
      digitalWrite (1,  LOW) ;
    }
  }
  return 0 ;
}