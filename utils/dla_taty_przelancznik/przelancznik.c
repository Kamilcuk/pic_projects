/*
  Copyright (C) 2003-2015 Kamil Cukrowski <kamil@dyzio.pl
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#include <stdio.h>
#include <libusb.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <signal.h>
#include <unistd.h>

/* my usb device */
#define VENDOR  0xffff
#define PRODUCT 0x0014
#define MACRO_TO_STR(macro) #macro
/* libusb */
struct libusb_device_handle *handle;

long long utime = 200000;
int treshold = 2;
char *exec_up = NULL;
char *exec_down = NULL;
int debug = 0;
int deamon = 1;

/* pthread */
pthread_t thread;
pthread_mutex_t lock;
static pthread_cond_t thread_signal;
unsigned char thread_cancel = 0;

static void safe_exit()
{
	printf("safe exit \n");
	libusb_exit(NULL);
	thread_cancel = 1;
	pthread_cond_signal(&thread_signal);
	pthread_join(thread, NULL);
	pthread_mutex_unlock(&lock);
    	pthread_cond_destroy(&thread_signal);
	pthread_mutex_destroy(&lock);
	exit(0);
}

#define fatal(mesg, ...) \
do {\
	printf(mesg, ##__VA_ARGS__);\
	exit(0);\
} while (0)

static void sig_hup ()
{
	printf("Cought signal. Shutting down.\n");
	exit(0);
}

int handle_libusb_bulk_transfer(struct libusb_device_handle *dev_handle, unsigned char endpoint, 
unsigned char *data, int length, unsigned int timeout)
{
	int ret;
	int len;
	int i;
	ret = libusb_bulk_transfer(dev_handle, endpoint, (unsigned char *)data, length, &len, timeout);
	switch(ret) {
	case 0:
		if ( debug ) {
			if ( endpoint&0x80 ) {
				printf(" received %d butes: ", len);
				for(i=0;i<len;i++)
					printf("%02x", data[i]);
				printf("\n");
			} else {
				printf(" sended %d butes: ", len);
				for(i=0;i<len;i++)
					printf("%c", data[i]);
				printf("\n");	
			}
		}
		break;
	case LIBUSB_ERROR_TIMEOUT:
		printf(" LIBUSB_ERROR_TIMEOUT \n");
		break;
	case LIBUSB_ERROR_PIPE:
		printf(" LIBUSB_ERROR_PIPE \n");
		break;
	case LIBUSB_ERROR_NO_DEVICE :
		printf(" LIBUSB_ERROR_NO_DEVICE  \n");
		fatal(" LIBUSB_ERROR_NO_DEVICE  \n");
		break;
	case LIBUSB_ERROR_OVERFLOW:
		printf("LIBUSB_ERROR_OVERFLOW \n");
		break;
	default:
		printf(" some funckgin error %d \n", ret);
	}
	return ret;
}

static void *thread_work(void *arg)
{
	unsigned char buff[2];
	for(;;) {
		
		if ( thread_cancel == 1 ) break;
		pthread_cond_wait(&thread_signal, &lock);
		if ( thread_cancel == 1 ) break;
		
		/* mutex locked after cond wait */
		
		printf("SIGUSR1 received. sending signal.\n");
		buff[0] = 'T';
		buff[1] = 0xff;
		handle_libusb_bulk_transfer(handle, 0x01, buff, 2, 1000);
		usleep(500000);
		buff[0] = 'T';
		buff[1] = 0x00;
		handle_libusb_bulk_transfer(handle, 0x01, buff, 2, 1000);
		
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

static void SIGUSR1_hup ()
{
	pthread_cond_signal(&thread_signal);
}

void parse_cmd(int argc, char **argv)
{
	int c=0;
	extern char *optarg;
	while (c != -1) {
		c=getopt(argc, argv, "ht:T:e:x:dDF");
		switch (c) {
		case 'h':
			printf("przelancznik: projekt dla taty.\n"
				"Program łączy się z modułem usb o vendorze " MACRO_TO_STR(VENDOR) "\n"
				" i o numerze product " MACRO_TO_STR(PRODUCT) "\n"
				"Program patrzy co jakiś czas czy odpowiedni pic jest zwarty \n"
				" po minięci udpowiedniej długości czasu, odpala polecenie podane na wiersz poleceń \n"
				" lub nic nie robi jeśli polecenia nie podano \n"
				"Ponadto jeśli program dostanie sygnał SIGUSR1 wysyła paczkę o zmianie \n"
				"stany odpowiedniego pinu na płytce \n"
				"\t-e\tpolecenie do uruchomienia po zwarciu kabli\n"
				"\t-x\tpolecenie do uruchowmienia po rozwarciu kabli\n"
				"\t-t\tczęstotść skanowania w microsekundach [%lld]\n"
				"\t-T\tco najmniej tyle razy musi utrzymać się się stan sygnału, by został zaakceptowany[%d]\n"
				"\t-d\t tryb debugowania \n"
				"\t-D\t uruchom w tle [defaultowo tak ma robić] \n"
				"\t-F\t nie uruchamiaj w tle\n"
				,
				utime,
				treshold
				);
			exit(0);
		case 't':
			utime = atoll(optarg);
			break;
		case 'T':
			treshold = atoi(optarg);
			break;
		case 'e':
			exec_up = optarg;
			break;
		case 'x':
			exec_down = optarg;
			break;
		case 'd':
			debug++;
			deamon = 0;
			break;
		case 'D':
			deamon = 1;
			break;
		case 'F':
			deamon = 0;
			break;
		}
	}
}

void run(char *what)
{
	pid_t child_pid;
	
	if ( what == NULL )
		return;
	
	/* Duplicate this process.  */
	child_pid = fork ();
	if (child_pid != 0) {
		/* This is the parent process.  */
		return;
	} else {
		fclose(stdin);
		
		/* Now execute PROGRAM, searching for it in the path.  */
		system(what);
		/* The execvp function returns only if an error occurs.  */
		fprintf (stderr, "an error occurred in execvp\n");
		abort (); /* hell not exit! */
	}
}

int daemonize(void) 
{
	int PID;
	PID = fork();
	switch ( PID ) {
	case 0:
		fclose(stderr);
		fclose(stdin);
		fclose(stdout);
		break;
	case -1:
		break;
	default:
		abort();
	}
	return(PID);
}

int main(int argc, char **argv)
{
	unsigned char stan = 0x00;
	int cnt = 0;
	unsigned char buff[64];
	int ret;
	
	parse_cmd(argc,argv);
	
	printf("Łączenie z urządzeniem.\n");
	
	if ( libusb_init(NULL) != 0 ) {
		printf(" libusb_open_erro \n ");
		return -1;
	}
	handle = libusb_open_device_with_vid_pid(NULL, VENDOR, PRODUCT);
	if ( !handle ) {
		printf(" not conected \n");
		return -1;
	}
	printf(" Connected to device ! \n");
	
	printf("Wysyłanie początkowych ządań do urządzenia.\n");
	
	/* obtain first one */
	handle_libusb_bulk_transfer(handle, 0x82, buff, sizeof(buff), 1000);
	handle_libusb_bulk_transfer(handle, 0x82, buff, sizeof(buff), 1000);
	stan = buff[0];
	
	printf("Konfigurowanie programu.\n");
	atexit(safe_exit);
	signal(SIGHUP, sig_hup);
	signal(SIGQUIT, sig_hup);
	signal(SIGTERM, sig_hup);
	signal(SIGINT, sig_hup);
	signal(SIGUSR1, SIGUSR1_hup);
	
	ret = pthread_cond_init(&thread_signal, NULL);
	if (ret != 0) {
		printf("pthread_cond_init ret=%d\n", ret);
		return ret;
	}
	ret = pthread_mutex_init(&lock, NULL);
	if (ret != 0) {
		printf("pthread_mutex_init ret=%d\n", ret);
		return ret;
	}
	ret = pthread_create(&thread, NULL, &thread_work, NULL);
	if (ret != 0) {
		printf("pthread_create ret=%d strerorr(ret)=%s", ret, strerror(ret));
		return ret;
	}
	
	printf("ALL ok. Forking into background.\n");
	if ( deamon ) {
		daemonize();
	}
	
	for(;;) {
		
		pthread_mutex_lock(&lock);
		handle_libusb_bulk_transfer(handle, 0x82, buff, sizeof(buff), 1000);
		pthread_mutex_unlock(&lock);
		
		if ( stan == buff[0] ) {
			cnt = 0;
		} else {
			cnt++;
			if ( cnt >= treshold ) {
				stan = buff[0];
				if ( stan ) {
					run(exec_up);
				} else {
					run(exec_down);
				}
				cnt = 0;
			}
		}
		
		usleep(utime);
		
		if ( debug ) {
			printf(" > received buff[0] = %d:%02x \n", buff[0], buff[0]);
			printf(" > stan = %d:%x \n", stan, stan);
			printf(" > cnt = %d\n", cnt);
			printf(" > sleep for %lld microseconds \n", utime);
		}
	}
	
	return 0;
}

