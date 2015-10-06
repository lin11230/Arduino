#include <Bounce2.h>

#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define SWITCH_PIN 7
#define DEBOUNCE_DELAY 50
#define DURATION 5000

Bounce bouncer = new Bounce();
// 定義狀態機的可能狀態
typedef enum{
  S_OFF,
  S_OFF_NO_PRESS,
  S_ON,
  S_ON_PRESS
}State;

State state = S_OFF;

void updateLed(){
  if(state == S_OFF || state == S_OFF_NO_PRESS){
    digitalWrite(LED_PIN, LOW);  
  }
  else if(state == S_ON || state == S_ON_PRESS){
    digitalWrite(LED_PIN, HIGH);
  }
  else{
    Serial.print("Error: in wrong state ");
    Serial.print(state);
  }
}

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  
  // After setting up the button, setup the object
  bouncer.attach(SWITCH_PIN);
  bouncer.interval(5);
  
  updateLED();
}

unsigned long time_previous;
void loop() {
  // put your main code here, to run repeatedly:

  bouncer.update();
  boolean switch_status = bouncer.read();

}
