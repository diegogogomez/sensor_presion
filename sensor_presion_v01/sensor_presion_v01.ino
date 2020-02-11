#include "HX711.h"
HX711 loadcell;
const int LOADCELL_DOUT_PIN = A1;
const int LOADCELL_SCK_PIN = A0;
float outputValue = 0;

unsigned long calibracion = 0;
volatile unsigned long presion = 0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadcell.set_scale();
  loadcell.set_offset();
  
  for(int i = 0; i < 100; i ++){
    calibracion += loadcell.get_units(10);
    delay(10);
  }  
  calibracion /= 100;
}

void loop() {
  presion = loadcell.get_units() - calibracion;
  outputValue = mapfloat(presion, 0, 0xFFFFFF, 0, 40) * 10.1972;
  Serial.print(outputValue);
  Serial.print(" ");
  Serial.println(outputValue);
  delay(10);
}

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
 return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}
