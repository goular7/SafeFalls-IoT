#include <LiquidCrystal.h> //Carrega a biblioteca LiquidCrystal  
 
const int pinSensornivel = 9; // Define o pino do sensor de nível 
const int pinSensorchuva = A5; // Define o pino do sensor de chuva 
const int ledg = 6; // Define o pino do led verde 
const int ledy = 7; // Define o pino do led amarelo 
const int ledr = 8; // Define o pino do led vermelho 
const int alarme = 13; // Define o pino do alarme 
int chuva = 0; // Variável chuva inicia em 0  
int nivel = 0; // Variável nível inicia em 0

//Define os pinos que serão utilizados para ligação do display  
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
 
void setup()
{
  lcd.begin(16, 2);               // Inicia LCD 
  pinMode(pinSensorchuva, INPUT); // Define o sensor de chuva como entrada 
  pinMode(pinSensornivel, INPUT); // Define o sensor de nível como entrada 
  pinMode(ledg, OUTPUT); // Define o led verde como saída 
  pinMode(ledy, OUTPUT); // Define o led amarelo como saída
  pinMode(ledr, OUTPUT); // Define o led vermelho como saída
  pinMode(alarme, OUTPUT);// Define o alarme como saída
  Serial.begin(9600); // Inicia o monitor serial a 9600 baud 
  lcd.setCursor(0,0); // Define onde o cursor irá escrever no LCD
  lcd.print("Nivel: "); // Imprime a palavra "Nível: "
  lcd.setCursor(0,1); // Define onde o cursor irá escrever no LCD
  lcd.print("Chuva: "); // Imprime a palavra "Chuva: "
}
 
void loop()
{  
  nivel = digitalRead(pinSensornivel); // Armazena o valor da leitura digital (0 ou 1) na variável nível 
  chuva = analogRead(pinSensorchuva); // Armazena o valor da leitura analógica (0 a 1023) na variável chuva 
  Serial.print("Valor digital : "); // Imprime "Valor digital: " no monitor serial 
  Serial.print(nivel);              // Imprime o valor da variável nível no monitor serial 
  Serial.print(" - Valor analogico : "); // Imprime " - Valor analogico: " no monitor serial
  Serial.println(chuva);                // Imprime o valor da variável chuva no monitor serial
  if (chuva <= 250)  // Pergunta se está chovendo 
  {
    lcd.setCursor(7,1);        
    lcd.print("         ");     // Limpa o que estava escrito anteriormente no LCD  
    lcd.setCursor(7,1);         // Imprime "Sem Chuva"
    lcd.print("Sem Chuva");     // No LCD
    if (nivel == 0)         // Pergunta se o sensor de nível está em 0 
    {
      lcd.setCursor(7,0);
      lcd.print("      "); // Limpa o que estava escrito anteriormente no LCD
      lcd.setCursor(7,0);
      lcd.print("Vazio");       // Imprime vazio e acendo o led ver e desliga os outros e o alarme 
      digitalWrite(ledg, HIGH);
      digitalWrite(ledy, LOW);
      digitalWrite(ledr, LOW);
      digitalWrite(alarme,LOW);
    }else
    {
      lcd.setCursor(7,0);
      lcd.print("      "); // Limpa o que estava escrito anteriormente no LCD
      lcd.setCursor(7,0);
      lcd.print("Cheio");       // Imprime cheio e liga o led vermelho e o alarme e apaga os outros 
      digitalWrite(ledr, HIGH);
      digitalWrite(ledy, LOW);
      digitalWrite(ledg, LOW);
      digitalWrite(alarme,HIGH);
    }  
  }else
  {
    if(nivel == 0)            // Pergunta se o sensor de nível está em 0 
    {
      lcd.setCursor(7,0);
      lcd.print("      "); // Limpa o que estava escrito anteriormente no LCD
      lcd.setCursor(7,0);
      lcd.print("Vazio");      // Imprime "Vazio" e acende o led amarelo e desliga os outros e o alarme 
      digitalWrite(ledg, LOW);
      digitalWrite(ledy, HIGH);
      digitalWrite(ledr, LOW);
      digitalWrite(alarme,LOW);
    }else
    {
      lcd.setCursor(7,0);
      lcd.print("      "); // Limpa o que estava escrito anteriormente no LCD
      lcd.setCursor(7,0);
      lcd.print("Cheio");      // Imprime "Cheio" e liga o led vermelho e o alarme e apaga os outros 
      digitalWrite(ledr, HIGH);
      digitalWrite(ledy, LOW);
      digitalWrite(ledg, LOW);
      digitalWrite(alarme,HIGH);
    }  
    if (chuva > 750 && chuva <= 1023) // Pergunta se a chuva está forte 
    {
      lcd.setCursor(7,1);
      lcd.print("         "); // Limpa o que estava escrito anteriormente no LCD
      lcd.setCursor(7,1);
      lcd.print("Forte"); // Imprime "Forte"
    }
    if (chuva > 500 && chuva <= 750) // Pergunta se a chuva está moderada 
    {
      lcd.setCursor(7,1);
      lcd.print("         "); // Limpa o que estava escrito anteriormente no LCD
      lcd.setCursor(7,1);
      lcd.print("Moder."); // Imprime "Moder."
    }
    if (chuva > 250 && chuva <= 500) // Pergunta se a chuva está fraca 
    {
      lcd.setCursor(7,1);
      lcd.print("         "); // Limpa o que estava escrito anteriormente no LCD
      lcd.setCursor(7,1);
      lcd.print("Fraca");   // Imprime "Fraca"
    }
  }  
  delay(1000); // Aguarda 1s até voltar para o início do loop 
}