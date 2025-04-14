const int solarPin = A0; // Pin connected to the solar panel outputl
int threshold; // Variable to store the threshold
const unsigned long measurementDuration = 5000; // Duration to measure values in milliseconds


// Function to establish the threshold dynamically
void establishThreshold() {
  int maxValue = 0;
  int minValue = 1023; // AnalogRead range is 0-1023

  unsigned long startTime = millis();
  while (millis() - startTime < measurementDuration) {
    int ledValue = analogRead(solarPin); // Read the voltage from the solar panel

    // Update max and min values
    maxValue = max(maxValue, ledValue);
    minValue = min(minValue, ledValue);
    delay(50); // Delay between readings for stability
  }

  threshold = (maxValue + minValue) / 2; // Set threshold to the average
  Serial.print("Threshold established at: ");
  Serial.println(threshold);
}