#include <stdio.h>
#include <iostream>
#include <string.h>
#include <winsock2.h>
#include <winsock.h>
#include <windows.h>
#pragma comment(lib,"wsock32.lib")
using namespace std;

int main()
{
    int count;
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    // 创建套节字
    SOCKET s = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET)
    {
        printf("Failed socket() %d \n", ::WSAGetLastError());
        return 0;
    }
    // 也可以在这里调用bind函数绑定一个本地地址,否则系统将会自动安排
    // 填写远程地址信息  sockaddr_in addr;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6789);
    int nLen = sizeof(addr);
    // 注意，这里要填写服务器程序所在机器的IP地址，如果你的计算机没有联网，直接使用127.0.0.1即可
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    // 发送数据
    char receivebuff[1024];
    char sendbuffer[1024];
    printf("UDP Client is running.\n\n");
    while (TRUE)
    {
        int nRecv = ::recvfrom(s, receivebuff, 1024, 0, (sockaddr *)&addr, &nLen);
        if (nRecv > 0)
        {
            //接收数据
            receivebuff[nRecv] = '\0';
            printf("Recieve message from server: %s\n", receivebuff);
            if (strcmp(receivebuff, "bye") == 0)
            {
                ::closesocket(s);
                WSACleanup();
                return 0;
            }
        }
        //发送数据
        gets(sendbuffer);
        ::sendto(s, sendbuffer, strlen(sendbuffer), 0, (sockaddr *)&addr, sizeof(addr));
        printf("Send message to server< %d >: %s\n", ++count, sendbuffer);
        if (strcmp(sendbuffer, "0") == 0)
        {
            ::closesocket(s);
            return 0;
        }
    }
    return 0;
}

