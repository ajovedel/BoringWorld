/** @file splat.c
 *
 * @brief Displays a spinning cursor.
 *
 * Links to libc.
 */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  char chars[] = {'|', '/', '-', '\\'};
  int i = 0;
	
  while(1){
    putchar(chars[i++]);
    sleep(200);
    putchar('\b');
    if(i == 4) 
      i = 0;
	}

	return 0;
}
