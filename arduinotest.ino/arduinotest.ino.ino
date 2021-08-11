/*
  String replace()

  Examples of how to replace characters or substrings of a String

  created 27 Jul 2010
  modified 2 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/StringReplace
*/

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // send an intro:
  Serial.println("BEGIN---------------------\n");
  Serial.println();
}


int pending = 0;
String pending_messages = "";

#define CONTROL_CHAR '~'

int pend_message(String cmd) {
  if (cmd.charAt(0) == CONTROL_CHAR && cmd.charAt(cmd.length()-1) == CONTROL_CHAR)
  {
    pending += 1;
    pending_messages += cmd.substring(1, cmd.length());
    return 0;
  } else {
    return -1;
  }
}

int read_message() {
  if (pending > 0 && pending_messages != "")
  {
    int end_first_string = pending_messages.indexOf('~');
    if (end_first_string >= 0)
    {
      String output = pending_messages.substring(0, end_first_string);
      display(output);
      pending_messages.remove(0, end_first_string + 1);
      pending--;
      return 0;
    }
  }
  return -1;
}

int enable_led = 1;
int enable_servo = 1;

int enable(String cmd) {
  if (cmd.length() != 2) {
    return -1;
  } else {
    enable_led = cmd.charAt(0) == '1';
    enable_servo = cmd.charAt(1) == '1';
  }
}

void display(String msg) {
  Serial.println("DISPLAY MESSAGE: -->" + msg + "<--");
}

void loop() {
  pend_message("~MessageOne~");
  pend_message("Invalid");
  pend_message("~MessageTwo~");
  pend_message("~<3~");
  Serial.println(pending_messages);
  int rtrned = read_message();
  rtrned = read_message();
  rtrned = read_message();
  rtrned = read_message();

  Serial.println("LED: " + String(enable_led));
  Serial.println(" Servo: " + String(enable_servo));
  enable("11");

  Serial.println("LED: " + String(enable_led));
  Serial.println(" Servo: " + String(enable_servo));
  enable("10");

  Serial.println("LED: " + String(enable_led));
  Serial.println(" Servo: " + String(enable_servo));
  enable("01");

  Serial.println("LED: " + String(enable_led));
  Serial.println(" Servo: " + String(enable_servo));
  enable("00");
  Serial.println("LED: " + String(enable_led));
  Serial.println(" Servo: " + String(enable_servo));
  enable("11");
  Serial.println("LED: " + String(enable_led));
  Serial.println(" Servo: " + String(enable_servo));
  while (true);
}
