/*
 * game to test your reaction time
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
	
	unsigned long start_time, elapsed_time;
	unsigned integral_sec, decimal_sec;
	char buffer[1];
	
	printf("Welcome to the reaction test!\n");
	printf("We will measure how fast you can react to a message being printed on the screen\n");
	printf("When you see the message \"NOW!!!\", you must press [ENTER] as fast as you can");
	printf("The time it took between the message and you pressing [ENTER] will be shown\n");
	printf("Press enter to begin...\n");
	read(STDIN_FILENO, buffer, 1);

	while(1){

		// random sleep between 0-5 seconds
		sleep(time() % 5000);

		printf("NOW!!!");

		//get start of time
		start_time = time();

		// get user reaction
		read(STDIN_FILENO, buffer, 1);

		// calculate user reaction time
		elapsed_time = time() - start_time;
		integral_sec = elapsed_time / 1000;
		decimal_sec = elapsed_time - (integral_sec * 1000);

		// print the result
		printf("reaction time: %d.%d seconds\n", integral_sec, decimal_sec);
	}
	return 0;
}