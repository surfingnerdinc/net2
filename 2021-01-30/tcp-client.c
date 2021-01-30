#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char **argv) {
    

    int sfd, rc;
    char buffer[255] = "";
    
    
    struct sockaddr_in saddr;
    struct hostent* addrent;

    addrent = gethostbyname(argv[1]);
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));
    memcpy(&saddr.sin_addr.s_addr, addrent->h_addr, addrent->h_length);
    connect(sfd, (struct sockaddr*)&saddr, sizeof(saddr));

    
    char *buff_mess;
    rc = 0;
    int received = 0;
    int koniec = 0;
    int zap = 0;
    int do_zap = strlen(buff_mess);
    asprintf(&buff_mess, "%s\n", argv[3]);
    
    
    while (zap < do_zap) {
        zap += write(sfd, buff_mess + zap, do_zap - zap);
    }

    while (!koniec) {
        rc = read(sfd, buffer+received, sizeof(buffer));
        if (rc > 0) {
            received += rc;
            if (buffer[received-1] == '\n') koniec = 1;
        }
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    printf("%s\n", buffer);

    close(sfd);

    return 0;
}
