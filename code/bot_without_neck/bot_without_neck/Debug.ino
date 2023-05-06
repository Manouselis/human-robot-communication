void handle_debug_command(String command){
  int break_index = command.indexOf("-");
  if(break_index != -1){
    String com_header = command.substring(0, break_index);
    com_header.trim();
    com_header.toLowerCase();
    String com_body = command.substring(break_index + 1);
    com_body.trim();
    com_body.toLowerCase();

    if (com_header.equals("eyes")){
//      pixels.clear();  
//       if(com_body.equals("neutral")){
//         display_eyes(neutral, 125);
//       } 
//       pixels.show();
    } else {
      Serial.println("I don't understand this debug command type");
      Serial.println(com_header);
    }
  }
}
