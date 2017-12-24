const uint8_t pin_layer[] = {10, 11, 12, 13};
const uint8_t pin_row[] = {0, 1, 2, 3};

const uint8_t total_layers = sizeof(pin_layer) / sizeof(uint8_t);
const uint8_t total_rows = sizeof(pin_row) / sizeof(uint8_t);

void setup() {
  for (int i = 0; i < total_layers; i++) {
    pinMode(pin_layer[i], OUTPUT);
  }

  for (int i = 0; i < total_rows; i++) {
    pinMode(pin_row[i], OUTPUT);
  }
}

void blink(uint8_t layer, uint8_t row, uint8_t microseconds = 1) {
  digitalWrite(pin_layer[layer], HIGH);
  digitalWrite(pin_row[row], LOW);
  delayMicroseconds(microseconds);
  digitalWrite(pin_layer[layer], LOW);
  digitalWrite(pin_row[row], HIGH);
}

void allOn(unsigned long miliseconds) {
  unsigned long previousMillis = millis();
  while (millis() - previousMillis <= miliseconds) {
    for (uint8_t layer = 0; layer < total_layers; layer++) {
      for (uint8_t row = 0; row < total_rows; row++) {
        blink(row, layer, 50);
      }
    }  
  }
}

void blinkRandom(uint8_t times) {
  for (int i = 0; i < times * total_layers * total_rows; i++) {
    uint8_t layer = random(0, total_layers);
    uint8_t row = random(0, total_rows);
    unsigned long miliseconds = random(100, 100);
    unsigned long previousMillis = millis();
    while (millis() - previousMillis <= miliseconds) {
      blink(layer, row);
    }
  }  
}

void bottomUp(uint8_t times, unsigned long miliseconds = 100) {
  for (int i = 0; i < times; i++) {
    for (uint8_t layer = 0; layer < total_layers; layer++) {
      for (uint8_t row = 0; row < total_rows; row++) {
        unsigned long previousMillis = millis();
        while (millis() - previousMillis <= miliseconds) {
          blink(layer, row);
        }
      }
    }
  }
}

void blinkRow(uint8_t row, unsigned long miliseconds = 100) {
  unsigned long previousMillis = millis();
  while (millis() - previousMillis <= miliseconds) {
    for (uint8_t layer = 0; layer < total_layers; layer++) {
      blink(layer, row);
    }
  }
}

void blinkAllRows(uint8_t times) {
  for (int i = 0; i < times; i++) {
    blinkRow(0);
    blinkRow(1);
    blinkRow(3);
    blinkRow(2);
  }
}

void blinkLayer(uint8_t layer, unsigned long miliseconds = 100) {
  unsigned long previousMillis = millis();
  while (millis() - previousMillis <= miliseconds) {
    for (uint8_t row = 0; row < total_rows; row++) {
      blink(layer, row);
    }
  }
}

void blinkAllLayers(uint8_t times) {
  for (int i = 0; i < times; i++) {
    for (uint8_t layer = 0; layer < total_layers; layer++) {
      blinkLayer(layer);
    }
  }
}

void loop() {
  allOn(2000);
  bottomUp(2);
  allOn(500);
  blinkAllRows(4);
  blinkAllLayers(4);
  blinkRandom(2);
}

