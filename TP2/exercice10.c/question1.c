#include <stdio.h>
#include <unistd.h>

void pong();

void ping(){
    printf("Ping\n");
    sleep(1);
    pong();
}

void pong(){
    printf("Pong\n");
    sleep(1);
    ping();
}

void main(){
    ping();
}