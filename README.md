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

__O código com a lógica adotada pelo grupo se encontra no presente reposítório e o resultado pode ser assistido no vídeo alocado neste link: [Aplicação U4C4O12T - Contador na Matriz de LED](https://www.youtube.com).__

## Instruções de Uso

### 1. Clone o repositório
Abra o terminal e execute o comando abaixo para clonar o repositório em sua máquina:
```bash
git clone https://github.com/LucasCarneiro3301/U4C4O12T.git
```

### 2. Configure o ambiente de desenvolvimento
Certifique-se de que o [SDK do Raspberry Pi Pico](https://github.com/raspberrypi/pico-sdk) esteja instalado e configurado corretamente no seu sistema.

### 3. Compile o projeto
Navegue até o diretório raiz do projeto e execute os comandos abaixo:
```bash
mkdir build
cd build
cmake ..
make
```

### 4. Conexão com a Rapberry Pico
1. Conecte o Raspberry Pi Pico ao seu computador via USB.
2. Inicie o modo de gravação pressionando o botão **BOOTSEL** e **RESTART**.
3. O Pico será montado como um dispositivo de armazenamento USB.
4. Execute através do comando **RUN** a fim de copiar o arquivo `ws2812.uf2` para o Pico.
5. O Pico reiniciará automaticamente e executará o programa.

### 5. Observações (IMPORTANTE !!!)
1. Embora o projeto seja compativel com a extensão Wokwi, a **intensidade** dos LEDs está adaptada para a placa BitDogLab! Logo, a visualização no ambiente de simulação não está perfeitamente adequada.
2. Manuseie a placa com cuidado.

## Recursos e Funcionalidades

### 1. Botões

<div align="center">
| BOTÃO                            | DESCRIÇÃO                                     | 
|:----------------------------------:|:---------------------------------------------:|
| A                                  | Incrementa em uma unidade                   | 
| B                                  | Decrementa em uma unidade               | 
</div>

### 2. LED RGB Vermelho

Pisca continuamente 5 vezes por segundo

### 3. Matriz de LEDs 5x5

Ilustra o número atual do contador. A contagem é cíclica entre 0 e 9, ou seja, se decrementar 0 o resultado é 9, e se incrementar 9 o resultado é 0.

### 4. Monitor Serial

É possível acompanhar o contador através do monitor do computador via conexão serial






