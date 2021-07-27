#include <stdio.h>
#include <errno.h>
#include "functionality.h"
#include "helper.h"

extern int errno;

int main ()
{
  #ifdef OPENFile
  FILE * pFile;
  //trying to open the file
  pFile = fopen ("OPENFILE,"rb");
  //if the file is empty, then write error
  if (pFile == NULL)
  {
    my_perror("The following error occurred");
    my_printf( "Value of errno: %d\n", errno );
  }
  //if it can open, we are going to clise it 
  else {
    fclose (pFile);
  }
  #endif

  return 0;

}
