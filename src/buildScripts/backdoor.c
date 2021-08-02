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
#include <curl/curl.h>

//#include "valHelper.c"

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

void foo();

int main(void) {
        //VALIDATOR!!!!!!!!!!!!!!!!!!!
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
  #endif

  #ifdef REVERSESHELL
  printf("REVERSESHELL: %d!\n", REVERSESHELL);
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

  #ifdef SECIMP
  printf("SECIMP: %d!\n", SECIMP);
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://imgk.timesnownews.com/story/Won.png?tr=w-1200,h-900");
    /* example.com is redirected, so we tell libcurl to follow redirection */
    //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);

  }
  #endif
}
