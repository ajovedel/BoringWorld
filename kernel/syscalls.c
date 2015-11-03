#include <exports.h>
#include <bits/errno.h>
#include <bits/fileno.h>
#include "syscalls.h"


/* read N character from STDIN and place it in a buffer */
ssize_t read(int fd, void *buf, size_t count){
	
	unsigned i;
	unsigned char temp;

	// fd has to be STDIN, otherwise return bad fd
	if(fd != STDIN_FILENO)
		return -EBADF;

	// verify that buf and buf+count is in range of SDRAM (A0000000-A3FFFFFF)
	if(!((unsigned)buf > 0xA0000000 && (unsigned)buf < 0xA3FFFFFF))
		return -EFAULT;
	if(!(((unsigned)buf+(unsigned)count) > 0xA0000000 && ((unsigned)buf+(unsigned)count) < 0xA3FFFFFF))
		return -EFAULT;

	for(i=0; i<count; i++){

		// get the character from STDIN
		temp = getc();

		// check for EOT character
		if(temp == 4)
			return ++i;

		// check for backspace or delete
		else if(temp == 8 || temp == 127)
			puts("\b \b");
			
		// check for newline and carriage return
		else if(temp == '\n' || temp == '\r'){
			((char *)buf)[i] = '\n';
			putc('\n');
			return ++i;
		}

		// if not a special char, read to buffer and write to STDOUT
		else{
			((char *)buf)[i] = temp;
			putc(((char*)buf)[i]);
		}
	}
	putc('\n');
	return i;
}


/* read N characters from a buffer and place it in STDOUT */
ssize_t write(int fd, const void *buf, size_t count){
	
	unsigned i;

	// fd has to be STDOUT, otherwise return bad fd
	if (fd != STDOUT_FILENO)
		return -EBADF;

	// verify that buf and buf+count is in range of SDRAM (A0000000-A3FFFFFF)
	// or StrataFlash ROM (0 - 00FFFFFF)
	if(!(((unsigned)buf > 0xA0000000 && (unsigned)buf < 0xA3FFFFFF) || ((unsigned)buf < 0xFFFFFF)))
		return -EFAULT;
	if(!((((unsigned)buf+(unsigned)count) > 0xA0000000 && ((unsigned)buf+(unsigned)count) < 0xA3FFFFFF) || (((unsigned)buf+(unsigned)count) < 0xFFFFFF)))
		return -EFAULT;

	// write buffer to STDOUT
	for(i=0; i<count; i++){

		// return if null is reached
		if(((char *)buf)[i] == '\0')
			return i;

		putc(((char*)buf)[i]);
	}
	return i;
}
