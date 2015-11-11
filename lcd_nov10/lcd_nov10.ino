/*******************************************************************
* November 2015
* LCD shield with menu screen
* No temperature reading
* Nuss Visatemongkolchai, Rhino Nevers
*******************************************************************/
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <Adafruit_MCP23017.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h> 

//Number of vials in the circuit
#define numVials 25


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
  int xy = xPos + (16*yPos);
  
  if (buttons & BUTTON_UP)
    pressUp();
  if (buttons & BUTTON_DOWN)
    pressDown(xPos, yPos);
  if (buttons & BUTTON_LEFT)
    pressLeft(xy);
  if (buttons & BUTTON_RIGHT) 
    pressRight(xy);
  if (buttons & BUTTON_SELECT){
    pressSelect(xy);
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
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("O: sample safe");
  lcd.setCursor(0, 1);
  lcd.print("X: sample unsafe");
  delay(2500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press select to");
  lcd.setCursor(0, 1);
  lcd.print("view");
  delay(1500);
  
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

        if(a==screenWidth - 1) {
          a = 0;
          b++;
        }
        else a++;
        
        if(alert[k] == 0) lcd.print("O");
        else lcd.print("X");
    }
 
  // Display the cursor and set it to blink.
  lcd.setCursor(xPos, yPos);
  lcd.cursor();
  lcd.blink();
}

void tempScreen(int xy) {
  screenNumber = 2;
  lcd.noCursor();
  lcd.noBlink();

  lcd.clear();
  lcd.setCursor(0, 0);

  String num = String(xy + 1);
  lcd.print("Vial " + num);

  lcd.setCursor(0, 1);
  lcd.print("Current temp: ");  
  
}

void tempScreenMax(int xy) {
  screenNumber = 3;

  lcd.clear();
  lcd.setCursor(0, 0);

  String num = String(xy + 1);
  lcd.print("Vial " + num);

  lcd.setCursor(0, 1);
  lcd.print("Max temp: ");  
  
}

void tempScreenMin(int xy) {
  screenNumber = 4;

  lcd.clear();
  lcd.setCursor(0, 0);

  String num = String(xy + 1);
  lcd.print("Vial " + num);

  lcd.setCursor(0, 1);
  lcd.print("Min temp: ");  
  
}

// Perform the action associated with pressing up.
void pressUp() {
  switch (screenNumber){
    case 1: if (yPos > 0) {
      yPos--;
      delay(300);
      break;
    }
  }
}

// Perform the action associated with pressing down.
void pressDown(byte x, byte y) {
  switch (screenNumber) {
    case 1: if(x + (16*(y+1)) >= numVials) break;
    
      if (yPos == 0) {
      yPos++;
      delay(300);
      break;
    }
  }
}

// Perform the action associated with pressing left.
void pressLeft(int xy) {
  switch (screenNumber) {
    case 1: {
      if (xPos == 0 && yPos == 0) break;
      
      if (xPos == 0 && yPos != 0) {
 
      xPos = screenWidth - 1;
      yPos--;
      delay(300);
      break;
      }
      
      if (xPos > 0 && xPos < screenWidth) {
      xPos--;
      delay(300);
      break;
      }

    }
            
     case 2: {
      tempScreenMin(xy);
      delay(300);
      break;
     }
     case 3: {
      tempScreen(xy);      
      delay(300);
      break;
     }
     case 4: {
      tempScreenMax(xy);
      delay(300);
      break;
     }
  }
}

// Perform the action associated with pressing right.
void pressRight(int xy) {
  switch (screenNumber) {
    case 1: {
      if(xy == numVials - 1) break;

    
      if (xPos == screenWidth - 1) {
        xPos = 0;
        yPos++;
        break;
        delay(300);
      }
      
      if (xPos < screenWidth - 1) {
      xPos++;
      delay(300);
      break;
      }
    }
    
    case 2: {
      tempScreenMax(xy);
      delay(300);
      break;
    }
    case 3: {
      tempScreenMin(xy);
      delay(300);
      break;
    }
    case 4: {
      tempScreen(xy); 
      delay(300);
      break; 
    }
  }      
}


// Perform the action associated with pressing select.
void pressSelect(int xy) {
  
  switch (screenNumber) {
    case 1: {
      tempScreen(xy); 
      delay(300);
      break;
    }
    case 2: {
      displayMenu(); 
      delay(300);
      break;
    }
    case 3: {
      displayMenu();
      delay(300);
      break;
    }
    case 4: {
      displayMenu(); 
      delay(300);   
      break; 
    }
}

}

