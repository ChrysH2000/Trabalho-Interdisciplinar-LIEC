// Inclusão das bibliotecas do sensor DHT22 (Medida de Humidade e temperatura)
#include <DHT.h>
#define DHT_PIN 2 // Define o pino 2 do arduino como o do sensor DHT22
#define DHTTYPE DHT22 // Define o modelo do sensor DHT
#define INTERVALO 5000 // Define um valor para servir como delay entre as leitura do sensor DHT

// Cria um objeto para o sensor DHT22
DHT dht(DHT_PIN, DHTTYPE);

// Procedimento executado apenas uma vez durante o funcionamento
void setup() {
  // Inicializa a serial do arduino e printa a mensagem
  Serial.begin(9600);
  Serial.println("INICIANDO SISTEMA");
  dht.begin();
}

//Procedimento que transmite os dados obtidos da temperatura em graus Celsius via bluetooth
void TemperaturaC (float t){
  Serial.print("C ");
  Serial.print(t);
  Serial.println("º");
}
//Procedimento que transmite os dados obtidos da umidade via bluetooth
void Umidade (float h){
  Serial.print("U ");
  Serial.print(h);
  Serial.println("%");
}
//Procedimento que transmite os dados obtidos da temperatura em Fahreinheit via bluetooth
void TemperaturaF (float f){
  Serial.print("F ");
  Serial.print(f);
  Serial.println("º");
  Serial.println();
}

//Procedimento que fica em loop durante a execução do programa
void loop() {
// Cria variáveis que irão receber os dados do sensor
  float h = 0, t = 0, f = 0; // h-> Umidade; t-> Temperatura em Celsius; f-> Temperatura em Fahrenheit 
  float lum = 0; // lum-> luminosidade

  // Variáveis recebem dados do sensor DHT
  h = dht.readHumidity(); // Recebe a umidade
  t = dht.readTemperature(); // Recebe a temperatura em graus Celsius
  f = dht.readTemperature(true); // Converte a temperatura para graus Farenheit

  // Elimina resultados indesejados
  if(t == 0 || h == 0){
    Serial.println(F("Falha na leitura do sensor"));
  }
  // Se estiver tudo ok com a leitura, transmite os dados via bluetooth
  else{
    TemperaturaC(t); // Temperatura em graus Celsius
    Umidade(h); // Umidade
    TemperaturaF(f); // Temperatura em Farenheit

    //Transmite os dados de luminosidade via bluetooth
    lum = analogRead(A5); //Se o sensor estiver conectado a um pino analogico
    Serial.println("l");
    Serial.println(lum);
  }

  //Inicializa as luzes do sensor, mantendo-as apagadas inicialmente
  digitalWrite(13, LOW); //Luz Verde
  digitalWrite(12, LOW); //Luz Vermelha
  digitalWrite(11, LOW); //Luz azul
  digitalWrite(10, LOW);//Buzzer
  //delay(500); (Comando de intervalo)

  //Acende a luz verde do RGD quando a umidade e temperatura estão adequadas para seres humanos 
  //Umidade entre 50% a 60% | Temperatura entre 20ºC e 26ºC
  if (h >= 50 && h <= 60 && t >= 20 && t <= 26){
    digitalWrite(13,HIGH);
  }
  //Acende a luz vermelha do RGD se a temperatura estiver em um nível não adequado para seres humanos
  //Temperatura abaixo de 20ºC ou acima de 26ºC
  else if (t < 20 || t > 26){
    digitalWrite(12, HIGH);    
  }
  //Acende a luz azul do RGD se a umidade estiver em um nivel não adequado para seres humanos
  //Umidade menor que 50% ou maior que 60%
  else if (h < 50 || h > 60){
    digitalWrite(11, HIGH);
  }
  //Liga o Buzer, caso umidade esteja em um nivel não adequado para seres humanos
  //Leitura de Luminosidade abaixo de 500
  if (lum <500){
  // if (h < 50 || h > 60){
    digitalWrite(10, HIGH);
    Serial.print("B");
    Serial.println();
  }
  
  // Espera o intervalo definido para fazer a próxima leitura
  delay(INTERVALO);  
}
