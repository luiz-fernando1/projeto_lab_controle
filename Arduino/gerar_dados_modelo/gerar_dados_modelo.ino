#include <NewPing.h>

/*pinos sensor
vcc -> laranja
trig -> branco
echo -> azul escuro
gnd -> azul claro

*/
#define TRIGGER_PIN 7  //    Arduino pin tied to trigger pin on the ultrasonic sensor. 
#define ECHO_PIN 6     // Arduino pin tied to echo pin on the ultrasonic sensor. 
#define MAX_DISTANCE 40  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
     
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int IN1 = 3 ;
int IN2 = 2 ;
#define pCONTROLE 9   // Define a porta de saída pro PWM [testar com um led]


void setup() {
  Serial.begin(9600);

  //pinMode(vel, INPUT);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(pCONTROLE, OUTPUT);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}


long lastTime1 = 0;
int PWM = 0;
// Correção da leitura sensor
int i = 0;
int distancia[500];


void loop() {

// Lê altura
distancia[i] = sonar.ping_cm();

if(distancia[i] == 0) {
  distancia[i] = distancia[i-1];
}

 analogWrite(pCONTROLE, PWM);
 long nowTime = millis();

  if (nowTime  > 1000){

  PWM = 200;
    if(nowTime > 15000){
      PWM = 110;
    }
      if(nowTime > 20000){
      PWM = 200;
    }
      if(nowTime > 35000){
      PWM = 110;
    
    }
  } 
        delay(20);
        Serial.print(PWM);
        Serial.print("\t");
        Serial.print(38-distancia[i]);
        Serial.print("\t");
        Serial.println(nowTime);
  i = i+1;
}
