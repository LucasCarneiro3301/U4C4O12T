/*
    Aluno: Lucas Carneiro de Araújo Lima
*/

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"

#include "ws2812.pio.h"

#include "numbers.h"

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define RED 13
#define GREEN 12
#define BLUE 11
#define BTNA 5
#define BTNB 6

uint8_t led = 0; // Índice do LED a ser controlado (0 a 24)
uint8_t red = 0;   // Intensidade do vermelho (0 a 255)
uint8_t green = 0;   // Intensidade do verde (0 a 255)
uint8_t blue = 80;   // Intensidade do azul (0 a 255)

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

static void gpio_irq_handler(uint gpio, uint32_t events); // Prototipação da função de interrupção

static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

unsigned short int counter = 0;

uint32_t led_buffer[NUM_PIXELS] = {0}; // Buffer para armazenar as cores de todos os LEDs


// Configura a cor para o LED selecionado no buffer
void update_led_buffer() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        led_buffer[i] = 0; 
    }

    led_buffer[led] = urgb_u32(red, green, blue);
}

// Envia o estado de todos os LEDs para a matriz
void set_leds_from_buffer() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        put_pixel(led_buffer[i]);
    }
}

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

    char tecla='\0';

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    //set_leds_from_color(pio, pio_claim_unused_sm(pio, true), color(0.0, 0.0, 0.0));

    numbers(0);

    gpio_set_irq_enabled_with_callback(BTNA, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BTNB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

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

        counter = (gpio == BTNA) ? (counter + 10 + 1)%10 : (gpio == BTNB) ? (counter + 10 - 1)%10 : counter;

        numbers(counter);

        printf("Contador atual: %i\n", counter);
    }
}
