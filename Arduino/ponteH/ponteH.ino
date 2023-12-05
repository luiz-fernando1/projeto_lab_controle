

int IN1 = 2 ;
int IN2 = 4 ;
int velocidadeA = 3;

//variavel auxiliar
int velocidade = 200;

void setup(){
Serial.begin(9600);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(velocidadeA,OUTPUT);
}

void loop(){

//Sentido 2
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);

analogWrite(velocidadeA,150);
}
