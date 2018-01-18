const int BUTTON_PIN = 8;
const int LED_PIN[] = {3,5,6};
const int PHOTO_PIN = 0;

const int BAUD = 9600;
String cmd = "";

bool state[] = {0,0,0};
int photoVal = 0;

bool cmdReady = false;
bool readSerial();

void setup(){

  Serial.begin(BAUD);
  cmd.reserve(200);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  for (int i = 0; i < 3; i++){
    pinMode(LED_PIN[i], OUTPUT);
    digitalWrite(LED_PIN[i], HIGH);
    delay(1000);
  }

}

void loop() {
  photoVal = map(analogRead(PHOTO_PIN), 250, 930, 590, 0);
  Serial.println(photoVal);
  delay(10);

  if (readSerial()) {
      if (!cmd.compareTo("high1")) 
        state[0] = HIGH;
      else if (!cmd.compareTo("low1"))
         state[0] = LOW;
      else if (!cmd.compareTo("high2"))
         state[1] = HIGH;
      else if (!cmd.compareTo("low2"))
         state[1] = LOW;
      else if (!cmd.compareTo("high3"))
         state[2] = HIGH;
      else if (!cmd.compareTo("low3"))
         state[2] = LOW;
  }

  for (int i = 0; i < 3; i++){
    digitalWrite(LED_PIN[i], state[i]);
  }
}

bool readSerial() {
  char c;
    // first, clear string if this is new
   if (cmdReady) {
      cmd = "";
      cmdReady = false;
   }
   while (Serial.available()) {
      // get the new byte:
      c = (char) Serial.read();
      if (c == '\r') continue;  // ignore cr 
      // a newline indicates command is complete so process
      if (c == '\n') {
        cmd.trim(); // remove leading and trailling whitespace
        cmdReady = true;
        break;  // exit reading since we have a command ready
      }
      // else add it to the command string
      cmd += c;
   }
   return cmdReady;
}
