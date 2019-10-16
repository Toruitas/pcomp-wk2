void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200); 
   Serial.println("what's your name?");
}

void loop() {


 if(Serial.available()) 
 {
   Serial.print("Hello "); //this will read serial data 
    String s = Serial.readString(); 
   Serial.println(s); 
 }
}
