/*******************************************************************************
 * Author :
 * Description :
 * Created :
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "commands.c"
int main(int argc, char * argv[]) {
    curlDown("http://localhost:8000/kitten-looking-at-camera.jpg","kitty.jpg");
    return 0;
}
