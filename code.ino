#include <Wire.h>
#include <MPU6050.h>
#include <BleMouse.h>

// --- Pins ---
#define BUTTON_LEFT 18
#define BUTTON_RIGHT 19

// --- MPU6050 and BLE Mouse ---
MPU6050 mpu;
BleMouse bleMouse("ESP32_AirMouse", "MyCompany", 100);

// --- Sensitivity ---
float gyroSensitivity = 1200.0;   // Adjust as needed

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);

  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("✅ MPU6050 Connected.");
    Serial.println(" Connect to Esp32_Airmouse.......");
  } else {
    Serial.println("❌ MPU6050 Not Detected!");
    while (1) delay(1000);
  }
  bleMouse.begin();
}

bool printedOnce = false;  // At top

void loop() {
  if (!bleMouse.isConnected()) {
    printedOnce = false;
    return;
  }

  if (!printedOnce) {
    Serial.println("✅ Bluetooth Mouse Connected.");
    printedOnce = true;
  }

  handleButtons();

  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float moveX = (-gz + gy) / gyroSensitivity;
  float moveY = -gx / gyroSensitivity;

  int dx = (int)(moveX);
  int dy = (int)(moveY);

  if (abs(dx) < 1) dx = 0;
  if (abs(dy) < 1) dy = 0;

  bleMouse.move(dx, dy);

  delay(5);
}


void handleButtons() {
  if (digitalRead(BUTTON_LEFT) == LOW) {
    bleMouse.press(MOUSE_LEFT);
  } else {
    bleMouse.release(MOUSE_LEFT);
  }

  if (digitalRead(BUTTON_RIGHT) == LOW) {
    bleMouse.press(MOUSE_RIGHT);
  } else {
    bleMouse.release(MOUSE_RIGHT);
  }
}