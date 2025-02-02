# U4C4O12T
Repositório para a atividade da unidade 4 e capítulo 4:  Interrupções.

__Aluno:__
Lucas Carneiro de Araújo Lima

## ATIVIDADE 
__Descrição:__
O projeto utiliza a placa BitDogLab com uma matriz 5x5 de LEDs WS2812, um LED RGB e dois botões. O LED vermelho do RGB deve piscar 5 vezes por segundo. O botão A incrementa e o botão B decrementa o número exibido na matriz de LEDs, que deve representar os números de 0 a 9.

__Para este trabalho, os seguintes componentes e ferramentas se fazem necessários:__
1) Microcontrolador Raspberry Pi Pico W.
2) Matriz de LEDs Coloridos (LED-RGB 5x5 WS2812).
3) Ambiente de trabalho VSCode.
4) Ferramenta educacional BitDogLab.
5) Botões A e B

__O resultado do projeto pode ser assistido através deste link: [Aplicação U4C4O12T - Contador na Matriz de LED](https://youtu.be/AJNJWrppGwU).__

<div align="center">
  <img src="https://github.com/user-attachments/assets/45ee39ff-bf4a-4fbb-897b-3f30eb7b1b9b" alt="GIF demonstrativo" width="300"/>
</div>

## Instruções de Uso

### 1. Clone o repositório
Abra o terminal e execute o comando abaixo para clonar o repositório em sua máquina:
```bash
git clone https://github.com/LucasCarneiro3301/U4C4O12T.git
```

### 2. Configure o ambiente de desenvolvimento
Certifique-se de que o [SDK do Raspberry Pi Pico](https://github.com/raspberrypi/pico-sdk) esteja instalado e configurado corretamente no seu sistema.

### 3. Conexão com a Rapberry Pico
1. Conecte o Raspberry Pi Pico ao seu computador via USB.
2. Inicie o modo de gravação pressionando o botão **BOOTSEL** e **RESTART**.
3. O Pico será montado como um dispositivo de armazenamento USB.
4. Execute através do comando **RUN** a fim de copiar o arquivo `ws2812.uf2` para o Pico.
5. O Pico reiniciará automaticamente e executará o programa.

### 4. Observações (IMPORTANTE !!!)
1. Embora o projeto seja compativel com a extensão Wokwi, a **intensidade** dos LEDs está adaptada para a placa BitDogLab! Logo, a visualização no ambiente de simulação não está perfeitamente adequada.
2. Manuseie a placa com cuidado.

## Recursos e Funcionalidades

### 1. Botões

| BOTÃO                            | DESCRIÇÃO                                     | 
|:----------------------------------:|:---------------------------------------------:|
| A                                  | Incrementa em uma unidade                   | 
| B                                  | Decrementa em uma unidade               | 

### 2. LED RGB Vermelho

Pisca continuamente 5 vezes por segundo

### 3. Matriz de LEDs 5x5

Ilustra o número atual do contador. A contagem é cíclica entre 0 e 9, ou seja, se decrementar 0 o resultado é 9, e se incrementar 9 o resultado é 0.

### 4. Monitor Serial

É possível acompanhar o contador através do monitor do computador via conexão serial

### 5. Interrupções

O programa implementa interrupção nos botões A e B. Dessa forma, não é necessário ler continuamente o estado de cada botão.

### 6. Deboucing

O programa implementa tratamento de boucing (via software). Dessa forma, evita leituras falsas de botões causadas por oscilações elétricas, garantindo que cada pressionamento seja registrado apenas uma vez,






