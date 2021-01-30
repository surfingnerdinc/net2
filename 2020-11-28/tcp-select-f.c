#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>



int main(int argc, char** argv) {
	
	socklen_t slt;
	int sfd, cfd, fdmax, fda, rc, i, on = 1;
	struct sockaddr_in saddr, caddr;
	static struct timeval timeout;
	

	fd_set mask, rmask, wmask;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(1234);
	


	sfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
	bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
	listen(sfd, 10);
	

	//synchroniczne zwielokrotnienie we / wy
	FD_ZERO(&mask);
	FD_ZERO(&rmask);
	FD_ZERO(&wmask);
	fdmax = sfd;
	char buffer[255];

void check() {
 if(strcmp(buffer, "133825") == 0){
  write (cfd, "Index belongs to: Marcin Dubinski \n", 35);
  }
 else {
  write (cfd, "Something went wrong\n", 22);
  }
};
	while(1) 
	{
		FD_SET(sfd, &rmask);
		wmask = mask;
		timeout.tv_sec = 5 * 60;
		timeout.tv_usec = 0;
		//select - umolzuwa monit wielu desc. Czeka az ktorys bedzie gotowy do wykonania operacji (bez blokowania).
		rc = select(fdmax+1, &rmask, &wmask, (fd_set*)0, &timeout);
		if(rc == 0) 
		{
			printf("timed out\n");
			continue;
		}
		fda = rc;
		if(FD_ISSET(sfd, &rmask)) 
		{
			fda -= 1;
			slt = sizeof(caddr);
			cfd = accept(sfd, (struct sockaddr*)&caddr, &slt);
			read(cfd, buffer, 256);
			printf("new connection: %s\n", inet_ntoa((struct in_addr)caddr.sin_addr));
			FD_SET(cfd, &mask);
			if(cfd > fdmax) fdmax = cfd;
		}
		for(i = sfd + 1; i <= fdmax && fda > 0; i++)
			if(FD_ISSET(i, &wmask)) 
			{
				fda -= 1;
				check();
				close(i);
				FD_CLR(i, &mask);
				if(i == fdmax)
					while(fdmax > sfd && !FD_ISSET(fdmax, &mask))
						fdmax -= 1;

			}
	}
	close(sfd);
	return EXIT_SUCCESS;
}
