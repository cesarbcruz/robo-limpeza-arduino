// Programa : Robo Limpeza com Arduino
// Autor : César Cruz
 
#include <AFMotor.h>

AF_DCMotor motor_dianteiro(1);
AF_DCMotor motor_aspirador(2);
AF_DCMotor motor_traseiro_esquerdo(3);
AF_DCMotor motor_traseiro_direiro(4);
const int sensor_direito = 30;
const int sensor_esquerdo = 31;

 
void setup()
{
  Serial.begin(9600);
  motor_dianteiro.setSpeed(255);
  motor_aspirador.setSpeed(255);
  motor_traseiro_esquerdo.setSpeed(255);
  motor_traseiro_direiro.setSpeed(255);
  pinMode(sensor_esquerdo, INPUT);
  pinMode(sensor_direito, INPUT);
  
  motor_dianteiro.run(FORWARD);
  motor_aspirador.run(FORWARD);
}
 
void loop()
{   
  boolean virarParaEsquerda = digitalRead(sensor_esquerdo) == HIGH;
  boolean virarParaDireita = digitalRead(sensor_direito) == HIGH;

  if(virarParaEsquerda && virarParaDireita){
    Serial.println("Para atras depois para direita");
    ligarMotoresTraseiro(BACKWARD);
    delay(1000);
    virarDireita();
    delay(1000);    
  }else if(virarParaDireita){
    Serial.println("Virar Para direita");   
    virarDireita();
    delay(1000);
  }else if(virarParaEsquerda){
    Serial.println("Virar Para esquerda");
    virarEsquerda();
    delay(1000);
  }else{
    ligarMotoresTraseiro(FORWARD);  
    Serial.println("Para frente");
    delay(10);
  }
}

void ligarMotoresTraseiro(int direcao){
  motor_traseiro_esquerdo.run(direcao);
  motor_traseiro_direiro.run(direcao);
}

void desligarMotoresTraseiro(){
    motor_traseiro_esquerdo.run(RELEASE);
    motor_traseiro_direiro.run(RELEASE);
}

void virarDireita(){
  desligarMotoresTraseiro();
  motor_traseiro_esquerdo.run(FORWARD);
  motor_traseiro_direiro.run(BACKWARD);
}

void virarEsquerda(){
  desligarMotoresTraseiro();
  motor_traseiro_esquerdo.run(BACKWARD);
  motor_traseiro_direiro.run(FORWARD);
}
