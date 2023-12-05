#include <NewPing.h>

/*pinos sensor
vcc -> laranja
trig -> branco
echo -> azul escuro
gnd -> azul claro

*/
#define TRIGGER_PIN  12  //    Arduino pin tied to trigger pin on the ultrasonic sensor. 
#define ECHO_PIN     13  // Arduino pin tied to echo pin on the ultrasonic sensor. 
#define MAX_DISTANCE 40  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
     
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int IN1 = 4 ;
int IN2 = 2 ;
#define pCONTROLE    3   // Define a porta de saída pro PWM [testar com um led]

void setup() {
  Serial.begin(9600);
}

int i = 0;
int distancia[500];

void loop() {

// Lê altura
distancia[i] = sonar.ping_cm();

if(distancia[i] == 0) {
  distancia[i] = distancia[i-1];
}
 delay(90);
 Serial.println(distancia[i]);

 i = i+1;
}
