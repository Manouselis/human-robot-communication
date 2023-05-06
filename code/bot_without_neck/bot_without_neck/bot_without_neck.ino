//#define DEBUG

#include "Arduino.h"
#include "Eyes.h"
#include "Camera.h"
#include "SerialCommunication.h"
#include "Servos.h"
#include "MP3.h"
#include "Speech.h"
//#include "TouchSensors.h"
#include "HUSKYLENS.h"

/*
    Connections:
    MP3 MODULE    -> D2
    LED EYES      -> D3
    SERVOS        -> D6
    SMALL SERVO   -> D8
    TOUCH_SENSOR  -> A0
    HUSKY_LENS    -> I2C
*/

String robot_name = "Bo the box";
String robot_version_number = "0.1";

long timer1, timer2, timer3;

void setup() {
  eyes_setup();
  serial_communication_setup();
  mp3_setup();
  husky_lens_setup();
  servo_setup();
  //touch_sensor_setup();
}

void loop() {
//  // Ever 20 milliseconds, update the servos
  if (millis() - timer1 >= 20){
    //serial_communication();
    //delay(50);
    timer1 = millis();
 //   move_servos();
    husky_lens();
//    touch_sensor();
    run_emotions();
    if(face_detected){
      no_face_time = 0;
      if (face_time < 10){
        face_time++;
      } else if (face_time == 10) {
        face_time++;
        Serial.println("face detected");
      }
  } else {
    face_time = 0;
    if (no_face_time < 50){
      no_face_time++;
    } else if (no_face_time == 50) {
      no_face_time++;
      Serial.println("face is gone");
    }
  }
  }

  // Every 50 milliseconds, read for new commands
  if (millis() - timer2 >= 100){
    timer2 = millis();
    serial_communication();
  }
}
