/*  Starblaster, authored by Julianna Clarke

The following is */

import processing.serial.*;
Serial port;
String input;
int val;
int BAUD = 9600;

int xpos = 200;
int ypos = 10;
int speed = 1;

void setup() {
    port = new Serial(this, "COM3", BAUD);
    port.bufferUntil('\n');
    
    size(600, 600);
}

void draw(){
  background(46, 60, 55);
  
  //draw rectangle
  fill(255, 87, 51);
  stroke(255, 87, 51);
  rect(xpos, ypos, 50, 50);
  
  //get input as a string type cast to int, then clear the string
  while (port.available() > 0) {
    input = port.readStringUntil('\n');
    input = trim(input);
    if (input != null) {
      val=int(input);
    }
    println(val);
  }
  input = "";
  
  //make the yposition the value of the photoresistor
  ypos = val;
  
  //turn the leds on for certain heights, subject to change
  if(ypos > 400){
    port.write("high1"+'\n');
    port.write("high2"+'\n');
    port.write("high3"+'\n');
  }
  else if(ypos > 200 && ypos < 400){
    port.write("high1"+'\n');
    port.write("high2"+'\n');
    port.write("low3"+'\n');
  }
  else{
    port.write("high1"+'\n');
    port.write("low2"+'\n');
    port.write("low3"+'\n');
  }
}