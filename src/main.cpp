#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>

#include "DisplayFactory.h"

int buffer = 0;
Display *display = 0;

int consumer_sleep_time_ms = 1000;
int producer_sleep_time_ms = 2000;

pthread_mutex_t show_mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t full_buffer_sem;
sem_t empty_buffer_sem;

void* consumer_thread(void*)
{
    while(1) {
        sem_wait(&full_buffer_sem);
        buffer--;
        sem_post(&empty_buffer_sem);
        
        pthread_mutex_lock(&show_mutex);
        display->show(buffer);
        pthread_mutex_unlock(&show_mutex);
        
        usleep(consumer_sleep_time_ms*1000);
    }
}

void* producer_thread(void*)
{
    while(1) {
        sem_wait(&empty_buffer_sem);
        buffer++;
        sem_post(&full_buffer_sem);
        
        pthread_mutex_lock(&show_mutex);
        display->show(buffer);
        pthread_mutex_unlock(&show_mutex);
        
        usleep(producer_sleep_time_ms*1000);
    }
}

void* speed_thread(void*)
{
    while(1) {
        consumer_sleep_time_ms = rand()%2000 + 1;
        producer_sleep_time_ms = rand()%2000 + 1;
    }
}

int main(int argc, char *argv[])
{
    display = DisplayFactory::getDisplay(Display::CONSOLE);

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
