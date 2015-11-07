/** @file typo.c
 *
 * @brief Echos characters back with timing data.
 *
 * Links to libc.
 */

#include <stdio.h>
#include <unistd.h>

#define MAX_CHAR  512

int main(int argc, char** argv)
{
  char buf[MAX_CHAR];
  unsigned long start_time,elapsed_time;
  unsigned integral_sec, decimal_sec;
  int siz;

  while(1)
  { 
    printf("Time-Checker >: ");
    
    start_time = time();
    siz = read(STDIN_FILENO, buf, MAX_CHAR);
    if(siz <= 0)
      return 0;

    buf[siz-1] = '\0';

    elapsed_time = time() - start_time; // in milliseconds
    printf("Elapsed is %ld\n",elapsed_time);
    integral_sec = elapsed_time / 1000;
    decimal_sec = elapsed_time - (integral_sec * 1000);

    // We need the 10th place
    decimal_sec = decimal_sec / 100;
    
    // Echo user buffer
    printf("%s\n",buf);
    
    // Print time
    printf("%d.%d\n",integral_sec,decimal_sec);

  }

	return 0;
}
