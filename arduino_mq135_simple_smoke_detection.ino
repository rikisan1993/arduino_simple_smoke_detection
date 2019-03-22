#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);

int sensor_val;
int sensor_pin = 0;
int led_pin = 12;
int buzzer_pin = 13;
int delay_time = 1500;
int serial_frequency = 9600;
int limit_PPM = 99;
  
// initial setup, run once
void setup(){ 
  pinMode(led_pin, OUTPUT); 
  pinMode(buzzer_pin, OUTPUT);
  Serial.begin(serial_frequency);
  lcd.begin(16, 2);
  lcd.init(); 
  lcd.backlight();
}

// main program
void loop(){
  sensor_val = analogRead(sensor_pin); 
  printSerial(sensor_val);
  printLCD(sensor_val);
  controlLED(sensor_val);
  controlBuzzer(sensor_val);
  delay(delay_time);                                   
}

void printLCD(int value){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("kadar CO: ");
  lcd.setCursor(10,0);
  lcd.print(value, DEC);
  lcd.print("PPM");

  if(value > limit_PPM){
    lcd.setCursor(2,1);
    lcd.print("NO SMOKING!!");
  } else {
    lcd.setCursor(3,1);
    lcd.print("SMOKE-FREE");
  }
  
}

void printSerial(int value) {
  Serial.print("Air Quality : ");
  Serial.print(value, DEC);               
  Serial.println(" PPM");
}

void controlLED(int value) {
  if(value > limit_PPM) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }  
}

void controlBuzzer(int value) {
  if(value > limit_PPM) {
    tone(buzzer_pin, 2500, 500);
  } else {
    noTone(buzzer_pin);
  }
}
