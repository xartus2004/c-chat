#include "socketutil.h"

struct AcceptedSocket {
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool acceptedSuccessfully;
};

struct AcceptedSocket *acceptIncomingConnection(int serverSocketFD);
void recieveAndPrintIncomingData(int socketFD);
void startAcceptingIncomingConnections(int serverSocketFD);
void acceptNewConnectionAndRecieveAndPrintItsData(int serverSocketFD);
void sendRecieveMessageToTheOtherClients(char *buffer, int socketFD);

void recievingAndPrintingDataOnSeparateThread(struct AcceptedSocket *clientSocket);

struct AcceptedSocket acceptedSockets[10];
int acceptedSocketsCount = 0;

void startAcceptingIncomingConnections(int serverSocketFD) {
    while(true) {
        struct AcceptedSocket* clientSocket = acceptIncomingConnection(serverSocketFD);
        acceptedSockets[acceptedSocketsCount++] = *clientSocket;
        recievingAndPrintingDataOnSeparateThread(clientSocket);
    }
}

void recievingAndPrintingDataOnSeparateThread(struct AcceptedSocket *pSocket) {
    pthread_t id;
    pthread_create(&id,NULL,recieveAndPrintIncomingData,pSocket->acceptedSocketFD);

}
struct AcceptedSocket * acceptIncomingConnection(int serverSocketFD) {
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof (struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD,&clientAddress,&clientAddressSize);
    struct AcceptedSocket* acceptedSocket = malloc(sizeof(struct AcceptedSocket));
    acceptedSocket->address = clientAddress;
    acceptedSocket->acceptedSocketFD = clientSocketFD;
    acceptedSocket->acceptedSuccessfully = clientSocketFD>0;

    if(!acceptedSocket->acceptedSuccessfully)
        acceptedSocket->error = clientSocketFD;
    return acceptedSocket;
}

void recieveAndPrintIncomingData(int socketFD) {
    char buffer[1024];

    while(true) {
        ssize_t amountRecieved = recv(socketFD,buffer,1024,0);
        if(amountRecieved>0) {
            buffer[amountRecieved]=0;
            printf("%s\n",buffer);

            sendRecieveMessageToTheOtherClients(buffer,socketFD);
        }
        if(amountRecieved==0)
            break;
    }
    close(socketFD);
}

void sendRecieveMessageToTheOtherClients(char *buffer, int socketFD) {
    for(int i=0 ; i<acceptedSocketsCount ; i++)
        if(acceptedSockets[i].acceptedSocketFD != socketFD) {
            send(acceptedSockets[i].acceptedSocketFD,buffer,strlen(buffer),0);
        }
}


int main(void)
{
    int serverSocketFD = createTCPIPv4Socket();
    struct sockaddr_in *serverAddress = createIPv4Address("",2000);

    int result = bind(serverSocketFD,serverAddress,sizeof(*serverAddress));
    if(result==0)
        printf("socket was bound successfully\n");

    int listenResult = listen(serverSocketFD,10);

    startAcceptingIncomingConnections(serverSocketFD);


    shutdown(serverSocketFD,SHUT_RDWR);

    return 0;
}
