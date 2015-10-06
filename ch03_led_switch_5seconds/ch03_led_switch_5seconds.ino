#include <Bounce2.h>

#define SERIAL_BAUDRATE 19200
#define LED_PIN 11
#define SWITCH_PIN 7
#define DEBOUNCE_DELAY 50
#define DURATION 5000

Bounce bouncer = Bounce();
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
  bouncer.interval(DEBOUNCE_DELAY);
  
  updateLed();
}

unsigned long time_previous;
void loop() {
  // put your main code here, to run repeatedly:

  bouncer.update();
  boolean switch_status = bouncer.read();

  switch(state){
    case S_OFF:
      if(switch_status == LOW){
        time_previous = millis();
        state = S_OFF_NO_PRESS;
      }
    break;
    case S_OFF_NO_PRESS:
      if(switch_status == LOW){
        unsigned long time_current = millis();
        if(time_current - time_previous >= DURATION){
          state = S_ON;  
        }
      }  
      else{
        state = S_OFF;  
      }
      break;
    case S_ON:
      if(switch_status == HIGH){
        time_previous = millis();
        state = S_ON_PRESS;  
      }
    break;
    case S_ON_PRESS:
      if(switch_status == HIGH){
        unsigned long time_current = millis();
        if(time_current - time_previous >= DURATION){
          state = S_OFF;  
        }  
      }
      else{
        state = S_ON;  
      }
      break;
  }
  //可以開 Tools 裡面的 Serial Monitor 看看送出的訊號
  Serial.println(state);
  updateLed();
}
