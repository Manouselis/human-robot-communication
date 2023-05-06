//#define TOUCH_PIN     A0
//
//bool prev_touch_value = 0;
//
//void touch_sensor_setup(){
//    pinMode(TOUCH_PIN, INPUT);
//}
//
//// --------------------------------------------------------------------------------- //
//// ---------------------------------- TOUCH SENSOR --------------------------------- //
//// --------------------------------------------------------------------------------- //
//void touch_sensor() {
//  // Read the value of the touch sensor. If it's being touched and wasn't previously, then that means someone just touched it
//  // We can then play the next audio fragment and loop through the emotions
//  bool touch_value = digitalRead(TOUCH_PIN);
//  if (touch_value && !prev_touch_value) {
//    PlayNext();
//    switch (emotion) {
//      case NEUTRAL:
//        emotion = SURPRISED;
//        break;
//      case SURPRISED:
//        emotion = HAPPY;
//        break;
//      case HAPPY:
//        emotion = ANGRY;
//        break;
//      case ANGRY:
//        emotion = SAD;
//        break;
//      case SAD:
//        emotion = NEUTRAL;
//        break;
//    }
//  }
//  prev_touch_value = touch_value;
//}
