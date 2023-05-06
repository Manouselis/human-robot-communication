void say(String command){
  if (command.equals("countdown")){
    SpecifyMusicPlay(9);
    countdown_movement();
    //Serial.println("saying the countdown");
  } else if (command.equals("goaway")){
    emotion = ANGRY;
    emotions_changed = true;
    SpecifyMusicPlay(10);
    //Serial.println("telling the user to go away");
  } else if (command.equals("goodbye")){
    emotion = NEUTRAL;
    emotions_changed = true;
    SpecifyMusicPlay(11);
    //Serial.println("saying goodbye");
  } else if (command.equals("greeting")){
    emotion = HAPPY;
    emotions_changed = true;
    SpecifyMusicPlay(1);
    //Serial.println("saying greeting");
  } else if (command.equals("groundrules")){
    emotion = NEUTRAL;
    emotions_changed = true;
    SpecifyMusicPlay(2);
    countdown_movement();
    //Serial.println("saying the ground rules");
  } else if (command.equals("intro")){
    emotion = HAPPY;
    emotions_changed = true;
    SpecifyMusicPlay(3);
    //Serial.println("saying the introduction");
  } else if (command.equals("robotname")){
    emotion = NEUTRAL;
    emotions_changed = true;
    SpecifyMusicPlay(6);
    //Serial.println("saying my name");
  } else if (command.equals("sorry")){
    emotion = SURPRISED;
    emotions_changed = true;
    SpecifyMusicPlay(12);
    //Serial.println("saying sorry");
  } else if (command.equals("robotmad")){
    emotion = ANGRY;
    emotions_changed = true;
    SpecifyMusicPlay(5);
    //Serial.println("saying that I'm mad");
  } else if (command.equals("robottie")){
    emotion = SURPRISED;
    emotions_changed = true;
    SpecifyMusicPlay(7);
    //Serial.println("saying that it's a tie");
  } else if (command.equals("robotlose")){
    emotion = SAD;
    emotions_changed = true;
    SpecifyMusicPlay(4);
    //Serial.println("saying that I lost");
  } else if (command.equals("robotwins")){
    emotion = HAPPY;
    emotions_changed = true;
    //servo1.write(100);
    SpecifyMusicPlay(8);
    //Serial.println("saying that I won");
  } else if (command.equals("rock")){
    SpecifyMusicPlay(14);
    do_movement("rock");
    //Serial.println("saying rock");
  } else if (command.equals("paper")){
    SpecifyMusicPlay(15);
    do_movement("paper");
    //Serial.println("saying paper");
  } else if (command.equals("scissors")){
    SpecifyMusicPlay(13);
    do_movement("scissors");
    //Serial.println("saying scissors");
  } 
  #ifdef DEBUG
  else if (command.equals("all")){
    for(int i = 1; i<=15; i++){
      SpecifyMusicPlay(i);
      Serial.println(i);
      delay(10000);
    }
  }
  #endif 
  else if(command.equals("nothing")){
    PlayPause();
    Serial.println("stopped talking");
  } else {
    #ifdef DEBUG
      //Serial.println("I don't know how to say ``" + command + "`` :(");
    #endif //DEBUG
  } 
}
