#include <netdb.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

struct cln
{
 int cfd;
 struct sockaddr_in caddr;
};

void* cthread(void* arg) {
   struct cln* c = (struct cln*)arg;
   printf("new connection: %s\n", inet_ntoa((struct in_addr)c->caddr.sin_addr));
   char buffer[255];
   read(c->cfd, buffer, 255);
   if (strcmp(buffer, "133825") == 0)
   {
     write(c->cfd, "Index belongs to Marcin Dubinski\n", 99);
   }
   else
   {
     write(c->cfd, "Error, wrong index-no.\n", 25);
   }
   close(c->cfd);
   free(c);
   return EXIT_SUCCESS;
 }
 int main(int argc, char** argv) {
   pthread_t tid;
   socklen_t slt;
   int sfd, on = 1;
   struct sockaddr_in saddr;
   saddr.sin_family = AF_INET;
   saddr.sin_addr.s_addr = INADDR_ANY;
   saddr.sin_port = htons(1234);
   sfd = socket(AF_INET, SOCK_STREAM, 0);
   setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
   bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
   listen(sfd, 10);
   while(1) {
     struct cln* c = malloc(sizeof(struct cln));
     slt = sizeof(c->caddr);
     c->cfd = accept(sfd, (struct sockaddr*)&c->caddr, &slt);
     pthread_create(&tid, NULL, cthread, c);
     pthread_detach(tid);
   }
   close(sfd);
return EXIT_SUCCESS;
}

