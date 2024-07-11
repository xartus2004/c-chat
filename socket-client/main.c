
#include <stdbool.h>

#include "socketutil.h"

void startListeningAndPrintingMessagesOnNewThread(int socketFD);
void listenAndPrint(int socketFD);

int main() {
    int socketFD = createTCPIPv4Socket();

    struct sockaddr_in *address = createIPv4Address("127.0.0.1",2000);

    int result = connect(socketFD, (struct sockaddr*)address, sizeof (*address));

    if(result == 0){
        printf("connection was successful\n");
    } else{
        perror("connection failed\n");
    }


    startListeningAndPrintingMessagesOnNewThread(socketFD);


    char *name = NULL;
    size_t nameSize = 0;
    printf("please enter your name\n");
    ssize_t nameCount = getline(&name,&nameSize,stdin);
    name[nameCount-1] = 0;

    char *line = NULL;
    size_t linesize = 0;
    printf("type and we will send(type exit)...\n");

    char buffer[1024];

    while(true) {
        ssize_t charCount = getline(&line,&linesize,stdin);
        line[charCount-1]=0;

        sprintf(buffer,"%s:%s",name,line);

        if(charCount>0) {
            if(strcmp(line,"exit\n")==0)
                break;
            ssize_t amountWasSent = send(socketFD,
                                        buffer,
                                        strlen(buffer),
                                        0);
        }
    }

    close(socketFD);
    return 0;
}
void startListeningAndPrintingMessagesOnNewThread(int socketFD) {
    pthread_t id;
    pthread_create(&id,NULL,listenAndPrint,socketFD);

}

void listenAndPrint(int socketFD) {
    char buffer[1024];

    while(true) {
        ssize_t amountRecieved = recv(socketFD,buffer,1024,0);
        if(amountRecieved>0) {
            buffer[amountRecieved]=0;
            printf("Response was %s",buffer);
        }
        if(amountRecieved==0)
            break;
    }
    close(socketFD);
}
