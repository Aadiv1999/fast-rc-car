#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define cx 128/2
#define cy 64/2
#define led 13
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


String buffer = "";         // a string to hold incoming data

int gm[2];


void setup() {
  buffer.reserve(20);     // Reserve 255 chars
  Serial.begin(115200);    // Initialize UART

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  pinMode(led, OUTPUT);
  Serial.begin(115200);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(cx - 30, cy - 10);
  // Display static text
  display.println("INIT"); //Write custom text here
  display.display();
  digitalWrite(led, LOW);
  delay(500);
  display.clearDisplay();
  display.display();
}

void loop() {
  // NOP
  serialEvent(gm);
  testDisplay(gm);
  display.display();
  digitalWrite(led, LOW);

}

// SerialEvent occurs every time we receive RX interrupt
int serialEvent(int* gm) {
  while (Serial.available()) {
    char c = (char)Serial.read();  // Read character
    buffer += c;                   // Add it to buffer
    // If end-of-line, reset buffer and send back the data
    if (c == '\n') {

      //cases on buffer

      if ((buffer == "161\n") && (gm[0] < 8)) {
        gm[0]++;
        digitalWrite(led, HIGH);
      }
      else if ((buffer == "151\n") && (gm[1] < 1))  {
        gm[1]++;
        digitalWrite(led, HIGH);
      }
      else if ((buffer == "131\n") && (gm[0] > 0)) {
        gm[0]--;
        digitalWrite(led, HIGH);
      }
      else if ((buffer == "141\n") && (gm[1] > 0)){
        gm[1]--;
        digitalWrite(led, HIGH);
      }
    }
  }
  buffer = "";
}


void testDisplay(int* gm) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1.5);
  display.setCursor(0, 0);
  display.print("Aadiv's Car");
  display.setCursor(0, 10);
  display.print("Gear: ");
  if (gm[0] == 0) {
    display.print("N");
  }
  else {
    display.print(gm[0]);
  }

  display.setCursor(0, 20);
  display.print("Mode: ");
  display.print(gm[1]);


}
