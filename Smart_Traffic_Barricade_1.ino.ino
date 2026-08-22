#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,16,2);

Servo s1, s2;

int red = 6;
int yellow = 7;
int green = 8;
int ir = 2;

void setup() {

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(ir, INPUT);

  s1.attach(11);
  s2.attach(12);

  lcd.init();
  lcd.backlight();

  s1.write(0);
  s2.write(0);

  // START 8 sec
  digitalWrite(red,1);
  digitalWrite(yellow,1);
  digitalWrite(green,1);

  lcd.setCursor(0,0);
  lcd.print("Welcome-");

  String t = "Team Vector Visionaries ";

  for(int i=0;i<t.length()-16;i++){
    lcd.setCursor(0,1);
    lcd.print(t.substring(i,i+16));
    delay(300);
  }

  digitalWrite(red,0);
  digitalWrite(yellow,0);
  digitalWrite(green,0);
}

void loop() {

  // 🔴 RED (10 sec)
  digitalWrite(red,1);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Vehicles Stopped");
  lcd.setCursor(0,1);
  lcd.print("Pedestrian Pass");

  delay(10000);

  digitalWrite(red,0);

  // 🟡 YELLOW (3 sec + servo 0→90)
  digitalWrite(yellow,1);

  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Be Aware");

  for(int p=0;p<=90;p++){

    s1.write(p);
    s2.write(p);

    if(digitalRead(ir)==LOW){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Obstacle Found");
      lcd.setCursor(0,1);
      lcd.print("Move Away!");
    }

    delay(33); // ~3 sec
  }

  digitalWrite(yellow,0);

  // 🟢 GREEN (12 sec)
  digitalWrite(green,1);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Vehicles  Pass");
  lcd.setCursor(0,1);
  lcd.print("Pedestrian Stop");

  delay(12000);

  digitalWrite(green,0);

  // 🟡 FINAL YELLOW (2 sec + servo 90→0)
  digitalWrite(yellow,1);

  for(int p=90;p>=0;p--){

    s1.write(p);
    s2.write(p);

    if(digitalRead(ir)==LOW){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Obstacle Found");
      lcd.setCursor(0,1);
      lcd.print("Move Away!");
    }

    delay(22); // ~2 sec
  }

  digitalWrite(yellow,0);
}