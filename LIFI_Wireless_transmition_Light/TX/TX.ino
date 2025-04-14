#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 10}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


#define Led_Pin 9

void setup() {
  // put your setup code here, to run once:
  pinMode(Led_Pin, OUTPUT);
  Serial.begin(9600); // Start serial communication at 9600 baud
}

void loop() {

  char customKey = customKeypad.getKey();
  
  if (customKey){
    //Serial.println(customKey);
    SendBits(String(customKey)+'\n');
  }

  if (Serial.available() > 0) { // Check if data is available to read
    String inputText = Serial.readStringUntil('\n'); // Read the string until Enter is pressed
    inputText += '\n';
    SendBits(inputText);

  }
}


void SendBits(String str){
    int length = str.length(); // Get the length of the input text
    int ar[20]; // Adjust this size based on expected input
    int bits[8];

    for (int i = 0; i < length; i++) {
      ar[i] = int(str[i]);
      int m = ar[i];
      int bin[8]; // Use 8 bits for ASCII values
      int newbin[8];

      // Convert to binary
      for (int z = 0; z < 8; z++) {
        bin[z] = m % 2;
        m = m / 2;
      }

      // Reverse the binary array to get the correct order
      for (int j = 0; j < 8; j++) {
        newbin[j] = bin[7 - j];
      }

      // Prepare bits for sending
      for (int p = 0; p < 8; p++) {
        bits[p] = newbin[p] == 1 ? HIGH : LOW;
      }

      // Transmit each bit
      bits[0] = HIGH; // Start bit (optional, depending on your protocol)
      for (int i = 0; i < 8; i++) {
        digitalWrite(Led_Pin, bits[i]);
        delay(10);
      }

      digitalWrite(Led_Pin, LOW); // Turn off laser after sending
      delay(50); // Delay between characters
    }
}