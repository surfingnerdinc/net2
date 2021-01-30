#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char** argv) {

	int sfd, rc;
	char userInput[255];


	struct sockaddr_in saddr;
	struct hostent* addrent;
	
	addrent = gethostbyname(argv[1]);
	sfd = socket(AF_INET, SOCK_STREAM,0);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(atoi(argv[2]));

	memcpy(&saddr.sin_addr.s_addr, addrent->h_addr, addrent->h_length);
	connect(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
	write(sfd, argv[3], 255);
	rc = read(sfd, userInput, sizeof(userInput));
	write(1, userInput, rc);
	close(sfd);
	
	return EXIT_SUCCESS;
}
