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
    // �����׽���
    SOCKET s = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET)
    {
        printf("Failed socket() %d \n", ::WSAGetLastError());
        return 0;
    }
    // Ҳ�������������bind������һ�����ص�ַ,����ϵͳ�����Զ�����
    // ��дԶ�̵�ַ��Ϣ  sockaddr_in addr;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6789);
    int nLen = sizeof(addr);
    // ע�⣬����Ҫ��д�������������ڻ�����IP��ַ�������ļ����û��������ֱ��ʹ��127.0.0.1����
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    // ��������
    char receivebuff[1024];
    char sendbuffer[1024];
    printf("UDP Client is running.\n\n");
    while (TRUE)
    {
        int nRecv = ::recvfrom(s, receivebuff, 1024, 0, (sockaddr *)&addr, &nLen);
        if (nRecv > 0)
        {
            //��������
            receivebuff[nRecv] = '\0';
            printf("Recieve message from server: %s\n", receivebuff);
            if (strcmp(receivebuff, "bye") == 0)
            {
                ::closesocket(s);
                WSACleanup();
                return 0;
            }
        }
        //��������
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

