// include the LCD screen library
#include <LiquidCrystal.h>

// include the DHT sensor library
#include "DHT.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initialize the two buttons
int button1Pin = 13;
int button2Pin = 10;

// created variables that will eventually represent the button boolean state
int button1State;
int button2State;

// define the sensor pin
#define DHTPin 7

// define the sensor type
#define DHTType DHT11

// put the sensors and the type of sensor into a function
DHT dht(DHTPin, DHTType);

void setup() {
// start the LCD screen
  lcd.begin(16,2);

// set the mode of each of the buttons
  pinMode(button1Pin,INPUT_PULLUP);
  pinMode(button2Pin,INPUT_PULLUP);
  
// start the serial monitor
  Serial.begin(9600);

// start the DHT sensor
  dht.begin();

// the start screen for the LCD screen 
  lcd.print("Click for Temp");
  lcd.setCursor(0,1);
  lcd.print("and Humidity");
}

void loop() {
// with a pre-made function, this command reads the humidity through the sensor
  float h = dht.readHumidity();

// with a pre-made function, this command reads the temperature through the sensor
  float t = dht.readTemperature();

// reads the two button states to use in later commands 
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

// the first if statement checks whether the right button is pressed or not
// then, it reads the humidity on the screen
if (button1State == LOW){
  lcd.clear();
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(14,1);
  lcd.print("<-");
    
}
// the second if statement checks whether the left button is pressed or not
// then, it reads the temperature on the screen
if (button2State == LOW){
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(t*1.8+32);
  lcd.print(" F");
  lcd.setCursor(14,1);
  lcd.print("->");
}

// there is a 1 second delay in between the loop because of the sensor
// the sensor needs at least a 1 second delay between each reading
 delay(1000);

// Starts the serial monitor to monitor the temperature and the humidity
 Serial.print("Temp: ");
 Serial.println(t*1.8+32);
 Serial.print("Humidity: ");
 Serial.println(h);
}
  