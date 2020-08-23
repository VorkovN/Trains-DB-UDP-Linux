#include "Client.h"

Client::Client() {

    clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientSocket < 0){
        cout << "socket error" << endl;
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8122);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	cout << "Connected!" << endl;
}

Client::~Client() {
    close(clientSocket);
}

int Client::getClientSocket() const{
    return clientSocket;
}

sockaddr_in& Client::getAddr() {
    return addr;
}
