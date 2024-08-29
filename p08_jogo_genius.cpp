// Declaração de Constantes
#define rodadas 6
#define meioSegundo 500
#define segundo 1000
#define portaBuzzer 9
#define frequenciaBuzzer 500

// Declaração de Array - Armazenar os Pinos dos LEDs
int portasLed[] = {13, 12, 11, 10};

// Declaração de Array - Armazenar os Pinos dos Botões
int portasBotoes[] = {5, 4, 3, 2};

// Declaração de Array - Armazenar a Sequência do Jogo
int sequenciaJogo[rodadas] = {};

// Declaração de Array - Armazenar as Jogadas do Usuário
int jogadasUsuario[rodadas] = {};

// Declaração de Variáveis Numéricas
int quantidadeLed = sizeof(portasLed) / sizeof(portasLed[0]);
int quantidadeBotoes = sizeof(portasBotoes) / sizeof(portasBotoes[0]);

void setup(){
  
  // Iniciando o Monitor Serial
  Serial.begin(9600);
  
  // Configurando o Buzzer
  pinMode(portaBuzzer, OUTPUT);
  
  // Inicializando o Gerador de Números Aleatórios
  randomSeed(analogRead(A0));
  
  // Configurando os Botões
  configuraBotoes();
  
  // Configurando os LEDs
  configuraLed();

  // Sorteando a Sequência do Jogo
  sorteioSequencia();
  
  // Exibindo a Sequência do Jogo
  for (int i = 0; i < rodadas; i++){
    piscaLed(sequenciaJogo[i]);    
  }
 
}

void loop(){ 
  
  // Realizando a Leitura dos Botões - O Usuário Realiza as Jogadas
  leituraBotoes(); 
  
  // Exibindo o Resultado
  if (resultadoJogo()){
    Serial.println("Voce venceu!");
    fimJogo(HIGH);
  }
  
  else {
    Serial.println("Voce perdeu!");
    fimJogo(LOW);
    ligaBuzzer(frequenciaBuzzer);
  }
  
}

// Função para Configuração dos Botões
void configuraBotoes(){
  
  for (int i = 0; i < quantidadeBotoes; i++){
  	pinMode(portasBotoes[i], INPUT);
  }

}

// Função para Configuração dos LEDs
void configuraLed(){
  
  for (int i = 0; i < quantidadeLed; i++){
   	pinMode(portasLed[i], OUTPUT);
  }

}

// Função para Sortear a Sequência do Jogo
void sorteioSequencia(){
  
  for (int i = 0; i < rodadas; i++){
    sequenciaJogo[i] = portasLed[random(0, quantidadeLed)];
  }
  
}

// Função para Verificação de Botão Acionado
void leituraBotoes(){
  
  for (int i = 0; i < rodadas; i++){
    
    bool jogadaRegistrada = false;
    
    while (!jogadaRegistrada){
      
      for (int j = 0; j < quantidadeBotoes; j++){
        
        if (digitalRead(portasBotoes[j]) == HIGH){
          
          jogadasUsuario[i] = portasLed[j];
          jogadaRegistrada = true;
          delay(segundo); 
          
        }
        
      }
    
    }
    
  }
  
}

// Função para Acender e Apagar o LED
void piscaLed(int porta){
  
  digitalWrite(porta, HIGH);
  delay(segundo);
  digitalWrite(porta, LOW);
  delay(segundo);

}

// Função para Verificar se o Usuário Venceu ou Perdeu
bool resultadoJogo(){

  for (int i = 0; i < rodadas; i++){
    
    if (sequenciaJogo[i] != jogadasUsuario[i]){
      return false;
    }
  
  }
  
  return true;

}

// Função para Exibir para o Usuário o Resultado do Jogo
void fimJogo(int estado){
  
  for (int i = 0; i < quantidadeLed; i++){
    digitalWrite(portasLed[i], estado);
  }

}

// Função para Ativar o Buzzer - Caso Tenha Perdido
void ligaBuzzer(int frequencia){
  tone(portaBuzzer, frequencia);
  delay(segundo);
}