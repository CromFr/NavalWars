#ifndef RESEAU_H_INCLUDED
#define RESEAU_H_INCLUDED

//DEFINITION VARIABLES GLOBALES

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Libs reseau
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFLEN 1024



//Liées au réseau
extern struct sockaddr_in si_me, si_other;
extern int sock_send, sock_recv;


int VerifValeursIP(char *cAddrIP);
int VerifValeursPort(int *nPort);
int MenuChangerConfig();
int SetConfig(char *cAddrIP, int nPortSend, int nPortRecev);
int GetConfig(char *cAddrIP, int *nPortSend, int *nPortRecev);
int init_socket_recv(int port_recv);
int init_socket_send(int port_send, const char* addr_ip);
int receive_position(int* i, int* j);
int send_position(int i, int j);



#endif // RESEAU_H_INCLUDED
