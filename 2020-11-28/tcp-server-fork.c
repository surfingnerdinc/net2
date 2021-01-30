#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>



void childend(int signo)
 {
         wait(NULL);
         printf("Proces potomny zostal zakonczony\n");
 }




int main(int argc, char** argv)
 {
         socklen_t slt;
         int sfd, cfd, on=1;
         char buffer[255];
         struct sockaddr_in saddr, caddr;
         signal(SIGCHLD, childend);
 
         sfd = socket(AF_INET, SOCK_STREAM, 0);
         saddr.sin_family = AF_INET;
         saddr.sin_addr.s_addr = INADDR_ANY;
         saddr.sin_port = htons(1234);
         setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
         bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
         listen(sfd,6);
         while(1){
                 slt = sizeof(caddr);
                 cfd = accept(sfd, (struct sockaddr*)&caddr, &slt);
                 if (fork() == 0)
                 {
                         close(sfd);
                         read(cfd, buffer, 255);
                         if (strcmp(buffer, "133825") == 0)
                         {
                                 write(cfd, "Student: Marcin Dubinski\n", 30);
                         }
                         else
                         {
                                 write(cfd, "Something went wrong\n", 25);
                         }
                         close(cfd);
                         return EXIT_SUCCESS;
                 }
                 close(cfd);
         }
         close(sfd);
         return EXIT_SUCCESS;
}

