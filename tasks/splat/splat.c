/** @file splat.c
 *
 * @brief Displays a spinning cursor.
 *
 * Links to libc.
 */

#include <unistd.h>

int main(int argc, char** argv)
{
	while(1){
		write(STDOUT_FILENO, "|", 1);
		sleep(200);
		write(STDOUT_FILENO, "\b", 1);
		write(STDOUT_FILENO, "/", 1);
		sleep(200);
		write(STDOUT_FILENO, "\b", 1);
		write(STDOUT_FILENO, "-", 1);
		sleep(200);
		write(STDOUT_FILENO, "\b", 1);
		write(STDOUT_FILENO, "\\", 1);	
		sleep(200);
		write(STDOUT_FILENO, "\b", 1);
		sleep(200);
	}

	return 0;
}
