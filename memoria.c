/*
Este é o algoritmo utilizado para o jogo da memória do cérebro - 
Utilizado na semana de Ciência e Tecnologia da Universidade Estadual do Norte do Paraná

Este código é uma adaptação do jogo "Simon says" (Genius)

Ele é composto por 5 botões:
BT_AZUL na porta de entrada 8;
BT_AMARELO na porta de entrada 12;
BT_VERMELHO na porta de entrada 11;
BT_VERDE na porta de entrada 10;
BT_BRANCO na porta de entrada 9;

O BT_BRANCO é o responsável por inicializar o jogo.

5 LEDS: 
LED_AZUL na porta de saída 6;
LED_AMARELO na porta de saída 5;
LED_VERMELHO na porta de saída 4;
LED_VERDE na porta de saída 3;
LED_BRANCO na porta de saída 2;

Quando a sequência colocada for errada, todos os LEDs piscam por três vezes e o jogo é reinicializado.

Hardware nessários:
5x Botões
1x led Azul
1x led Amarelo
1x led Vermelho
1x Led Verde
1x Led Branco

3x resistores de 82 Ohms
2x resisores de 150 Ohms
10x jumpers
*/

//setando as portas de entradas e saidas
const int MAX_LEVEL = 13;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 0;

const int BT_AZUL = 8;
const int BT_AMARELO = 12;
const int BT_VERMELHO = 11;
const int BT_VERDE = 10;
const int BT_BRANCO= 9;

const int LED_AZUL = 6;
const int LED_AMARELO = 5;
const int LED_VERMELHO = 4;
const int LED_VERDE = 3;
const int LED_BRANCO= 2;

int velocity = 1000;

void setup() {
  
  
  pinMode(BT_AZUL, INPUT_PULLUP); 
  pinMode(BT_AMARELO, INPUT_PULLUP); 
  pinMode(BT_VERMELHO, INPUT_PULLUP); 
  pinMode(BT_VERDE, INPUT_PULLUP); 
  pinMode(BT_BRANCO, INPUT_PULLUP); 

  pinMode(LED_BRANCO, OUTPUT); 
  pinMode(LED_VERDE, OUTPUT);  
  pinMode(LED_VERMELHO, OUTPUT); 
  pinMode(LED_AMARELO, OUTPUT); 
  pinMode(LED_AZUL, OUTPUT);

  digitalWrite(LED_BRANCO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_AZUL, LOW);

}

void loop(){
    
  int btbranco = digitalRead(BT_BRANCO);
  
  if ((btbranco == LOW) and level==0){
    generate_sequence();
  }
  if (level != 0){ 
    //Se o botao de inicializar é pressionado ou esta ganhando...
    show_sequence();    //mostra a sequencia
    get_sequence();     //Espera a entrada do usuario
  }
}

void waiting(){
    digitalWrite(LED_BRANCO, HIGH);
    delay(500);
    digitalWrite(LED_VERDE, HIGH);
    delay(500);
    digitalWrite(LED_VERMELHO, HIGH);
    delay(500);
    digitalWrite(LED_AMARELO, HIGH);
    delay(500);
    digitalWrite(LED_AZUL, HIGH);
    delay(500);
    //delay(500);
    digitalWrite(LED_BRANCO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_AZUL, LOW);
    delay(1000);
  }
  
void show_sequence(){
  digitalWrite(LED_BRANCO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_AZUL, LOW);
  

  for (int i = 0; i < level; i++){
    digitalWrite(sequence[i], HIGH);
    delay(velocity);
    digitalWrite(sequence[i], LOW);
    delay(200);
  }
}

void get_sequence(){
  int flag = 0; //este é um indicador que a sequencia está correta

  for (int i = 0; i < level; i++){
    flag = 0;
    while(flag == 0){
          int btazul = digitalRead(BT_AZUL);
          int btamarelo = digitalRead(BT_AMARELO);
          int btvermelho = digitalRead(BT_VERMELHO);
          int btverde = digitalRead(BT_VERDE);
          int btbranco = digitalRead(BT_BRANCO);
          
          //A0 = azul - 6
          if (btazul == LOW){
                  digitalWrite(LED_AZUL, HIGH);
                  your_sequence[i] = LED_AZUL;
                  flag = 1;
                  delay(500);
                  if (your_sequence[i] != sequence[i]){
                    wrong_sequence();
                    return;
                  }
                  digitalWrite(LED_AZUL, LOW);
          }
          //A1 = amrelo = 5
          if (btamarelo == LOW){
                  digitalWrite(LED_AMARELO, HIGH);
                  your_sequence[i] = 5;
                  flag = 1;
                  delay(500);
                  if (your_sequence[i] != sequence[i]){
                    wrong_sequence();
                    return;
                  }
                  digitalWrite(LED_AMARELO, LOW);
          }
          //a2 = vermelho = 4
          if (btvermelho == LOW){
                  digitalWrite(LED_VERMELHO, HIGH);
                  your_sequence[i] = 4;
                  flag = 1;
                  delay(500);
                  if (your_sequence[i] != sequence[i]){
                    wrong_sequence();
                    return;
                  }
                  digitalWrite(LED_VERMELHO, LOW);
           }
    
           if (btverde == LOW){
                  digitalWrite(LED_VERDE, HIGH);
                  your_sequence[i] = 3;
                  flag = 1;
                  delay(500);
                  if (your_sequence[i] != sequence[i]){
                    wrong_sequence();
                    return;
                  }
                  digitalWrite(LED_VERDE, LOW);
           }
              
           if (btbranco == LOW){
                  digitalWrite(LED_BRANCO, HIGH);
                  your_sequence[i] = 2;
                  flag = 1;
                  delay(500);
                  if (your_sequence[i] != sequence[i]){
                    wrong_sequence();
                    return;
                  }
                  digitalWrite(LED_BRANCO, LOW);
            }

      }//while
    }//for
    right_sequence();
}

void generate_sequence(){
  randomSeed(millis()); //in this way is really random!!!

  for (int i = 0; i < MAX_LEVEL; i++){
    sequence[i] = random(2,7);
    delay(2);
  }
    level = 1;
}

void wrong_sequence(){
  for (int i = 0; i < 1; i++){
      digitalWrite(LED_BRANCO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, HIGH);
      digitalWrite(LED_AMARELO, HIGH);
      digitalWrite(LED_AZUL, HIGH);
      delay(4000);
      digitalWrite(LED_BRANCO, LOW);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, LOW);
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_AZUL, LOW);
      //delay(500);
  }
  level = 0;
  velocity = 1000;
}

void right_sequence(){
    digitalWrite(LED_BRANCO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_AZUL, LOW);
    delay(450);
    digitalWrite(LED_BRANCO, HIGH);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_AZUL, HIGH);
    delay(450);
    digitalWrite(LED_BRANCO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_AZUL, LOW);
    delay(450);

    if (level < MAX_LEVEL);
      level++;

    velocity -= 50; //increase difficulty
}
