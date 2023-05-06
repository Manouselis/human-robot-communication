#include <SoftwareSerial.h>
#include <MP3Player_KT403A.h>

SoftwareSerial mp3(2, 3);                     // The MP3 module is connected on pins 2 and 3

void mp3_setup(){
  mp3.begin(9600);
  delay(100); // Wait 0.1 seconds for the MP3 player to boot up
  SelectPlayerDevice(0x02);       // Select SD card as the player device.
  SetVolume(0x1E);                // Set the volume, the range is 0x00 to 0x1E.
}
