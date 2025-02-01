/*
    Aluno: Lucas Carneirod e Araújo Lima
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

int main() {
    stdio_init_all();
    printf("WS2812 5x5 Matrix - Single LED Control\n");

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    unsigned short int counter = 0;
    char tecla='\0';

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    set_leds_from_color(pio, pio_claim_unused_sm(pio, true), color(0.0, 0.0, 0.0));

    while(true) {
        tecla = getchar_timeout_us(50);
        
        if(tecla != PICO_ERROR_TIMEOUT) {
            counter = (tecla == '+') ? (counter + 10 + 1) : (tecla == '-') ? (counter + 10 - 1) : counter;

            printf("Contador atual: %i\n", counter);
            numbers(counter%10);
            sleep_ms(1000);

            counter = (counter >= 10) ? counter - 10 : counter;
        }

        sleep_ms(100); 
    }

    return 0;
}
