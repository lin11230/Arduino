#include <Bounce2.h>

#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define SWITCH_PIN 7

Bounce bouncer = Bounce();
boolean led_status;

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);

  // After setting up the button, setup the object
  bouncer.attach(SWITCH_PIN);
  bouncer.interval(5);
  
  led_status = LOW;
  digitalWrite(LED_PIN, led_status);
}

void loop() {
  
  if(bouncer.update() == true && bouncer.read() == HIGH){
    led_status = !led_status;
    digitalWrite(LED_PIN, led_status);
  }
}
