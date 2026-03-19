// ==============================================================================
// PROJECT: Ultrasonic Smart Glasses for the Blind
// MICROCONTROLLER: Arduino Nano / Pro Mini (ATmega328P)
// ==============================================================================

// --- Pin Definitions ---
const int TRIG_L = 2;     // Left Sensor Trigger
const int ECHO_L = 3;     // Left Sensor Echo
const int TRIG_R = 4;     // Right Sensor Trigger
const int ECHO_R = 5;     // Right Sensor Echo
const int MOTOR_PIN = 10; // Haptic Feedback (PWM to Transistor Base)
const int STATUS_LED = 13;// Onboard LED for visual debugging

// --- Calibration Thresholds ---
const int MIN_DIST = 10;   // Distance (cm) for MAXIMUM vibration
const int MAX_DIST = 100;  // Distance (cm) where vibration STARTS
const int MOTOR_MAX = 255; // Maximum PWM signal (Full 5V)
const int MOTOR_MIN = 95;  // Minimum PWM signal to overcome motor friction

void setup() {
  // Start serial communication for laptop debugging
  Serial.begin(9600);
  
  // Configure pin modes
  pinMode(TRIG_L, OUTPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_R, OUTPUT);
  pinMode(ECHO_R, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  // --- Startup Sequence ---
  // A quick double-buzz to let the user know the glasses are ON and working
  for(int i = 0; i < 2; i++) {
    digitalWrite(STATUS_LED, HIGH);
    analogWrite(MOTOR_PIN, 150);
    delay(200);
    digitalWrite(STATUS_LED, LOW);
    analogWrite(MOTOR_PIN, 0);
    delay(200);
  }
  Serial.println("System Initialized. Scanning...");
}

// --- Distance Calculation Function ---
long getDistance(int trigPin, int echoPin) {
  // Ensure the trigger pin is clear
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send a 10-microsecond sonic burst
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo time with a 30ms timeout (prevents code freezing)
  long duration = pulseIn(echoPin, HIGH, 30000); 
  
  // If duration is 0, it means it timed out (no object detected)
  if (duration == 0) {
    return MAX_DIST + 1; 
  }
  
  // Calculate distance in cm (Time * Speed of Sound / 2)
  return (duration / 2) * 0.0343;
}

void loop() {
  // 1. Read distances from both sensors
  long distL = getDistance(TRIG_L, ECHO_L);
  long distR = getDistance(TRIG_R, ECHO_R);
  
  // 2. Find the closest obstacle (Left or Right)
  long closestDist = min(distL, distR);

  // 3. Process the feedback
  if (closestDist <= MAX_DIST) {
    // Turn on the status LED
    digitalWrite(STATUS_LED, HIGH);

    // Map the distance to a vibration intensity. 
    // Closer distance (e.g., 10cm) maps to stronger PWM (255)
    int intensity = map(closestDist, MAX_DIST, MIN_DIST, MOTOR_MIN, MOTOR_MAX);
    
    // Constrain ensures the value never drops below 0 or goes above 255
    intensity = constrain(intensity, 0, MOTOR_MAX);
    
    // Send the signal to the motor
    analogWrite(MOTOR_PIN, intensity);
    
    // Print data to the Serial Monitor for the presentation demo
    Serial.print("Left: "); Serial.print(distL);
    Serial.print("cm | Right: "); Serial.print(distR);
    Serial.print("cm | Closest: "); Serial.print(closestDist);
    Serial.print("cm | Motor PWM: "); Serial.println(intensity);
  } 
  else {
    // No obstacle within the 100cm active zone
    digitalWrite(STATUS_LED, LOW);
    analogWrite(MOTOR_PIN, 0); // Turn off motor
  }

  // A small delay to keep the sensors from interfering with each other
  delay(50); 
}
