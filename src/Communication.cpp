//
// Created by Mazen on 16.11.19.
//

#include <netinet/in.h>
#include <printf.h>
#include <arpa/inet.h>
#include <cstring>
#include <zconf.h>
#include<stdio.h>

#include "../headers/Communication.h"

int Communication::sendMsg(const char * IP, const int PORT, char* msg) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock , msg , strlen(msg) , 0);
    printf("Client: Sent Message\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n", buffer);
}