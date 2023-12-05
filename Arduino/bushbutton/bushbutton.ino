
int pushbutton1 = 7; 
int pushbutton2 = 8; 
int pushbutton3 = 9; 
int var;

void setup()
{
   Serial.begin(9600);
  pinMode(pushbutton1, INPUT_PULLUP);
  pinMode(pushbutton2, INPUT_PULLUP);
  pinMode(pushbutton3, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(pushbutton1) == LOW) 
  {
    Serial.print("ola");
  }
  if (digitalRead(pushbutton2) == HIGH) 
  {
    var=20;
  }
  if (digitalRead(pushbutton3) == HIGH) 
  {
    var=30;
  }
         
        
}
