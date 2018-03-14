
/* Athor: Md. Khairul Alam
   Date: 1 September, 2016
   This program is for smart lamp */
String inputString = "";
boolean stringComplete = false; 
int brightness=0, red=0, green=0, blue=0; //common cathode
//int brightness=0, red=255, green=255, blue=255; //for common anode
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int whitePin = 6;
int off = 0;
int color = 0;
int white = 0;

void setup(){
 
  Serial.begin(9600);  // baud rate is 9600 must match with bluetooth 
  //The String reserve() function allows you to allocate a buffer in memory for manipulating strings.
  inputString.reserve(50);  // reserve 50 bytes in memory to save for string manipulation 
  boolean stringOK = false;

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(whitePin, OUTPUT);  
 
}
void loop(){
  if (stringComplete) {
    //  Serial.println(inputString);
        int value = inputString.toInt();
        if(value >= 0 && value <=255)
          brightness = value;
        else if(value>=256 && value<=511)
          red = value - 255;
        else if(value>=512 && value<=766)
          green = value - 512;
        else if(value>=767 && value<=1023)
          blue = value - 767;
        else if(value==1111){  // number 1111 does not mean anything
                               // just use any unique number and must be same as android app
          Serial.print("off button pressed");
          off = 1;
          white = 0;
          color = 0;
          }
        else if(value==2222){
          Serial.print("white button pressed");
          white = 1;
          off = 0;
          color = 0;
          }
        else if(value==3333){
          Serial.print("color button pressed");
          color = 1;
          white = 0;
          off = 0;
          }
         else if(value==4444){
          Serial.print("red");
          red = 255;
          green = 0;
          blue = 0;
          }
         else if(value==5555){
          Serial.print("green");
          red = 0;
          green = 255;
          blue = 0;
          }
        else if(value==6666){
          Serial.print("green");
          red = 0;
          green = 0;
          blue = 255;
          }
        else if(value==7777){
          Serial.print("megenta");
          red = 255;
          green = 0;
          blue = 255;
          }
        else if(value==8888){
          Serial.print("cyan");
          red = 0;
          green = 255;
          blue = 255;
          }
        else if(value==9999){
          Serial.print("yelow");
          red = 255;
          green = 255;
          blue = 0;
          }
        else if(value==1700){
          Serial.print("pink");
          red = 255;
          green = 105;
          blue = 180;
          }
        else if(value==2700){
          Serial.print("violet");
          red = 238;
          green = 130;
          blue = 238;
          }
       Serial.print(red);
       Serial.print(":");
       Serial.print(green);
       Serial.print(":");
       Serial.println(blue);
       inputString = "";
       stringComplete = false;
    }
  if(color==1){
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);
      analogWrite(whitePin, 0);
    }  
  if(white==1){
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      analogWrite(whitePin, brightness);
    }
  if(off==1){
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      analogWrite(whitePin, 0);
    }
 /* for common anode
    if(color==1){
      analogWrite(redPin, 255-red);
      analogWrite(greenPin, 255-green);
      analogWrite(bluePin, 255-blue);
      analogWrite(whitePin, 0);
    }  
  if(white==1){
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 255);
      analogWrite(whitePin, brightness);
    }
  if(off==1){
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 255);
      analogWrite(whitePin, 0);
    }
  */
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    //Serial.write(inChar);
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline or a carriage return, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n' || inChar == '\r') {
      stringComplete = true;
    } 
  }
}

