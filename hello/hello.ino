boolean playing = false;
boolean getName = true;
String name = "";
boolean getConvincingLine = false;
String convincingLine = "";
boolean getDesperateLine = false;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);  // 115200
   Serial.println("Press enter to begin.");
}

void loop() {
  
 if(Serial.available())
  {
    if (!playing){
      // Since a string reads as true, 
      playing = Serial.readString();
      getName = true;
    }
    
    if (getName){
      Serial.println("What is your name?");
      name = Serial.readString();
      if (name.length()>=1){
        Serial.println(name);
        getName = false;
        getConvincingLine = true;
      }
    }

    if (getConvincingLine){
      Serial.println("*You have reached the spaceship airlock, and want to open the doors. What do you say to Hal?*");
      convincingLine = Serial.readString();
      if (convincingLine.length()>=1){
        Serial.println(convincingLine); 
        Serial.println("I'm sorry, ");
        Serial.print(name);
        Serial.println(", I'm afraid I can't do that");
        convincingLine = "";
        delay(2000);
        getConvincingLine = false;
        getDesperateLine = true;
      }
    }
    if (getDesperateLine){
      getDesperateLine = false;
      Serial.println("*That's not good. What can you say to Hal to get him to open up the airlock?*");
      convincingLine = Serial.readString();
      if (convincingLine.length()>=1){
        Serial.println(convincingLine); 
        convincingLine = "";
        delay(2000);
        Serial.println("I think you know what the problem is just as well as I do.");
        delay(2500);
        Serial.println("This conversation can serve no purpose anymore. Goodbye.");
        Serial.println("*You hear a click and the line drops. Hal won't talk to you. You slowly drift away into the black.*");
        getDesperateLine = false;
        playing = false;
      }

    }
        
  }
}
