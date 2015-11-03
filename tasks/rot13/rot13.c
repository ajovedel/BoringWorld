/*
 * rot13.c: ROT13 cipher test application
 *
 * Authors: Alejandro Jove <ajovedel@andrew.cmu.edu>
 * Date:    10-5-2015
 */

#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	unsigned int BUF_SIZE = 256;
	char buffer[BUF_SIZE];
	int bytes_read = 0, i;
	unsigned char flag = 0; 

	//print arguments
	for(i=0; i<argc; i++){
		write(STDOUT_FILENO, argv[i], 10);
		write(STDOUT_FILENO,"\n", 1);
	}
	
	while(1){
		//read initial line and check if it is just a newline char	
		bytes_read = read(STDIN_FILENO, buffer, BUF_SIZE);
		if(buffer[0] == '\n')
			return 0;

		//ser flag to 0 to indicate new user input line
		flag = 0;

		//loop through user input line
		while(flag == 0){

			//exit with 0 if zero bytes are read, excluding newline character		
			if(bytes_read == 0)
				return 0;

			//check for read syscall error
			if(bytes_read == -1)
				return 1;
		
			//check for lower and upper case letters and apply rot13
			for(i=0; i<bytes_read; i++){
				if((buffer[i] >= 'a' && buffer[i] <= 'm') || (buffer[i] >= 'A' && buffer[i] <= 'M'))
					buffer[i] += 13;
				else if((buffer[i] >= 'n' && buffer[i] <= 'z') || (buffer[i] >= 'N' && buffer[i] <= 'Z'))
					buffer[i] -= 13;
				if(buffer[i] == '\n')
					flag = 1;
			}
	
			//write to stdout and check for syscall error	
			if(write(STDOUT_FILENO, buffer, bytes_read) == -1)
				return 0;

			//check if newline char is found
			if(flag == 0)
				bytes_read = read(STDIN_FILENO, buffer, BUF_SIZE);
		}		
	}
	return -255;
}
