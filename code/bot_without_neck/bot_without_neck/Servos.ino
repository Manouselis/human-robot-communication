#include <Servo.h> 

#define SERVO_PIN_1   6
#define SERVO_PIN_2   7
#define SERVO_PIN_3   8

Servo servo1, servo2, servo3;
float servo1_pos = 90, servo2_pos = 90, servo3_pos = 90;
float servo1_target = 90, servo2_target = 90, servo3_target = 0;
float servo1_speed = 0, servo2_speed = 0;

float servo1_target_pc = 90, servo2_target_pc = 90;

void servo_setup(){
//  servo1.attach(SERVO_PIN_1);
//  servo2.attach(SERVO_PIN_2);
  servo3.attach(SERVO_PIN_3);
//  servo1.write(20);
//  servo2.write(20);
  servo3.write(0);
  delay(100); 
}

//void move_servos(){
//  // We apply some smoothing to the servos and limit the speed
//  // We do this because abrubt movements cause a big spike in current draw
//  // If we are connected to the PC, we use the PC angles. Otherwise we use the angles from the Arduino
//  float servo1_target_ = (pc_connected) ? servo1_target_pc : servo1_target;
//  float servo2_target_ = (pc_connected) ? servo2_target_pc : servo2_target;
//  int tag_idSelected=0;
//  
//  servo1.write(180);
//  delay(1000);
//  servo1.write(120);
//  delay(1000);
//  servo1.write(60);
//  delay(1000);
//  servo1.write(0);
//  delay(1000);
//  pickState();
//  delay(3000);
//  name();
//}

//RPS VERSION
void move_servos() {
  //Serial.println("In Move Servos");
  //servo1.write(180);
  //delay(1000);
  //servo1.write(162);//162 rock
  //delay(1000);
  //servo1.write(90); //90 paper
  //delay(1000);
  //servo1.write(18); //18 scissorsservo1.write(18); //144
  //delay(1000);
  //servo1.write(0); //144
}

void do_movement(String command){
  if (command.equals("countdown")){
    emotion = NEUTRAL;
    emotions_changed = true;
    run_emotions();
    SpecifyMusicPlay(9);
    countdown_movement();
    //Serial.println("doing the countdown movement");
  } if (command.equals("rock")){
    emotion = NEUTRAL;
    emotions_changed = true;
    SpecifyMusicPlay(14);
    servo3.write(165);
    //Serial.println("doing the countdown movement");
  } if (command.equals("paper")){
    emotion = NEUTRAL;
    emotions_changed = true;
    SpecifyMusicPlay(15);
    servo3.write(120);
    //Serial.println("doing the countdown movement");
  } if (command.equals("scissors")){
    emotion = NEUTRAL;
    emotions_changed = true;
    SpecifyMusicPlay(13);
    servo3.write(60);
    //Serial.println("doing the countdown movement");
  } if (command.equals("go")){
    servo3.write(0);
    //Serial.println("doing the countdown movement");
  } else {
     //Serial.print("I'm don't know how to perform the move: ");
     //Serial.println(command);
  }

}

void countdown_movement() {
  Serial.println("in countdown movement");
  servo3_target = 120;
  servo3.write(165);
  delay(1000);
  for (servo3_pos = 165; servo3_pos >= servo3_target; servo3_pos -= 1) {
    servo3.write(servo3_pos);
    delay(5);
  }
  servo3_target = 60;
  delay(1000);
  for (servo3_pos = servo3_pos; servo3_pos >= servo3_target; servo3_pos -= 1) {
    servo3.write(servo3_pos);
    delay(5);
  }
  servo3_target = 0;
  delay(1000);
  for (servo3_pos = servo3_pos; servo3_pos >= servo3_target; servo3_pos -= 1) {
    servo3.write(servo3_pos);
    delay(5);
  }
  delay(1000);
}
