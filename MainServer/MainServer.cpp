#include <thread>
#include <iostream>
#include <set>
#include "Server.h"
#include "Controller.h"

Server server;
Controller controller;


int main(int argc, char* argv[]) {



	while (true) {
	    sleep(1);
        int err;
        sockaddr_in ClientAddr{};
        int ClientAddrSize=sizeof(ClientAddr);


        char from[64];
        char to[64];
        char freight_type[64];
        int cars_count = 0;
        string msg;
        while (true) {
            sleep(1);
            memset(from, 0, 64);
            memset(to, 0, 64);
            memset(freight_type, 0, 64);
            try {
                cout << "recv" << endl;
                if (recvfrom(server.getServerSocket(), from, sizeof(from), 0, (sockaddr *)&ClientAddr, reinterpret_cast<socklen_t *>(&ClientAddrSize)) > 0
                    && recvfrom(server.getServerSocket(), to, sizeof(to), 0, (sockaddr *)&ClientAddr, reinterpret_cast<socklen_t *>(&ClientAddrSize)) > 0
                    && recvfrom(server.getServerSocket(), freight_type, sizeof(freight_type), 0, (sockaddr *)&ClientAddr, reinterpret_cast<socklen_t *>(&ClientAddrSize)) > 0
                    && recvfrom(server.getServerSocket(), (char*)&cars_count, sizeof(int), 0, (sockaddr *)&ClientAddr, reinterpret_cast<socklen_t *>(&ClientAddrSize)) > 0)
                    msg = controller.order(from, to, freight_type, cars_count - (int)'0');
            }
            catch (exception& ex) {
                msg = ex.what();
            }
            cout << "recv2" << endl;
            sendto(server.getServerSocket(),msg.c_str(), 256,0,(sockaddr *)&ClientAddr,sizeof(ClientAddr));
        }
	}


	system("pause");
	return 0;
}