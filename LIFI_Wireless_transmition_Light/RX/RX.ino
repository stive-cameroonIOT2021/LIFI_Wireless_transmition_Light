#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SOLARPIN A7
#define THRESHOLD 300

#define MAX_LINES 4
String receivedText = "";

// Assuming receivedText is a string containing the text to be displayed
int cursorX = 0;  // Start from the first column
int cursorY = 0;  // Start from the first row
int lcdWidth = 20; // LCD width (20 columns)
int lcdHeight = 4; // LCD height (4 rows)
// Initialize the LCD. Adjust the address (0x27) and size (20, 4) if needed.
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  pinMode(SOLARPIN, INPUT);
  Serial.begin(9600);
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();  // Turn on the backlight
}

void loop() {
  int reading = analogRead(SOLARPIN);
  int bits[8];
  // Listening for the start bit
  if (reading > THRESHOLD) {
    // Reading bits
    for (int i = 0; i < 8; i++) {
      if (analogRead(SOLARPIN) > THRESHOLD) {
        bits[i] = 1;
      } else {
        bits[i] = 0;
      }
      delay(10);
    }

    // Convert bits to character
    int m = 0;
    for (int j = 1; j < 8; j++) {
      if (bits[j] == 1) {
        m += (1 << (7 - j));
      }
    }

    char n = m;
    receivedText += n;

    // Clean receivedText to remove unnecessary characters
    cleanString(receivedText);

// Display received text on the LCD
for (int i = 0; i < receivedText.length(); i++) {
    // Set the cursor at the current position
    lcd.setCursor(cursorX, cursorY);

    // Print the character at the current position
    lcd.print(receivedText[i]);

    // Move to the next column
    cursorX++;

    // If the end of the row is reached, move to the next row
    if (cursorX >= lcdWidth) {
        cursorX = 0;        // Reset column to 0
        cursorY++;          // Move to the next row
    }

    // If the LCD is full (all rows are occupied), reset to the top-left corner
    if (cursorY >= lcdHeight) {
        cursorY = 0;        // Reset to the first row
        cursorX = 0;        // Reset to the first column
        lcd.clear();        // Optional: clear the screen if you want to refresh it
    }
}
receivedText = "";  // Clear the string after printing

  }
}

// Function to clean the received string
void cleanString(String &text) {
  String cleanedText = "";
  for (int i = 0; i < text.length(); i++) {
    char c = text.charAt(i);
    // Only keep printable ASCII characters (space to tilde)
    if (c >= 32 && c <= 126) {
      cleanedText += c;
    }
  }
  text = cleanedText;  // Update the original string with the cleaned version
}

// Function to display the text on the LCD

