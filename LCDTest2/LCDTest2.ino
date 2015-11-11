/*******************************************************************
* 
* Rhino Nevers
* 02 NOV 2015
*
* Test code for a basic menu on the LCD shield.
*******************************************************************/

// Include libraries for the LCD screen.
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <Adafruit_MCP23017.h>

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
  boolean buttons = lcd.readButtons();
  if (buttons & BUTTON_UP)
    pressUp();
  if (buttons & BUTTON_DOWN)
    pressDown();
  if (buttons & BUTTON_LEFT)
    pressLeft();
  if (buttons & BUTTON_RIGHT)
    pressRight();
  if (buttons & BUTTON_SELECT)
    pressSelect();
}
 
// Set up the LCD screen.
void initializeLCD() {
  // Start the LCD screen with 2 rows and 64 columns.
  lcd.begin(screenWidth, screenHeight);
  // Print "LCD Shield Test" centered on the screen.
  lcd.setCursor(3, 0);
  lcd.print("LCD Shield");
  lcd.setCursor(6, 1);
  lcd.print("Test");
  lcd.setBacklight(WHITE);
  delay(3000);
  lcd.clear();
}

// Display the main menu.
void displayMenu() {
  // Display the main menu items.
  screenNumber = 1;
  byte itemNumber = 1;
  for (byte i = 0; i < screenWidth; i+=8) {
    for (byte j = 0; j < screenHeight; j++) {
      lcd.setCursor(i, j);
      String text = String(itemNumber);
      lcd.print("Item" + text);
      itemNumber++;
      Serial.print(itemNumber);
    }
  }
  // Display the cursor and set it to blink.
  lcd.setCursor(0, 0);
  lcd.cursor();
  lcd.blink();
}

// Perform the action associated with pressing up.
void pressUp() {
  switch (screenNumber) {
    case 1: if (yPos > 0) {
      yPos--;
    }
  }
}

// Perform the action associated with pressing down.
void pressDown() {
  switch (screenNumber) {
    case 1: if (yPos < screenHeight/2) {
      yPos++;
    }
  }
}

// Perform the action associated with pressing left.
void pressLeft() {
  switch (screenNumber) {    
    case 1: if (xPos > 0) {
      xPos -= screenWidth/2;
    }
  }
}

// Perform the action associated with pressing right.
void pressRight() {
  switch (screenNumber) {
    case 1: if (xPos < screenWidth/2) {
      xPos += screenWidth/2;
    }
  }
}

// Perform the action associated with pressing select.
void pressSelect() {
}
