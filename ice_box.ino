

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int Relayled = 2;                 // IN1
int Relaypeltier = 3;                 // IN2
int Relayfan = 4;                 // IN3
int doorsensor = 7;
int tmpin = 2;
int tmpout= 1;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

float readingin;
float readingout;
float voltagein;
float tempin;
float voltageout;
float tempout;
float fvaluein;
float fvalueout;
float sensitivity = 0.1;
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET LED_BUILTIN//4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

void setup() {
  pinMode(Relayled,OUTPUT);     
  pinMode(Relaypeltier,OUTPUT);  
  pinMode(Relayfan,OUTPUT);
  pinMode(doorsensor,INPUT);
  readingin = analogRead(tmpin);
  fvaluein = readingin;
  readingout = analogRead(tmpout);
  fvalueout =readingout;
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("made by");
  display.setTextSize(2);
  display.setCursor(0,20);
  display.println("CodeMakers");
  display.setTextSize(1);
  display.setCursor(0,50);
  display.println("2020/7 minsung");
  display.display();
  delay(2000);
  digitalWrite (Relayled,HIGH);//off
  digitalWrite (Relaypeltier,HIGH);
  digitalWrite (Relayfan,HIGH);
}

void loop() {
  boolean dooropen = digitalRead(doorsensor);

  
  readingin = analogRead(tmpin);
  fvaluein = fvaluein*(1-sensitivity)+readingin*sensitivity;
  voltagein = fvaluein * 5.0/1024.0;
  tempin = (voltagein-0.5)*100;
  
  int tempinm = tempin;
  
  readingout = analogRead(tmpout);  
  fvalueout = fvalueout*(1-sensitivity)+readingout*sensitivity;
  voltageout = fvalueout * 5.0/1024.0;
  tempout = (voltageout-0.5)*100;
  
  int tempoutm = tempout;
 
  if(dooropen == 0){
    digitalWrite(Relayled,LOW);
    mprint(2," DOOR OPEN");
  }
  else
  { 
    display.clearDisplay();
    display.setTextColor(WHITE);
   if(tempin<=0){
    digitalWrite(Relaypeltier,HIGH);
    display.setTextSize(1);
    display.setCursor(50,0);
    display.println("REACHED");
    }
   else{    
    if(tempout>55){
      digitalWrite(Relaypeltier,HIGH);
      delay(30000);
    }
    else digitalWrite(Relayfan,LOW);
    
    digitalWrite(Relaypeltier,LOW);
    display.setTextSize(1);
    display.setCursor(5,0);
    display.println("COOLING DOWN");
    }

    display.setTextSize(1);
    display.setCursor(0,35);
    display.println("IN:");
    display.setTextSize(2);
    display.setCursor(20,30);
    display.println(tempinm);
    display.setTextSize(1);
    display.setCursor(45,35);
    display.println("C");
    display.setTextSize(1);
    display.setCursor(60,35);
    display.println("OUT:");
    display.setTextSize(2);
    display.setCursor(83,30);
    display.println(tempoutm);
    display.setTextSize(1);
    display.setCursor(108,35);
    display.println("C");
    display.display();
    digitalWrite(Relayled,HIGH);
  }
}
void mprint(int a,char *m)
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(a);
  display.setCursor(0,0);
  display.println(m);
  display.display();
}
