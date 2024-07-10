#ifndef SOCKET_UTIL_LIBRARY_H
#define SOCKET_UTIL_LIBRARY_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

struct sockaddr_in* createIPv4Address(char *ip, int port);
int createTCPIPv4Socket();

#endif //SOCKET_UTIL_LIBRARY_H
