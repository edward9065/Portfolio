#include <stdio.h>  
#include <sys/poll.h>
#include <sys/socket.h> //connect
#include <sys/stat.h> //sockaddr_in struct
#include <arpa/inet.h> 
#include <unistd.h> //read, write
#include <stdlib.h> //atoi 
#include <string.h> //memset
 
int run(int connection) {
    //poll
    struct pollfd fds[2]; 
    //open STREAMS device
    int ret, i;
    int timeout = 60000; //1 min in ms
    fds[0].fd = connection;//open(connection, O_WRONLY); //???
    //standard input streamq
    fds[1].fd = 0; //open(0, O_RDONLY);
    fds[0].events = POLLIN; 
    fds[1].events = POLLIN;

    char* buffer = calloc(4096, sizeof(char));

    for(;;) {
        //do something
        //one minute timer for poll

        int success = poll(fds, 2, timeout);
        //struct fds[], number of structs, int timeout

        //use poll to pick either the connected socket(from accept) or client's connect
        //or use stdin to read from - one minute time out
        if(success) {
            //the socket -> stdout
            if(fds[0].revents & POLLIN) {
                read(connection, buffer, 4096);
                write(1, buffer, 4096);
              
            }
            //standard in -> the socket
            else if(fds[1].revents & POLLIN) {
                read(0, buffer, 4096);
                write(connection, buffer, 4096);
              
            }
            memset(buffer, 0, 4096);
        }
        else {
            puts("No input or output recieved for one minute - terminating program");
            free(buffer);
            close(connection);
            //return -1 if poll doesn't get anything for an entire minute
            return -1;
        }
    }
    //free and close everything
    free(buffer);
    close(connection);
    
    return 0;
}

int server() {
    // start by getting a random port from the ephemeral port range
    srandom(getpid()); // random seed based on this process's OS-assigned ID
    int port = 0xc000 | (random()&0x3fff); // random element of 49152–65535

    struct sockaddr_in ipOfServer;
    memset(&ipOfServer, 0, sizeof(struct sockaddr_in));
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
    ipOfServer.sin_port = htons(port);

    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener == -1) {
        puts("Error: failed to create server listener socket"); 
        return -1;
    }
    int b = bind(listener, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));
    if(b == -1) {
        puts("Error: failed to assign a name to the server listener socket");
        return -1;
    }

    int l = listen(listener , 20);
    if(b == -1) {
        puts("Error: listen function failed");
        return -1;
    }

    system("host $HOSTNAME"); // display all this computer's IP addresses
    printf("The server is now listening on port %d\n", port); // and listening port

    int connection;

    //attempt connection - could be a do while
    do {
        connection = accept(listener, (struct sockaddr*)NULL, NULL);
    } while(!connection);

    //done with listener
    close(listener);
    //send to the run function
    run(connection);
    
    return 0;
    
}


int client(const char* IP, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) puts("Error: ");

    //Connect to Remote server 
    struct sockaddr_in ipOfServer;
    memset(&ipOfServer, 0, sizeof(struct sockaddr_in));
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(port);
    ipOfServer.sin_addr.s_addr = inet_addr(IP);
    
    //Read message from server. 
    int c = connect(sock, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer));
    if(c == -1) {
        puts("Error: failed to connect to server");
        return -1;
    }

    run(sock);
    return 0;
}


int main(int argc , char *argv[]){
    //server
    if(argc == 1) {
        if(!server()) {
            return -1;
        }
    }
    else if(argc == 3) {
        const char *IP = argv[1];
        int port = atoi(argv[2]);
        if(!(client(IP, port))) {
            return -1; 
        }
    }
    else {
        puts("Error: incorrect number of arguments");
        return -1;
    }

//everything worked
return 0;
}