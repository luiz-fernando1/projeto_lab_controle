#include <NewPing.h>

class PID{

public:
  double error;
  double sample;
  double lastSample;
  double kP, kI, kD;      
  double P, I, D;
  double pid;  
  double setPoint;
  long lastProcess;

  PID(double _kP, double _kI, double _kD){
    kP = _kP;
    kI = _kI;
    kD = _kD;
  }

  void addNewSample(double _sample){
    sample = _sample;
  }

  void setSetPoint(double _setPoint){
    setPoint = _setPoint;
  }

  double process(){

  error = setPoint - sample;
  
  float deltaTime = (millis() - lastProcess) / 1000.0;
  lastProcess = millis();

   //Serial.print(deltaTime);
   //Serial.print("\t");
  //Proporcional
  P = error * kP;
  
  //Integrador
  I = I + (error * kI) * deltaTime;

  //Derivativo
  D = (lastSample - sample) * kD / deltaTime;

  lastSample = sample;

  // Soma tudo
  pid = P + I + D;
  
  return pid;
  }
};

/*pinos sensor
vcc -> laranja
trig -> branco
echo -> azul escuro
gnd -> azul claro

*/
#define TRIGGER_PIN  12  //    Arduino pin tied to trigger pin on the ultrasonic sensor. 
#define ECHO_PIN     13  // Arduino pin tied to echo pin on the ultrasonic sensor. 
#define MAX_DISTANCE 37  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define pCONTROLE    3   // Define a porta de saída pro PWM [testar com um led]
     
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int controlePwm = 255; //descobrir isso
int aux;
int IN3 = 4 ;
int IN4 = 2 ;

//Push Buttom
int pushbutton1 = 7; 
int pushbutton2 = 8; 
int pushbutton3 = 9;

void setup() {
  Serial.begin(9600);

  pinMode(pushbutton1, INPUT_PULLUP);
  pinMode(pushbutton2, INPUT_PULLUP);
  pinMode(pushbutton3, INPUT_PULLUP);
  
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(pCONTROLE, OUTPUT);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}


// Correção da leitura sensor
int i = 0;
int aux1[100];
long lastTime1 = 0;
int sp = 15;

//Declarando os ganhos encontrado
//PID meuPid(1.7323, 4.6097/2, 0.16275);
//PID meuPid(4.3778, 5.2536/2, 0);
PID meuPid(6.9, 3, 0);

void loop() {

    // Leitura do sensor
    int sensor = sonar.ping_cm();

    //Solução para valores lido como ZERO
    aux1[i] = sensor;
    if(sensor == 0) {
      sensor = aux1[i-1];
      aux1[i]= aux1[i-1];
      //i = 0;
    }
   
    int distancia = 38-sensor; // isso para converter a distancia do sensor para altura no tubo
    

    // SetPoint por PushButton
      if (digitalRead(pushbutton1) == HIGH){
        sp=15;
      }
      if (digitalRead(pushbutton2) == HIGH){
        sp=20;
      }
      if (digitalRead(pushbutton3) == HIGH){
        sp=30;
      }
      
      meuPid.setSetPoint(sp);
    
      // Manda pro objeto PID!
      meuPid.addNewSample(distancia);
    
      // Converte para controle
      controlePwm = (meuPid.process()); //mudar de acordo com o valor acima
      if(controlePwm > 255)
        aux = 180;
      else if(controlePwm <= 140 )
        aux = 130;
      else
        aux = controlePwm;
        
      // Saída do controle
      analogWrite(pCONTROLE, aux);
    
       long nowTime = millis();
       if (nowTime - lastTime1 > 1000){
         lastTime1 = nowTime;
         Serial.print("Sinal: ");;
         Serial.print(controlePwm);
         Serial.print("\t");
         Serial.print("PWM: ") ;
         Serial.print(aux);
         Serial.print("\t");
         Serial.print("SetPoint: ") ;
         Serial.print(sp);
         Serial.print("\t");
         Serial.print("  Altura: ");
         Serial.print(distancia);
         Serial.print("\t");
         Serial.print("Erro: ");
         Serial.println(sp-distancia);
       }  

       delay(90);
       
   i = i+1;
  
}
