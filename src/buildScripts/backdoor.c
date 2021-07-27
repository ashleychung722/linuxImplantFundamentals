//#define IPADDR "192.168.1.1"

#include <stdio.h>


int main (int argc, char const *argv[])
{
  #ifdef DEBUG
  printf("%s!\n", IPADDR);
  #endif

  #ifdef IP
  printf("%s!\n", IPADDR);
  #endif

  #ifdef DOMAIN
  printf("%s!\n", IPADDR);
  #endif

  #ifdef PLATFORM
  printf("%s!\n", IPADDR);
  #endif

  #ifdef ARCH
  printf("%s!\n", IPADDR);
  #endif

  #ifdef OS
  printf("%s!\n", IPADDR);
  #endif

  #ifdef VERSION_NUM
  printf("%s!\n", IPADDR);
  #endif

  #ifdef PAYLOAD
  printf("%s!\n", IPADDR);
  #endif

  #ifdef INTERFACE
  printf("%s!\n", IPADDR);
  #endif

  return 0;
}
