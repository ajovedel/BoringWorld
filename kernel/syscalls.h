
/*syscalls available for C_SWI_handler to call*/
void exit(int status);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
//unsigned long time();
//void sleep(unsigned long milis);
