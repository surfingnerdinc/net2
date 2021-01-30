#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>


int main(int argc, char* argv[]){
 WORD WRequiredVersion;
 WSADATA WData;
 SOCKET fd;
 int rc;
 struct sockaddr_in addr;
 struct hostent* addrent;
 char buf[1024];


 if (argc != 3) { 
  fprintf(stderr, "usage: %s server_name port_number\n", argv[0]);
  exit(1);
 }

 WRequiredVersion = MAKEWORD(2, 0_;
 WSAStartup(WRequiredVersion, &WData);
 addrent = gethostbyname(argv[1]);
 fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 addr.sin_family = AF_INET;

 memcpy(&addr.sin_addr.s_addr, addrent -> h_addr, addrent -> h_length);
 addr.sin_port = htons(atoi(argv[2]));
 connect (fd, (struct sockaddr*)&addr, sizeof(struct sockaddr));


//dodanie send
 send(fd, "133825", 6, MSG_DONTROUTE);

 rc = recv(fd, buf, sizeof(buf), 0);
 buf[rc] = '\x0';
 printf("Data from server [%s]:\t%s\n", argv[1], buf);
 closesocket(fd);
 WSACLEANUP();
 return 0;
}
