#include <iostream>
#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
using namespace std;

int main() {
    WSADATA data;	//Socket�İ汾��Ϣ 
    WORD sVersion;
    sVersion = MAKEWORD(2, 2);
    int nRes = WSAStartup(sVersion, &data); // ��ʼ���׽��ֿ�
	if (nRes != 0){
		printf("error:%d\n\n", WSAGetLastError());
		return 0;
	}
    
    //���� 
    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0); // AF_INET��ʾ��������ͨ�ţ�SOCK_DGRAM��ʾ����UDPͨ�� 
	if (s == INVALID_SOCKET){
		printf("Socket error:%d\n\n", WSAGetLastError());
		return 0;
	}
	
    //���sockaddr_in�ṹ 
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6789); //UDP_TEST_PORT
    server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //UDP_SERVER_IP
    
    //��
    int b = bind(s, (sockaddr*)&server_addr, sizeof(server_addr));
    if (b == SOCKET_ERROR){
		printf("Bind error:%d\n\n", WSAGetLastError());
		return 0;
	}
	
	printf("UDP Server is running.\n\n");
	
	
	sockaddr_in client_addr; 
	char recvBuf[256] = {0}; // UDP���ݱ������ַ
    int len = sizeof(client_addr); // UDP���ݱ�����
    int count = 0;
	while(1){
		//���� 
    	if (recvfrom(s, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&client_addr, &len) != 0 && recvBuf) {
            printf("Recieve message from client: %s\n", recvBuf);
        }
     	if (strcmp(recvBuf, "bye") == 0) break; 
     	
        //����
        char sendBuf[256] = "This is server!\nThe message I received is: ";
        char a[] = "\n"; 
        strcat(sendBuf, recvBuf);
        strcat(sendBuf, a);
		sendto(s, sendBuf, strlen(sendBuf) + 1, 0, (sockaddr*)&client_addr, len);
		printf("Send message to client< %d >: %s\n", ++count, sendBuf);
	} 
	
	 
    //�ر� 
    closesocket(s);
    WSACleanup();
    
    return 0;
}

