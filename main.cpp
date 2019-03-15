#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include <vector>

#define Log(message)    {std::cout << message << std::endl;}


class receiverThread {
public:
    receiverThread(int listeningPort) : _listeningPort(listeningPort),
                                        _thread(&receiverThread::main, this) {

    }

    void main() {

        struct sockaddr_in serverAddr, clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        memset(&serverAddr, 0, sizeof(serverAddr));

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(_listeningPort);
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        int sock;
        int ret;

        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (sock < 0) {
            Log("Failed to create socket!");
            return;
        }


        ret = bind(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

        if (ret < 0) {
            Log("Could not bind socket!");
            return;
        }

        char ctr = 0;

        while (true) {
            char recvBuf[1024];

            ssize_t len = recvfrom(sock, recvBuf, sizeof(recvBuf), 0,
                                   (struct sockaddr *) &clientAddr, &clientAddrLen);

            if (len < 0) {
                Log("Failed recvfrom operation!");
            } else {
                if (recvBuf[0] != ctr) {
                    std::ostringstream oss;
                    oss << "Received: " << (int) recvBuf[0] << " | Expected: " << (int) ctr;
                    Log(oss.str());
                    ctr = recvBuf[0];
                } else {
                    ctr += 1;
                }

            }
        }
    }

    void Join() {
        _thread.join();
    }

private:
    std::thread _thread;
    int _listeningPort;
};


int main() {

    receiverThread rt1(9001);
    receiverThread rt2(9002);
    receiverThread rt3(9003);
    receiverThread rt4(9004);
    receiverThread rt5(9005);
    receiverThread rt6(9006);
    receiverThread rt7(9007);
    receiverThread rt8(9008);
    receiverThread rt9(9009);
    receiverThread rt10(9010);

    rt1.Join();
    rt2.Join();
    rt3.Join();
    rt4.Join();
    rt5.Join();
    rt6.Join();
    rt7.Join();
    rt8.Join();
    rt9.Join();
    rt10.Join();

    return 0;
}