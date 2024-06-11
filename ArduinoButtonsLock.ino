// Pin configuration
int buttonPins[] = {2, 3, 4, 5}; // Button pins
int greenLEDPin = 12;            // Green LED pin
int redLEDPin = 11;              // Red LED pin

// Correct combination to unlock
int correctCombination[] = {1, 2, 1, 1};
int enteredCombination[4] = {0, 0, 0, 0};
int currentIndex = 0;

void setup() {
  Serial.begin(9600);

  // Initialize button pins as input
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Initialize LED pins as output
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  // Turn on the red LED at startup (door is locked)
  digitalWrite(redLEDPin, HIGH);
  digitalWrite(greenLEDPin, LOW);
}

void loop() {
  // Check button presses
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      handleButtonPress(i + 1);
      delay(250); // Debounce delay
    }
  }
}

void handleButtonPress(int button) {
  // Shift entered combination and add new button press
  for (int i = 0; i < 3; i++) {
    enteredCombination[i] = enteredCombination[i + 1];
  }
  enteredCombination[3] = button;

  // Check if the entered combination is correct
  if (checkCombination()) {
    unlockDoor();
  }
}

bool checkCombination() {
  for (int i = 0; i < 4; i++) {
    if (enteredCombination[i] != correctCombination[i]) {
      return false;
    }
  }
  return true;
}

void unlockDoor() {
  // Turn off the red LED and turn on the green LED (door is unlocked)
  digitalWrite(redLEDPin, LOW);
  digitalWrite(greenLEDPin, HIGH);
  delay(5000); // Keep the door unlocked for 5 seconds

  // Turn off the green LED and turn on the red LED (door is locked again)
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(redLEDPin, HIGH);

  // Reset the entered combination
  for (int i = 0; i < 4; i++) {
    enteredCombination[i] = 0;
  }
}

