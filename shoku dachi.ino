#include <LedControl.h> //including 8x8 LED library
#define PHOTORESISTOR_PIN A1 //defining photoresistor pin into input Analog 1


//button
const int waterPin = 9; //defining water button into digital input 9
const int lightPin = 10; //defining light button into digital input 10


// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status


//Sensor Code


int sensor; //soil moisture sensor output
int luminosity; //photoresistor output
int hum; //humidity remapped number
int lum; //luminosity remapped number
const int powerpin = 8; //defining soil moisture sensor powerpin into digital input 8
const int delayTime = 1000; //delay between sensor reading



//8x8 LED Display


int DIN = 5; //data input into digital input 5
int CS = 4; //chip select into digital input 4
int CLK = 3; //clock input into digital input 3
LedControl lc(DIN, CLK, CS, 1); //defining LED control


byte happy[8] = {0x00,0x00,0x42,0xa5,0x00,0x42,0x3c,0x00}; //hex for happy face in 8x8 LED Monitor
byte water[8] = {0x00,0x00,0x00,0xe7,0x81,0x81,0x99,0x24}; //hex for need water face in 8x8 LED Monitor
byte light[8] = {0x00,0x00,0x00,0x24,0xc3,0x00,0x18,0x24}; //hex for need light face in 8x8 LED Monitor
byte dead[8] = {0x00,0x00,0xa5,0x42,0xa5,0x00,0x3c,0x00}; //hex for need water and light face in 8x8 LED Monitor
byte glare[8] = {0x00,0x00,0xff,0xff,0x66,0x00,0x0e,0x00}; //hex for too much light
byte throwup[8] = {0x00,0xa5,0x42,0xa5,0x00,0x3c,0x3c,0x3c}; //hex for too much water
byte waterzero[8] = {0x18,0x18,0x24,0x24,0x42,0x42,0x42,0x3c}; //hex for critical water in 8x8 LED Monitor
byte waterhalf[8] = {0x18,0x18,0x24,0x24,0x42,0x7e,0x7e,0x3c}; //hex for decent water in 8x8 LED Monitor
byte waterfull[8] = {0x18,0x18,0x3c,0x3c,0x7e,0x7e,0x7e,0x3c}; //hex for healthy water in 8x8 LED Monitor
byte lightzero[8] = {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80}; //hex for critical light in 8x8 LED Monitor
byte lighthalf[8] = {0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0}; //hex for decent light in 8x8 LED Monitor
byte lightfull[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}; //hex for healthy light in 8x8 LED Monitor



//setup for soil moisture sensor
void setup1()
{
  pinMode (powerpin, OUTPUT);
}


void loop1()
{
  digitalWrite(powerpin,HIGH); //turn sensor ON
  delay(10); //short delay
  sensor = analogRead(A0); //read sensor
  hum = map(sensor, 0, 550, 1, 4); //mapping soil moisture sensor
  digitalWrite(powerpin,LOW); //turn sensor OFF
  Serial.println(hum); //print reading
  delay(delayTime); //wait until next reading
}


//setup 2 for luminosity
void setup2()
{
  pinMode (luminosity, INPUT);
}


//loop 2 for luminosity
void loop2()
{
  luminosity = analogRead(PHOTORESISTOR_PIN);
  lum = map(luminosity, 0, 800, 1, 4);
  Serial.println(lum);
  delay(delayTime);
}


//setup for LED
void setup3()
{
  lc.shutdown (0, false);
  lc.setIntensity (0, 8); //LED light intensity
  lc.clearDisplay (0);
}


//loop for LED
void loop3()
{
  if (hum==2 && lum==2) //optimal condition
  {
    DisplayBytes(happy);
  }


  else if (hum==3 && lum==3)
  {
    DisplayBytes(happy);
  }


  else if (hum==2 && lum==1) //lack of light
  {
    DisplayBytes(light);
  }


  else if (hum==3 && lum==1) //lack of light
  {
    DisplayBytes(light);
  }


  else if (hum==2 && lum==4) //too much light
  {
    DisplayBytes(glare);
  }


  else if (hum==3 && lum==4) //too much light
  {
    DisplayBytes(glare);
  }


  else if (hum==1 && lum==2) //lack of water
  {
    DisplayBytes(water);
  }


  else if (hum==1 && lum==3) //lack of water
  {
    DisplayBytes(water);
  }


  else if (hum==4 && lum==2) //too much water
  {
    DisplayBytes(throwup);
  }


  else if (hum==4 && lum==3) //too much water
  {
    DisplayBytes(throwup);
  }


  else if (hum==1 && lum==1)//plant about to die
  {
    DisplayBytes(dead);
  }


  else if (hum==4 && lum==4)
  {
    DisplayBytes(dead);
  }
  
  delay(500);
}


//setup for button
void setup4()
{
  pinMode (waterPin, INPUT); //setup water button
  pinMode (lightPin, INPUT); //setup light button
}


void loop4()
{
  //button pressed
  // read the state of the pushbutton value:
  buttonState = digitalRead(waterPin); //define water button condition


  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH && hum==2) {
    // turn water display LED on:
    DisplayBytes(waterhalf);
  }
  else if (buttonState == HIGH && hum==3){
    DisplayBytes(waterfull);
  }
  else if (buttonState == HIGH && hum==1){
    DisplayBytes(waterzero);
  }
   else if (buttonState == HIGH && hum==4){
    DisplayBytes(waterfull);
    delay(500);
    lc.clearDisplay(0);
    delay(500);
    DisplayBytes(waterfull);
    delay(500);
    lc.clearDisplay(0);
    delay(500);
    DisplayBytes(waterfull);
    delay(500);
  }
  delay(50);
  
  buttonState = digitalRead(lightPin); //define light button condition


  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH && lum==2) {
    // turn water display LED on:
    DisplayBytes(lighthalf);
  }
  else if (buttonState == HIGH && lum==3){
    DisplayBytes(lightfull);
  }
  else if (buttonState == HIGH && lum==1){
    DisplayBytes(lightzero);
  }
  else if (buttonState == HIGH && lum==4){
    DisplayBytes(lightfull);
    delay(500);
    lc.clearDisplay(0);
    delay(500);
    DisplayBytes(lightfull);
    delay(500);
    lc.clearDisplay(0);
    delay(500);
    DisplayBytes(lightfull);
    delay(500);
  }
  delay(50);
}


void setup() {
  Serial.begin(9600); //Setup Serial Monitor
  setup1();
  setup2();
  setup3();
  setup4();
}


void loop() {
  loop1();
  loop2();
  loop3();
  loop4();
}


void DisplayBytes(byte image[]) //displaying image from hex byte 
  {
  for(int i =0; i<=7; i++){
    lc.setRow(0,i, image[i]);
  }
}

