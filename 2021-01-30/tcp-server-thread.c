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

   int rc = 0;
   int received = 0;
   int koniec = 0;
   char *buff_mess;
   char *tmp_buff;
   char *final;

   memset(buffer, 0, sizeof(buffer);

   while(!koniec) {
	rc = read (c -> cfd, buffer + received, sizeof(buffer);
	if(rc > 0){
		received +=received;
		if(buffer[received-1] == '\n') break;
		}
	}
	 
	
   asprintf(&tmp_buff, "%s\n", c->tmp_buff);
   
   if(strcmp(buffer, tmp_buff) == 0){
	asprintf(&buff_mess, "%s\n", c->final);
	} else {
		break
	}
	
	
   int zap = 0;
   int do_zap = strlen(buff_mess);

   while(zap < do_zap){
	zap += write(c->, cfd, buff_mess+zap, do_zap-zap)
	}

	
//   read(c->cfd, buffer, 255);
//   write(c->cfd, "Index belongs to Marcin Dubinski\n", 32);
//   write(c->cfd, "Something went wrong\n", 22);
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

