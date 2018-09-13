#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <libsoc_gpio.h>
#include <libsoc_debug.h>

#define BUTTON1 48
#define BUTTON2 51
#define BUTTON3 5
#define BUTTON4 4

#define LED1 3
#define LED2 2
#define LED3 49
#define LED4 15

gpio *gpio_output_1;
gpio *gpio_output_2;
gpio *gpio_output_3;
gpio *gpio_output_4;

gpio *gpio_input_1;
gpio *gpio_input_2;
gpio *gpio_input_3;
gpio *gpio_input_4;

int gpio_interrupt_callback_1(void* arg) {
    libsoc_gpio_set_level(gpio_output_1, HIGH);
    usleep(10000);
    libsoc_gpio_set_level(gpio_output_1, LOW);
    return 0;
}

int gpio_interrupt_callback_2(void* arg) {
    libsoc_gpio_set_level(gpio_output_2, HIGH);
    usleep(10000);
    libsoc_gpio_set_level(gpio_output_2, LOW);
    return 0;
}

int gpio_interrupt_callback_3(void* arg) {
    libsoc_gpio_set_level(gpio_output_3, HIGH);
    usleep(10000);
    libsoc_gpio_set_level(gpio_output_3, LOW);
    return 0;
}

int gpio_interrupt_callback_4(void* arg) {
    libsoc_gpio_set_level(gpio_output_4, HIGH);
    usleep(10000);
    libsoc_gpio_set_level(gpio_output_4, LOW);
    return 0;
}


int main(void) {
    libsoc_set_debug(1);

    gpio_output_1 = libsoc_gpio_request(LED1, LS_SHARED);
    libsoc_gpio_set_direction(gpio_output_1, OUTPUT);
    gpio_output_2 = libsoc_gpio_request(LED2, LS_SHARED);
    libsoc_gpio_set_direction(gpio_output_2, OUTPUT);
    gpio_output_3 = libsoc_gpio_request(LED3, LS_SHARED);
    libsoc_gpio_set_direction(gpio_output_3, OUTPUT);
    gpio_output_4 = libsoc_gpio_request(LED4, LS_SHARED);
    libsoc_gpio_set_direction(gpio_output_4, OUTPUT);

    gpio_input_1 = libsoc_gpio_request(BUTTON1, LS_SHARED);
    libsoc_gpio_set_direction(gpio_input_1, INPUT);
    gpio_input_2 = libsoc_gpio_request(BUTTON2, LS_SHARED);
    libsoc_gpio_set_direction(gpio_input_2, INPUT);
    gpio_input_3 = libsoc_gpio_request(BUTTON3, LS_SHARED);
    libsoc_gpio_set_direction(gpio_input_3, INPUT);
    gpio_input_4 = libsoc_gpio_request(BUTTON4, LS_SHARED);
    libsoc_gpio_set_direction(gpio_input_4, INPUT);

    libsoc_gpio_callback_interrupt(gpio_input_1, &gpio_interrupt_callback_1, NULL);
    libsoc_gpio_callback_interrupt(gpio_input_2, &gpio_interrupt_callback_2, NULL);
    libsoc_gpio_callback_interrupt(gpio_input_3, &gpio_interrupt_callback_3, NULL);
    libsoc_gpio_callback_interrupt(gpio_input_4, &gpio_interrupt_callback_4, NULL);

    libsoc_set_debug(0);

    printf("Waiting for interrupt. Press 'q' and 'Enter' at any time to exit\n");

    char key = -1;

    while(1) {
        key = fgetc(stdin);
        if(key == 'q') {
            goto exit;
        }
    }


exit:
    if (gpio_output_1) {
        libsoc_gpio_free(gpio_output_1); }
    if (gpio_output_2) {
        libsoc_gpio_free(gpio_output_2); }
    if (gpio_output_3) {
        libsoc_gpio_free(gpio_output_3); }
    if (gpio_output_4) {
        libsoc_gpio_free(gpio_output_4); }

    if (gpio_input_1) {
        libsoc_gpio_free(gpio_input_1); }
    if (gpio_input_2) {
        libsoc_gpio_free(gpio_input_2); }
    if (gpio_input_3) {
        libsoc_gpio_free(gpio_input_3); }
    if (gpio_input_4) {
        libsoc_gpio_free(gpio_input_4); }


    return EXIT_SUCCESS;
}
