	#include <stdio.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <errno.h>
	#include <pthread.h>
	#include <stdbool.h>
	#include <stdint.h>
	#include <unistd.h>
	#include <sys/wait.h>
	#include <stdlib.h>

bool end = false;
int outfd = 0;
int infd = 0;
pthread_t out;

void sig_handler(int signo)
{
	printf("sig_handler\n");
	close(outfd);
	close(infd);
	exit(1);
}

void* outFunc(void*arg) 
{
	char buf[1];
	ssize_t ret;
	printf("outFunc opening %s\n", arg);
	outfd = open(arg, O_RDONLY | O_NONBLOCK);
	if ( outfd < 0 ) {
		perror("error opening file");
		exit(errno);
	}
	for(;;) {
		ret = read(outfd, buf, 1);
		if ( ret == -1 ) {
			usleep(100000);
		} else {
			printf("%c", buf[0]);
		}
	}
	close(outfd);
	return NULL;
}

void inFunc(void *arg)
{
	char buf[3];
	ssize_t ret;
	printf("inFunc opening %s\n", arg);
	infd = open(arg, O_WRONLY | O_APPEND);
	if ( infd < 0 ) {
		perror("error opening file");
		exit(errno);
	}
	for(;;) {
		ret = read(STDIN_FILENO, buf, sizeof(buf));
		if ( ret == -1 ) {
			usleep(100000);
		} else {
			//printf("READ FROM STDIN: %02x \n", buf[0]);
			ret = write(infd, buf, sizeof(buf));
			if ( ret < 0 ) {
				perror("write infd buf 1 ");
			}
		}
	}
	close(infd);
}

int main(int argc, char **argv)
{
	int fd;
	fd = open(argv[1], O_RDWR | O_NONBLOCK);
	if ( fd < 0 ) {
		perror("error opening file");
		exit(errno);
	}
	close(fd);
	signal(SIGINT, sig_handler);
	pthread_create(&out, NULL, outFunc, argv[1]);
	inFunc(argv[1]);
	pthread_join(out, NULL);
	close(fd);
	return 0;
}

