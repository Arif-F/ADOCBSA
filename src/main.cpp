#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Servo.h>
#include <Ultrasonic.h>

#define buzzer = 7
#define ledR = 6
#define ledH = 5

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo servo;

float suhu = 2.9;
float rata = 0;
int angle = 10;
int jarak = 0;

const int trigPin = 12;
const int echoPin = 11;
long duration;
int distance;

void setup()
{
  // put your setup code here, to run once:
  servo.attach(8);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, OUTPUT);
  Serial.begin(9600);
  mlx.begin();
  lcd.begin(16, 2);
}

void loop()
{
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  rata = suhu;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(500);
  Serial.println("suhu;");
  Serial.println(suhu = 2.8 + mlx.readObjectTempC());
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("CEK SUHU ANDA");
  lcd.setCursor(0, 1);
  lcd.print("DEKATKAN KEPALA");
  lcd.print(" ");
  lcd.print(suhu, 1);
  lcd.print((char)223);
  lcd.print("C");
  if (distance < 5)
  {
    suhu = 2.9 + mlx.readObjectTempC();
    lcd.setCursor(0, 1);
    lcd.print("SUHU ANDA:");
    lcd.print(suhu, 1);
    lcd.print((char)223);
    lcd.print("");
    lcd.print("C");
    delay(5000);
  }
  if (distance > 5)
  {
    lcd.setCursor(0, 1);
    lcd.print("DEKATKAN KEPALA");
    lcd.print((char)223);
    delay(2000);
  }
}