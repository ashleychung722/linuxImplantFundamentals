//#define IPADDR "192.168.1.1"

#include <stdio.h>


int main (int argc, char const *argv[])
{
  #ifdef DEBUG
  printf("Error occurred!\n", DEBUG);
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

  return 0;
}
