
#include <stdbool.h>

#include "socketutil.h":
int main() {
    int socketFD = createTCPIPv4Socket();

    struct sockaddr_in *address = createIPv4Address("127.0.0.1",2000);

    int result = connect(socketFD, (struct sockaddr*)address, sizeof (*address));

    if(result == 0){
        printf("connection was successful\n");
    } else{
        perror("connection failed\n");
    }

    char *line = NULL;
    size_t linesize = 0;
    printf("type and we will send(type exit)...\n");

    while(true) {
        ssize_t charCount = getline(&line,&linesize,stdin);
        if(charCount>0) {
            if(strcmp(line,"exit\n")==0)
                break;
            ssize_t amountWasSent = send(socketFD,line,charCount,0);
        }
    }

    char* message = "GET \\ HTTP/1.1\r\nHOST:google.com\r\n\r\n";
    send(socketFD,message,strlen(message),0);

    char buffer[1024];
    recv(socketFD,buffer,1024,0);

    printf("Resonse was %s\n",buffer);

    close(socketFD);
    return 0;
}

