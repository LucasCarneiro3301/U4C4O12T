/*
    Aluno: Lucas Carneiro de Araújo Lima
*/

//Inicialização das bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"
#include "numbers.h"

//Pinagem dos componentes
#define WS2812_PIN 7
#define RED 13
#define GREEN 12
#define BLUE 11
#define BTNA 5
#define BTNB 6

#define NUM_PIXELS 25
#define IS_RGBW false

static void gpio_irq_handler(uint gpio, uint32_t events); // Prototipação da função de interrupção

static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

unsigned short int counter = 0;

// Configura a matriz de LED conforme uma cor especificada
void set_leds_from_color(PIO pio, uint sm, uint32_t cor) {
  for (int16_t i = 0; i < NUM_PIXELS; i++) {
    pio_sm_put_blocking(pio, sm, cor);
  }
}

// Inicializa e configura os LEDs RGB como saída. Inicializa e configura os botões como entradas.
void setting_inputs_and_outputs() {
    gpio_init(RED);
    gpio_set_dir(RED, GPIO_OUT); 
    gpio_put(RED, false);

    gpio_init(BTNA);
    gpio_set_dir(BTNA, GPIO_IN);
    gpio_pull_up(BTNA);  

    gpio_init(BTNB);
    gpio_set_dir(BTNB, GPIO_IN);
    gpio_pull_up(BTNB);  
}

int main() {
    stdio_init_all();
    
    setting_inputs_and_outputs();

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW); //Inicializa a matriz de leds

    numbers(0); //Inicializa no número 0

    gpio_set_irq_enabled_with_callback(BTNA, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); //Callback de interrupção do Botão A
    gpio_set_irq_enabled_with_callback(BTNB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); //Callback de interrupção do Botão b

    while(true) {
        gpio_put(RED, true);
        sleep_ms(1000/10);
        gpio_put(RED, false);
        sleep_ms(1000/10);
    }

    return 0;
}

// Função de interrupção com debouncing
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time()); // Obtém o tempo atual em microssegundos

    if (current_time - last_time > 200000) { // 200 ms de debouncing
        last_time = current_time; 

        counter = (gpio == BTNA) ? (counter + 1)%10 : (gpio == BTNB) ? (counter + 10 - 1)%10 : counter; //Mantém o contador entre 0 e 9

        numbers(counter);

        printf("Contador atual: %i\n", counter);
    }
}
