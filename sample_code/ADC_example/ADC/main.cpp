// Author:         Dale Hetherington
// Net ID:         
// Date:
// Assignment:
//
// Description: File description
//----------------------------------------------------------------------//
#include <Arduino.h>
#include <avr/io.h>
#include "adc.h"

int main() {

  initADC7();
  Serial.begin(9600);
  unsigned int result = 0;
  float voltage = 0;

  while(1){
      // print out ADC value
	// read in ADCL first then read ADCH
      result = ADCL;
      result += ((unsigned int) ADCH) << 8;
      voltage = result * (4.72/1024.0);
      Serial.println(voltage);
  }

  return 0;
}
