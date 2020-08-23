#include "Server.h"

Server::Server() {

    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket < 0){
        cout << "socket error" << endl;
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8122);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(serverSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        cout << "connection error" << endl;
        exit(2);
    }
    cout << "Connected!" << endl;

    //int nonBlocking = 1;
    //if ( fcntl( serverSocket, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 ){
    //    cout << "failed to set non-blocking socket" << endl;
    //    exit(3);
    //}
}

Server::~Server() {
    close(serverSocket);
}

int Server::getServerSocket(){
    return serverSocket;
}
