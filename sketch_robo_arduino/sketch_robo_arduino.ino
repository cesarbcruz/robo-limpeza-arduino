// Programa : Robo Limpeza com Arduino
// Autor : César Cruz
 
#include <AFMotor.h>

AF_DCMotor motor_dianteiro(1);
AF_DCMotor motor_aspirador(2);
AF_DCMotor motor_traseiro_esquerdo(3);
AF_DCMotor motor_traseiro_direiro(4);
const int sensor_direito = 30;
const int sensor_esquerdo = 31;
String ultima_acao = "";
long inicio_acao = 0;
long tempo_maximo_acao = 10000;
long tempo_minimo_acao = 2000;

 
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
  String nova_acao = "";

  if(virarParaEsquerda && virarParaDireita){
    nova_acao = "Para atras depois para direita";
    ligarMotoresTraseiro(BACKWARD);
    delay(1000);
    virarDireita();
    delay(1000);
  }else if(virarParaDireita){
    nova_acao =  "Virar Para direita";   
    virarDireita();
    if(millis() - inicio_acao < tempo_minimo_acao){
      Serial.println("tempo extra para rotacao para direita");
      delay(2000);      
    }else{
      delay(1000);
    }
  }else if(virarParaEsquerda){
    nova_acao = "Virar Para esquerda";
    virarEsquerda();
    if(millis() - inicio_acao < tempo_minimo_acao){
      Serial.println("tempo extra para rotacao para esquerda");
      delay(2000);      
    }else{
      delay(1000); 
    }
  }else{
    nova_acao = "Para frente";
    ligarMotoresTraseiro(FORWARD);  
    delay(10);
  }
  
  if(nova_acao == ultima_acao){

    if(millis() - inicio_acao > tempo_maximo_acao){
      ultima_acao = "Seguranca: Ir para atras depois para esquerda";
      desligarMotoresTraseiro();
      delay(1000);
      ligarMotoresTraseiro(BACKWARD);
      delay(1000);
      virarEsquerda();
      delay(2000);
      inicio_acao = millis();
    }
    
  }else{
    ultima_acao = nova_acao;
    inicio_acao = millis();
  }
  
  Serial.println(ultima_acao);
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
