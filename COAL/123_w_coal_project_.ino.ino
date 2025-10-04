#define Flame_sensor 6
#define Smoke_sensor 2
#define Red_led 5
#define Green_led 3
#define Buzzer 4

bool flame_status = false;
bool smoke_status = false;

unsigned long fireDetectedTime = 0;
unsigned long smokeDetectedTime = 0;

bool fireAlertActive = false;
bool smokeAlertActive = false;

void setup() {
  Serial.begin(9600);
  pinMode(Flame_sensor, INPUT);
  pinMode(Smoke_sensor, INPUT);
  pinMode(Red_led, OUTPUT);
  pinMode(Green_led, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  digitalWrite(Red_led, LOW);
  digitalWrite(Green_led, LOW);
  digitalWrite(Buzzer, LOW);
}

void loop() {
  flame_status = digitalRead(Flame_sensor);
  smoke_status = digitalRead(Smoke_sensor);
  unsigned long currentTime = millis();

  // 🔥 FIRE DETECTED
  if (flame_status == LOW) {
    fireDetectedTime = currentTime;
    fireAlertActive = true;
  }

  if (fireAlertActive) {
    if (currentTime - fireDetectedTime <= 5000) {
      digitalWrite(Red_led, HIGH);
    } else {
      digitalWrite(Red_led, LOW);
      fireAlertActive = false;
    }
  }

  // 🌫 SMOKE DETECTED
  if (smoke_status == LOW) {
    smokeDetectedTime = currentTime;
    smokeAlertActive = true;
  }

  if (smokeAlertActive) {
    if (currentTime - smokeDetectedTime <= 5000) {
      digitalWrite(Green_led, HIGH);
    } else {
      digitalWrite(Green_led, LOW);
      smokeAlertActive = false;
    }
  }

  // 🔔 BUZZER Control (agar koi bhi alert active ho)
  if ((fireAlertActive && currentTime - fireDetectedTime <= 5000) || 
      (smokeAlertActive && currentTime - smokeDetectedTime <= 5000)) {
    digitalWrite(Buzzer, HIGH);
  } else {
    digitalWrite(Buzzer, LOW);
  }

  delay(100);
}
