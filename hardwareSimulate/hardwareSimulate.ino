//DFRobot.com
//Compatible with the Arduino IDE 1.0
//Library version:1.1


#include <Wire.h>
#include <stdlib.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

void setup(){
  Serial.begin(115200); //initial the Serial
  lcd.init();           // initialize the lcd 
  lcd.backlight();
  
  lcd.home();
  
  lcd.print("DEVICE READY");
}

String inMsg = "";
bool incoming = false;

void loop(){

  //loading incoming command
  if(Serial.available()){
      char x = Serial.read();
      inMsg += x;
      incoming = true;
  }
  delay(10);
  if(incoming && Serial.available() <= 0) {
    Serial.println(inMsg + " ACK!");
    showMsg(inMsg);
    String ack = inMsg + " Received";
    incoming = false;
    inMsg = "";
  }
}

void showMsg(String msg) {
  String outMsg = String(testResult());
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("OBJ: " + msg);
  lcd.setCursor(0,1);
  lcd.print("TESTING...");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(msg);
  lcd.setCursor(0,1);
  lcd.print(outMsg + " mg/kg");
  Serial.println(msg + ": " + outMsg + "mg/kg");
}

long testResult() {
  return random(0,3000);
}

