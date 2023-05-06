#include <SoftwareSerial.h>
#include "HUSKYLENS.h"

HUSKYLENS huskylens;
HUSKYLENSResult face;

void husky_lens_setup(){
  Wire.begin();
  while (!huskylens.begin(Wire)) {
      Serial.println(F("Begin failed!"));
      Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
      Serial.println(F("2.Please recheck the connection."));
      delay(100);
  }
}

void husky_lens() {
    if (!huskylens.request()) {}
    else if (!huskylens.available()) {
    //Serial.println(F("No face appears on the screen!"));
    face_detected = false;
  } else {
    //Serial.println(F("###########"));

    // We loop through all faces received by the HuskyLens. If it's a face that we've learned (ID=1), we will track that face.
    // If no learned face is on the screen, we take the first face returned (which is the face closest to the center)
    face_detected = false;
    int face_index = 0;
    while (huskylens.available()) {
      HUSKYLENSResult result = huskylens.read();
      if (result.command == COMMAND_RETURN_BLOCK) {
        //Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
        if (face_index == 0 || result.ID == 1) face = result;
        face_index ++;
        face_detected = true;
      }
    }
    //Serial.println(String() + F("Block:xCenter=") + face.xCenter + F(",yCenter=") + face.yCenter + F(",width=") + face.width + F(",height=") + face.height + F(",ID=") + face.ID);
  }
}

//
//void name(){
//  HUSKYLENSResult result = huskylens.read();
//  Serial.println("User picked: ");
//  Serial.println(String() +F("ID=") + result.ID);
//    int state = result.ID
//    switch (state) {
//      case 1:
//        state = rock;
//        break;
//      case 2:
//        state = paper;
//        break;
//      case 3:
//        state = scissors;
//        break;
//
//    } 
//    return state 
//}
//
//void pickState(){
//   int randNumber = random(4);
//   if(randNumber == 0){
//    servo1.write(180);
//   }
//   else{
//    if(randNumber == 1){
//        servo1.write(120);
//    }
//    else{
//        if(randNumber == 2){
//          servo1.write(60);
//        }
//        else{
//          servo1.write(60);  
//        }
//    }
//   }
//
//}
//
////void printResult(HUSKYLENSResult result){
////    if (result.command == COMMAND_RETURN_BLOCK){
////   Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
////    }
////    else if (result.command == COMMAND_RETURN_ARROW){
////        Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
////    }
////    else{
////        Serial.println("Object unknown!");
////    }
////}
