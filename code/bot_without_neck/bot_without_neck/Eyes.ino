enum Emotion {NEUTRAL, SURPRISED, HAPPY, ANGRY, SAD};
Emotion emotion = NEUTRAL;
bool emotions_changed = false;

void eyes_setup(){
  pixels.begin();
}

// --------------------------------------------------------------------------------- //
// -------------------------------------- EYES ------------------------------------- //
// --------------------------------------------------------------------------------- //
void display_eyes(const byte arr[], int hue){
   display_eye(arr, hue, true);
   display_eye(arr, hue, false);
}

void display_eye(const byte arr[], int hue, bool left) {
  // We will draw a circle on the display
  // It is a hexagonal matrix, which means we have to do some math to know where each pixel is on the screen

  int rows[] = {4, 5, 6, 7, 6, 5, 4};      // The matrix has 4, 5, 6, 7, 6, 5, 4 rows.
  int NUM_COLUMNS = 7;                     // There are 7 columns
  int index = (left) ? 0 : 37;             // If we draw the left eye, we have to add an offset of 37 (4+5+6+7+6=5+4)
  for (int i = 0; i < NUM_COLUMNS; i++) {
    for (int j = 0; j < rows[i]; j++) {
      int brightness = LED_BRIGHTNESS * bitRead(arr[i], (left) ? rows[i] - 1 - j : j);
      pixels.setPixelColor(index, pixels.ColorHSV(hue * 256, 255, brightness));
      index ++;
    }
  }
}


//void run_emotions(){
//  pixels.clear();  
//
//  switch (emotion) {
//    case NEUTRAL:
//      if (millis() % 5000 < 150) display_eyes(blink1, 125);
//      else if (millis() % 5000 < 300) display_eyes(blink2, 125);
//      else if (millis() % 5000 < 450) display_eyes(blink1, 125);
//      else display_eyes(neutral, 125);
//
//      if (tag_detected) {
//        servo1_target = 90.0 + float(tag.xCenter - 160) / 320.00 * -50.00;
//        servo2_target = 90.0 + float(tag.yCenter - 120) / 240.00 * 50.00;
//      }
//      break;
//    case HAPPY:
//      display_eyes(happy, 80);
//      
//      servo1_target = 90 + 10.0 * sin(millis() / 500.00);
//      servo2_target = 80 + 15.0 * cos(millis() / 400.00);
//      break;
//    case SAD:
//      display_eyes(sad, 150);
//      
//      servo1_target = 90 + 3.0 * sin(millis() / 400.00);
//      servo2_target = 120 + 20.0 * cos(millis() / 500.00);
//      break;
//    case ANGRY:
//      display_eyes(angry, 0);
//
//      servo1_target = 90 + 10.0 * sin(millis() / 250.00);
//      servo2_target = 110 + 15.0 * cos(millis() / 175.00);
//      break;
//    case SUPRISED:
//      display_eyes(suprised, 125);
//
//      servo1_target = 90;
//      servo2_target = 80 + 10.0 * cos(millis() / 500.00);
//      break;
//  }
//
//  pixels.show();
//}

//RPS VERSION
void run_emotions() {
//  //Serial.println("In run emotions");
  pixels.clear();

  if(emotions_changed){
    switch (emotion) {
      case NEUTRAL:
        if (millis() % 5000 < 150) display_eyes(blink1, 125);
        else if (millis() % 5000 < 300) display_eyes(blink2, 125);
        else if (millis() % 5000 < 450) display_eyes(blink1, 125);
        else display_eyes(neutral, 125);
        break;
      case HAPPY:
        display_eyes(happy, 80);
        break;
      case SAD:
        display_eyes(sad, 150);
        break;
      case ANGRY:
        display_eyes(angry, 0);
        break;
      case SURPRISED:
        display_eyes(surprised, 125);
        break;
    }
    pixels.show();
    emotions_changed = false;
  }

//  
}

void change_emotions(String command){
  if (command.equals("neutral")){
    emotion = NEUTRAL;
    //Serial.println("I'm now feeling neutral");
  } else if (command.equals("surprised")){
    emotion = SURPRISED;
    //Serial.println("I'm now feeling surprised");
  } 
  else if (command.equals("happy")){
    emotion = HAPPY;
    //Serial.println("I'm now feeling happy");
  } else if (command.equals("angry")){
    emotion = ANGRY;
    //Serial.println("I'm now feeling angry");
  } else if (command.equals("sad")){
    emotion = SAD;
    //Serial.println("I'm now feeling sad");
  } 
  else {
     //Serial.print("I'm don't have the emotion: ");
     //Serial.println(command);
  }
  emotions_changed = true;
}
