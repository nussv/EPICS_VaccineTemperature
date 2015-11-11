/*******************************************************************
* November 2015
* LCD shield with menu screen
* No temperature reading
* Nuss Visatemongkolchai
*******************************************************************/
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <Adafruit_MCP23017.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h> 

// Initialize the LCD.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
// Define the backlight colors.
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

// Define the menu's maximum size.
const byte menuHeight = 2;
const byte menuWidth = 64;

// Define the screen's maximum size.
const byte screenHeight = 2;
const byte screenWidth = 16;

// Define the cursor's position.
byte xPos = 0;
byte yPos = 0;

// Define the current screen being displayed.
// The proper way to handle this is with a stack of states.
byte screenNumber = 0;

//For temperature readings
#define numVials 4
byte alert[numVials] = {0}; //0 for normal, 1 for warning

// Set up the LCD, print the title and display the main menu.
void setup() {
  initializeLCD();
  displayMenu();
  Serial.begin(9600);
}

// Display the main menu and read button inputs.
void loop() {
  // Display the cursor in its current position.
  lcd.setCursor(xPos, yPos);
  // Read inputs from the LCD's buttons.
  byte buttons = lcd.readButtons();
  if (buttons & BUTTON_UP)
    pressUp();
  if (buttons & BUTTON_DOWN)
    pressDown();
  if (buttons & BUTTON_LEFT)
    pressLeft();
  if (buttons & BUTTON_RIGHT) 
    pressRight();
  if (buttons & BUTTON_SELECT){
    pressSelect(xPos + yPos);
  }
}
 
// Set up the LCD screen.
void initializeLCD() {
  // Start the LCD screen with 2 rows and 64 columns.
  lcd.begin(screenWidth, screenHeight);
  // Print menu.
  lcd.setCursor(0, 0);
  lcd.print("Vial Temperature");
  lcd.setCursor(6, 1);
  lcd.print("Menu");
  delay(1000);
  
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("O: sample safe");
//  lcd.setCursor(0, 1);
//  lcd.print("X: sample unsafe");
//  delay(2500);
//
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("Press select to");
//  lcd.setCursor(0, 1);
//  lcd.print("view");
//  delay(1500);
  
  lcd.setBacklight(WHITE);
  lcd.clear();
}

// Display the main menu.
void displayMenu() {
  // Display the main menu items.
  lcd.clear();
  screenNumber = 1;

byte a = 0;
byte b = 0;

  for (int k = 0; k < numVials; k++) {
        lcd.setCursor(a, b);
        if(alert[k] == 0) lcd.print("O");
        else lcd.print("X");
        a++;
        if(a==screenWidth) {
          a == 0;
          b++;
        }
    }
 
  // Display the cursor and set it to blink.
  lcd.setCursor(xPos, yPos);
  lcd.cursor();
  lcd.blink();
}

void tempScreen(byte b) {
  screenNumber = 2;
  lcd.clear();
  lcd.setCursor(0, 0);

  String num = String(b + 1);
  lcd.print("Vial " + num);

  lcd.setCursor(0, 1);
  lcd.print("Celsius:");  
  
}

// Perform the action associated with pressing up.
void pressUp() {
  switch (screenNumber){
    case 1: if (yPos > 0) {
      yPos--;
      delay(200);
    }
  }
}

// Perform the action associated with pressing down.
void pressDown() {
  switch (screenNumber) {
    case 1: if (yPos == 0) {
      yPos++;
      delay(200);
    }
  }
}

// Perform the action associated with pressing left.
void pressLeft() {
  switch (screenNumber) {
    case 1: if (xPos == 0) {
      xPos = numVials - 1;
      delay(200);
      break;
      }
      
      if (xPos > 0) {
      xPos--;
      delay(200);
      break;
      }
    }   
}

// Perform the action associated with pressing right.
void pressRight() {
  switch (screenNumber) {
    case 1: if (xPos >= numVials - 1) {
      xPos = 0;
      delay(200);
      break;
      }
      
      if (xPos < numVials - 1) {
      xPos++;
      delay(200);
      break;
      }
    }   
}


// Perform the action associated with pressing select.
void pressSelect(byte b) {
  switch (screenNumber) {
    case 1: {
      tempScreen(b); 
      delay(200);
      break;
    }
    case 2: {
      Serial.println(screenNumber);
      Serial.println("Display menu being called");
      displayMenu(); 
      delay(200);
      break;
    }
}

}

