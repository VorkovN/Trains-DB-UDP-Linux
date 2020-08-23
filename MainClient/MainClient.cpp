#include <cstring>    // sizeof()
#include <iostream>
#include <string>
#include <thread>

// headers for socket(), getaddrinfo() and friends
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>    // close()

#include "Client.h"

using namespace std;


Client client;


[[noreturn]] void ClientHandler(sockaddr_in ad, int adSize) {
	char msg[256];
	while (true) {
        memset(msg, 0, 256);
		if (recvfrom(client.getClientSocket(), msg, 64, 0, (sockaddr *)&ad, reinterpret_cast<socklen_t *>(&adSize)) > 0) {
			cout << msg << endl;
			sleep(1);
		}
	}
}


int main(int argc, char* argv[]) {
    sockaddr_in ad = client.getAddr();
    int adSize=sizeof(ad);
    int clSoc = client.getClientSocket();

    thread func_thread(ClientHandler, ad, adSize);
    func_thread.detach();

	char from[64];
	char to[64];
	char freight_type[64];
	char cars_count[64];
	while (true) {
		sleep(1);
        memset(from, 0, 64);
        memset(to, 0, 64);
        memset(freight_type, 0, 64);
		cout << "Input city1" << endl;
		cin.getline(from, sizeof(from));
		cout << "Input city2" << endl;;
		cin.getline(to, sizeof(to));
		cout << "Input type of freight (liquid, wood or ore)" << endl;;
		cin.getline(freight_type, sizeof(freight_type));
		cout << "Input count of cars" << endl;
		cin.getline(cars_count, sizeof(cars_count));
        sendto(clSoc,from,strlen(from),0,(sockaddr *)&ad,sizeof(ad));
        sendto(clSoc,to,strlen(to),0,(sockaddr *)&ad,sizeof(ad));
        sendto(clSoc,freight_type,strlen(freight_type),0,(sockaddr *)&ad,sizeof(ad));
        sendto(clSoc,cars_count,sizeof(int),0,(sockaddr *)&ad,sizeof(ad));
		cin.clear();
		cout << endl;
	}

	system("pause");
	return 0;
}
