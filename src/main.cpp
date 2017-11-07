#include <cstdlib>
#include <fcntl.h> // O_RDONLY
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdio>

#include "DisplayFactory.h"

#define ADC4 "/sys/bus/iio/devices/iio:device0/in_voltage4_raw"
#define ADC6 "/sys/bus/iio/devices/iio:device0/in_voltage6_raw"
#define MAX_BUFF 64

int buffer = 0;
Display* display = 0;

int consumer_sleep_time_ms = 1000;
int producer_sleep_time_ms = 2000;

pthread_mutex_t show_mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t full_buffer_sem;
sem_t empty_buffer_sem;

void* consumer_thread(void*)
{
    while (1) {
        sem_wait(&full_buffer_sem);
        buffer--;
        sem_post(&empty_buffer_sem);

        pthread_mutex_lock(&show_mutex);
        display->show(buffer);
        pthread_mutex_unlock(&show_mutex);

        usleep(consumer_sleep_time_ms * 1000);
    }
}

void* producer_thread(void*)
{
    while (1) {
        sem_wait(&empty_buffer_sem);
        buffer++;
        sem_post(&full_buffer_sem);

        pthread_mutex_lock(&show_mutex);
        display->show(buffer);
        pthread_mutex_unlock(&show_mutex);

        usleep(producer_sleep_time_ms * 1000);
    }
}

void* speed_thread(void*)
{
    int fd = 0;
    char buf_ADC4[MAX_BUFF] = { 0 };
    snprintf(buf_ADC4, sizeof(buf_ADC4), ADC4);
    char adc4[5] = { 0, 0, 0, 0, 0 }; // four digits and null terminator \0

    char buf_ADC6[MAX_BUFF] = { 0 };
    snprintf(buf_ADC6, sizeof(buf_ADC6), ADC6);
    char adc6[5] = { 0, 0, 0, 0, 0 }; // four digits and null terminator \0

    while (1) {
        fd = open(buf_ADC4, O_RDONLY | O_NONBLOCK);
        read(fd, adc4, 4); // reads 4 bytes from file FD to adc4
        close(fd);

        fd = open(buf_ADC6, O_RDONLY | O_NONBLOCK);
        read(fd, adc6, 4); // reads 4 bytes from file FD to adc6
        close(fd);

        printf("ADC4: %d\tADC6: %d\n", atoi(adc4), atoi(adc6));
        fflush(stdout);

        consumer_sleep_time_ms = atoi(adc4);
        producer_sleep_time_ms = atoi(adc6);
        usleep(100);
    }
}

int main(int argc, char* argv[])
{
    display = DisplayFactory::getDisplay(Display::LCD);

    sem_init(&full_buffer_sem, 0, 0);
    sem_init(&empty_buffer_sem, 0, 7);

    pthread_t consumer, producer;
    pthread_t speed;

    pthread_create(&consumer, NULL, consumer_thread, NULL);
    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&speed, NULL, speed_thread, NULL);

    pthread_join(consumer, NULL);
    pthread_join(producer, NULL);
    pthread_join(speed, NULL);

    return 0;
}
