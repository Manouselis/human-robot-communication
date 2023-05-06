bool pc_connected = false;

String command;

void serial_communication_setup(){
  Serial.begin(115200);
  #ifdef DEBUG
  Serial.println("Utwente | Human-Robot Communication");
  String name = "This is the robot named {name}";
  name.replace("{name}", robot_name);
  Serial.println(name);
  String version = "Version: {version}";
  version.replace("{version}", robot_version_number);
  Serial.println(version);
  #endif
}

void serial_communication() {
  if(Serial.available()){
    command = Serial.readString();
    command.trim();
  }
  

  process_command(command);
//
//  // data is a string of what we received, we will split it into the different values
//  // We receive multiple values from our PC as in "123,abc,123,"
//  // We can then split this string and extract the values out.
//  if (data.length() > 1 && data.charAt(data.length() - 1) == ',') {
//    Serial.print(data);
//    pc_connected = true; // Once we get a message from the PC, we turn off the touch sensor and do everything with input from the PC
//
//    String value;
//    for (int i = 0; data.length() > 0; i++){
//      value = data.substring(0, data.indexOf(','));
//      data = data.substring(data.indexOf(',') + 1, data.length());
//
//      if (i == 0) servo1_target_pc = value.toInt();
//      if (i == 1) servo2_target_pc = value.toInt();
//      if (i == 2) {
//        if (value == "NEUTRAL") emotion = NEUTRAL;
//        if (value == "SUPRISED") emotion = SUPRISED;
//        if (value == "HAPPY") emotion = HAPPY;
//        if (value == "ANGRY") emotion = ANGRY;
//        if (value == "SAD") emotion = SAD;
//      }
//      // If more values are needed, add other lines here, e.g. if (i == 3) ...
//    }
//  }
}

void process_command(String the_command){
  if(command.length() > 0){
    int break_index = command.indexOf("-");
    //Serial.println(break_index);
    Serial.println(the_command);
    if(break_index != -1){
       String com_header = command.substring(0, break_index);
       com_header.trim();
       com_header.toLowerCase();
       String com_body = command.substring(break_index + 1);
        com_body.trim();
        com_body.toLowerCase();
      #ifdef DEBUG
        if (com_header.equals("debug")){
          handle_debug_command(com_body);
        }
      #else
        if (com_header.equals("debug")){
          //Serial.println("Debugging is disabled");
        }
      #endif //DEBUG
        else if (com_header.equals("s")){
          say(com_body);
        } 
//        else if (com_header.equals("emotion")){
//          change_emotions(com_body);
//        } 
//        else if (com_header.equals("move")){
//          do_movement(com_body);
//        }
        else {
          Serial.println("I don't understand this command type");
          Serial.println(com_header);
        }
    } else {
      Serial.println("malformed command");
    }
  }
  command = "";
}
