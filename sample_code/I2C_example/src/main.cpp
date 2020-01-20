#include <Arduino.h>
#include "i2c.h"


int main() {

//Serial.begin(9600);
initI2C();
//Serial.println("I finished init");
sei();

while(1){
sendDataI2C(0x1A, 0x0F);
//_delay_ms(10);

}
return 0;
}