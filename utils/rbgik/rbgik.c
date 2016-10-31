/*
  Copyright (C) 2003-2014 Kamil Cukrowski <kamil@dyzio.pl
  based on aubio-0.4.1/examples/*.c written by Paul Brossier <piem@aubio.org>

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


#define PROG_HAS_ONSET 1
#define PROG_HAS_OUTPUT 1
#define PROG_HAS_JACK 1
#define HAVE_JACK 1

#include "utils.h"
#include "parse_args.h"
#include "jackio.h"
#include "jackio.c"
#include "utils.c"

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

#include <setjmp.h>
#include <signal.h>

#include <pthread.h>

#include <gtk/gtk.h>

int debug = 0;
int use_parse_cmd = 1;
int mode = 5;
int use_gtk = 1;
int use_usb = 1;
int usb_error = 0;

/* my usb device */
#define VENDOR  0xffff
#define PRODUCT 0x0011

/* timer */
#define TIMER_TV_SEC 1 /* timer seconds */
#define TIMER_TV_USEC 250000000 /* time useconds */
static timer_t timer_id = 0;

/* libusb */
libusb_context *ctx;
struct libusb_device_handle *handle;

/* aubioonset.c */
aubio_onset_t *o;
aubio_wavetable_t *wavetable;
fvec_t *onset;
smpl_t is_onset;

/* aubiotrack.c */
aubio_tempo_t * tempo;
aubio_wavetable_t *wavetable;
fvec_t * tempo_out;
smpl_t is_beat = 0;
uint_t is_silence = 0.;

/* gtk */
GtkWidget *window;
GdkRGBA color;


/* aktualny stan ! */
struct {
	unsigned char R, G, B, S;
} stan;

char colors[][10] = {
"0x000000",
"0x000033",
"0x000066",
"0x000099",
"0x0000CC",
"0x0000FF",
"0x003300",
"0x003333",
"0x003366",
"0x003399",
"0x0033CC",
"0x0033FF",
"0x006600",
"0x006633",
"0x006666",
"0x006699",
"0x0066CC",
"0x0066FF",
"0x009900",
"0x009933",
"0x009966",
"0x009999",
"0x0099CC",
"0x0099FF",
"0x00CC00",
"0x00CC33",
"0x00CC66",
"0x00CC99",
"0x00CCCC",
"0x00CCFF",
"0x00FF00",
"0x00FF33",
"0x00FF66",
"0x00FF99",
"0x00FFCC",
"0x00FFFF",
"0x330000",
"0x330033",
"0x330066",
"0x330099",
"0x3300CC",
"0x3300FF",
"0x333300",
"0x333333",
"0x333366",
"0x333399",
"0x3333CC",
"0x3333FF",
"0x336600",
"0x336633",
"0x336666",
"0x336699",
"0x3366CC",
"0x3366FF",
"0x339900",
"0x339933",
"0x339966",
"0x339999",
"0x3399CC",
"0x3399FF",
"0x33CC00",
"0x33CC33",
"0x33CC66",
"0x33CC99",
"0x33CCCC",
"0x33CCFF",
"0x33FF00",
"0x33FF33",
"0x33FF66",
"0x33FF99",
"0x33FFCC",
"0x33FFFF",
"0x660000",
"0x660033",
"0x660066",
"0x660099",
"0x6600CC",
"0x6600FF",
"0x663300",
"0x663333",
"0x663366",
"0x663399",
"0x6633CC",
"0x6633FF",
"0x666600",
"0x666633",
"0x666666",
"0x666699",
"0x6666CC",
"0x6666FF",
"0x669900",
"0x669933",
"0x669966",
"0x669999",
"0x6699CC",
"0x6699FF",
"0x66CC00",
"0x66CC33",
"0x66CC66",
"0x66CC99",
"0x66CCCC",
"0x66CCFF",
"0x66FF00",
"0x66FF33",
"0x66FF66",
"0x66FF99",
"0x66FFCC",
"0x66FFFF",
"0x990000",
"0x990033",
"0x990066",
"0x990099",
"0x9900CC",
"0x9900FF",
"0x993300",
"0x993333",
"0x993366",
"0x993399",
"0x9933CC",
"0x9933FF",
"0x996600",
"0x996633",
"0x996666",
"0x996699",
"0x9966CC",
"0x9966FF",
"0x999900",
"0x999933",
"0x999966",
"0x999999",
"0x9999CC",
"0x9999FF",
"0x99CC00",
"0x99CC33",
"0x99CC66",
"0x99CC99",
"0x99CCCC",
"0x99CCFF",
"0x99FF00",
"0x99FF33",
"0x99FF66",
"0x99FF99",
"0x99FFCC",
"0x99FFFF",
"0xCC0000",
"0xCC0033",
"0xCC0066",
"0xCC0099",
"0xCC00CC",
"0xCC00FF",
"0xCC3300",
"0xCC3333",
"0xCC3366",
"0xCC3399",
"0xCC33CC",
"0xCC33FF",
"0xCC6600",
"0xCC6633",
"0xCC6666",
"0xCC6699",
"0xCC66CC",
"0xCC66FF",
"0xCC9900",
"0xCC9933",
"0xCC9966",
"0xCC9999",
"0xCC99CC",
"0xCC99FF",
"0xCCCC00",
"0xCCCC33",
"0xCCCC66",
"0xCCCC99",
"0xCCCCCC",
"0xCCCCFF",
"0xCCFF00",
"0xCCFF33",
"0xCCFF66",
"0xCCFF99",
"0xCCFFCC",
"0xCCFFFF",
"0xFF0000",
"0xFF0033",
"0xFF0066",
"0xFF0099",
"0xFF00CC",
"0xFF00FF",
"0xFF3300",
"0xFF3333",
"0xFF3366",
"0xFF3399",
"0xFF33CC",
"0xFF33FF",
"0xFF6600",
"0xFF6633",
"0xFF6666",
"0xFF6699",
"0xFF66CC",
"0xFF66FF",
"0xFF9900",
"0xFF9933",
"0xFF9966",
"0xFF9999",
"0xFF99CC",
"0xFF99FF",
"0xFFCC00",
"0xFFCC33",
"0xFFCC66",
"0xFFCC99",
"0xFFCCCC",
"0xFFCCFF",
"0xFFFF00",
"0xFFFF33",
"0xFFFF66",
"0xFFFF99",
"0xFFFFCC",
"0xFFFFFF",
};

struct libusb_device_handle *usb_connect(libusb_context *ctx, int vendor, int product)
{
	struct libusb_transfer *transfer;
	struct libusb_device_handle *handle;
	int result, count;
	int restore_kernel_driver = 0;

	count = 0;
	result = libusb_init(&ctx);
	if (result < 0) {
		printf("Error %i initializing usb context\n", result);
		goto quit;
	}

	libusb_set_debug(ctx, 3);

	/* Detect device */
	handle = libusb_open_device_with_vid_pid(ctx, vendor, product);
	if (handle == NULL) {
		printf("Cannot find device %hX, %hX\n", vendor, product);
		goto clean_context;
	}

	result = libusb_kernel_driver_active(handle, 0);
	if (result < 0) {
		printf("Error %i checking kernel driver\n", result);
		goto clean_handle;
	}
	if (result > 1) {
		result = libusb_detach_kernel_driver(handle, 0);
		if (result < 0) {
			printf("Error %i detaching kernel driver\n", result);
			goto clean_handle;
		}
		restore_kernel_driver = 1;
	}

	result = libusb_claim_interface(handle, 0);
	if (result < 0) {
		printf("Error %i claiming interface\n", result);
		goto restore_kernel_driver;
	}

	return handle;
	
 release_interface:
	libusb_release_interface(handle, 0);

 restore_kernel_driver:
	if (restore_kernel_driver)
		libusb_attach_kernel_driver(handle, 0);

 clean_handle:
	libusb_close(handle);

 clean_context:
	libusb_exit(ctx);
	
 quit:
	return NULL;
}

struct libusb_device_handle *usb_disconnect(libusb_context *ctx, struct libusb_device_handle *handle)
{
	libusb_release_interface(handle, 0);
	libusb_close(handle);
	libusb_exit(ctx);
	return NULL;
}

void gtk_set(char *buff)
{
	if ( buff[0] >= '0' && buff[0] <= '9' && buff[1] == 'x' ) {
		char buf[20];
		snprintf(buf, 20, "#%6s\0", &buff[2]);
		//printf(" sendinf %s \n", buf);
		gdk_rgba_parse(&color, buf);
		gtk_widget_override_background_color (window, GTK_STATE_NORMAL, &color); 
		gtk_widget_show (window);
		int i=0;
		for(i=0; i<256; i++) {
			gtk_main_iteration_do(FALSE);
		}
	}
}


/**
 * convertuje dwa znaki ascii hex na liczbe 0-255 int
 * d - liczba dziesiatek hex
 * j - liczba jednosci szesnastokowo
 * return - liczba int powstala z 0xdj 
 * wspierane tylko lowerletters */
unsigned char my_strtol(unsigned char d, unsigned char j)
{
	unsigned char num;
	
	if ( d >= '0' && d <= '9') {
		num = (d-'0');
	} else if ( d >= 'a' && d <= 'f' ) {
		num = (d-'a')+10;
	} else if ( d >= 'A' && d <= 'F' ) {
		num = (d-'A')+10; 
	} else {
		num = 0xa;
	}
	
	num <<= 4;
	
	if ( j >= '0' && j <= '9') {
		num |= (j-'0');
	} else if ( j >= 'a' && j <= 'f' ) {
		num |= (j-'a')+10;
	} else if ( j >= 'A' && j <= 'F' ) {
		num |= (j-'A')+10; 
	} else {
		num |= 0xa;
	}
	
	return num;
}

void rbgik_send(char *buf)
{
	int ret;
	int len;
	unsigned char buff[20];
	
	if ( buf[0] >= '0' && buf[0] <= '9' && buf[1] == 'x' ) {
		
		buff[0] = buf[1];
		buff[1] = 0x00;
		buff[2] = my_strtol(buf[4], buf[5]);
		buff[3] = my_strtol(buf[6], buf[7]);
		buff[4] = my_strtol(buf[2], buf[3]);
		
		stan.R = buff[2];
		stan.G = buff[3];
		stan.B = buff[4];
		stan.S = 100;
		
	}
	
	//printf("sending %c=%02x:%02x:%02x \n", buff[0], buff[2]&0xff, buff[3]&0xff, buff[4]&0xff);
	
	if ( use_usb ) {
		ret = libusb_bulk_transfer(handle, 0x01, buff, 5, &len, 1000);
		switch(ret) {
		case 0:
			//printf(" sended %d butes: %s  \n", len, buff);
			break;
		case LIBUSB_ERROR_TIMEOUT:
			printf(" LIBUSB_ERROR_TIMEOUT \n");
			break;
		case LIBUSB_ERROR_PIPE:
			printf(" LIBUSB_ERROR_PIPE \n");
			break;
		case LIBUSB_ERROR_NO_DEVICE :
			printf(" LIBUSB_ERROR_NO_DEVICE  \n");
			break;
		case LIBUSB_ERROR_OVERFLOW:
			printf("LIBUSB_ERROR_OVERFLOW \n");
			break;
		default:
			printf(" some funckgin error \n");
		}
	}
	
	if ( use_gtk )
		gtk_set(buf);
}

void rgb(unsigned char R,unsigned char G,unsigned char B,unsigned char S)
{
	char buff[20];
	
	if ( debug )
		printf("RGBS %3d %3d %3d %3d \n", R, G, B, S);
	
	if ( S >= 100 )
		S = 100;
	R = (float)R*(float)S/(float)100;
	G = (float)G*(float)S/(float)100;
	B = (float)B*(float)S/(float)100;
	
	snprintf(buff, 20, "0x%02x%02x%02x", R, G, B);
	
	rbgik_send(buff);
	
	stan.R = R;
	stan.G = G;
	stan.B = B;
	stan.S = S;
}

void do_the_job(void)
{
	static unsigned int pos = 0;
	unsigned int new_pos;
	unsigned char E, R, B, G;
	
	/*do {
		new_pos = rand()%(sizeof(colors)/sizeof(*colors));
	} while ( new_pos == pos );
	pos = new_pos;*/
	
	E = rand()%2 ? 60.0 : 100.0;
	R = rand() % 255 * E/100.0;
	G = rand() % 255 * E/100.0;
	B = rand() % 255 * E/100.0;
	
	rgb(R, G, B, E);
	
	//printf("%s\n", colors[pos]);
	//rbgik_send(colors[pos]);
	
	/* pos++;
	if ( pos >= sizeof(colors)/sizeof(*colors) )
		pos = 0; */
	/*
	
	switch(pos) {
	case 0:
		send("0x0000ff");
		break;
	case 1:
		send("0x00ffff");
		break;
	case 2:
		send("0x00ff00");
		break;
	case 3:
		send("0xffff00");
		break;
	case 4:
		send("0xff0000");
		break;
	case 5:
		pos = 0;
		send("0xff00ff");
		break;
	}
	
	pos++;
	* */
}

int process_block_onset(fvec_t * ibuf, fvec_t * obuf)
{
	aubio_onset_do(o, ibuf, onset);
	is_onset = fvec_get_sample(onset, 0);
	if (!usejack && !sink_uri)
		return 0;
	fvec_zeros(obuf);

	if (is_onset) {
		do_the_job();
	}
	
	if (mix_input) {
		aubio_wavetable_do(wavetable, ibuf, obuf);
	} else {
		aubio_wavetable_do(wavetable, obuf, obuf);
	}
	return 0;
}

void process_block_track(fvec_t * ibuf, fvec_t *obuf) 
{
	aubio_tempo_do (tempo, ibuf, tempo_out);
	is_beat = fvec_get_sample (tempo_out, 0);
	if (silence_threshold != -90.)
		is_silence = aubio_silence_detection(ibuf, silence_threshold);
	if ( !usejack && ! sink_uri ) 
		return;
	fvec_zeros (obuf);
	if ( is_beat && !is_silence ) {
		do_the_job();
	}
	if (mix_input)
		aubio_wavetable_do (wavetable, ibuf, obuf);
	else
		aubio_wavetable_do (wavetable, obuf, obuf);
}

void process_print(void)
{
	if ( is_onset ) {
		outmsg ("%f\n", aubio_onset_get_last_s (o) );
	}
}

void do_onset(int argc, char **argv)
{
	examples_common_init(argc, argv);
	
	verbmsg("using source: %s at %dHz\n", source_uri, samplerate);
	verbmsg("onset method: %s, ", onset_method);
	verbmsg("buffer_size: %d, ", buffer_size);
	verbmsg("hop_size: %d, ", hop_size);
	verbmsg("silence: %f, ", silence_threshold);
	verbmsg("threshold: %f\n", onset_threshold);

	
	o = new_aubio_onset(onset_method, buffer_size, hop_size, samplerate);
	if (onset_threshold != 0.)
		aubio_onset_set_threshold(o, onset_threshold);
	if (silence_threshold != -90.)
		aubio_onset_set_silence(o, silence_threshold);

	onset = new_fvec(1);

	wavetable = new_aubio_wavetable(samplerate, hop_size);
	aubio_wavetable_set_freq(wavetable, 2450.);

	//examples_common_process((aubio_process_func_t) process_block_onset, 
	//	process_print);

	printf ("Jack activation ...\n");
	aubio_jack_activate (jack_setup, process_block_onset);
	printf ("Processing (Ctrl+C to quit) ...\n");
	
	for(;;)
		pause();
	
	aubio_jack_close (jack_setup);

	del_aubio_onset(o);
	del_aubio_wavetable(wavetable);
	del_fvec(onset);

	
	examples_common_del();
}

void do_track(int argc, char **argv)
{
	// override general settings from utils.c
	
	buffer_size = 1024;
	hop_size = 512;
	
	examples_common_init(argc,argv);
	
	verbmsg ("using source: %s at %dHz\n", source_uri, samplerate);
	verbmsg ("tempo method: %s, ", tempo_method);
	verbmsg ("buffer_size: %d, ", buffer_size);
	verbmsg ("hop_size: %d, ", hop_size);
	verbmsg ("threshold: %f\n", onset_threshold);
	
	tempo_out = new_fvec(2);
	tempo = new_aubio_tempo(tempo_method, buffer_size, hop_size, samplerate);
	if (onset_threshold != 0.) 
		aubio_tempo_set_threshold (tempo, onset_threshold);
	
	wavetable = new_aubio_wavetable (samplerate, hop_size);
	aubio_wavetable_set_freq ( wavetable, 2450.);
	
	examples_common_process((aubio_process_func_t)process_block_track,process_print);
	
	del_aubio_tempo(tempo);
	del_aubio_wavetable (wavetable);
	del_fvec(tempo_out);
	
	examples_common_del();
}

void do_random(int argc, char **argv)
{
	unsigned char R, G, B, time, buff[20];
	float E;
	for(;;) {
		E = 100.0;
		R = rand() % 255 * E/100.0;
		G = rand() % 255 * E/100.0;
		B = rand() % 255 * E/100.0;
		time = rand() % 500 + 200;
		
		snprintf(buff, 20, "0x%.2x%.2x%.2x", R, G, B); 
		
		printf(" %s \n", buff);
		
		rbgik_send(buff);
		usleep(time*1000);
		
		
		E = 30.0;
		R = rand() % 255 * E/100.0;
		G = rand() % 255 * E/100.0;
		B = rand() % 255 * E/100.0;
		time = rand() % 500 + 200;
		
		snprintf(buff, 20, "0x%.2x%.2x%.2x", R, G, B); 
		
		printf(" %s \n", buff);
		
		rbgik_send(buff);
		usleep(time*1000);
		
		
		
		E = 30.0;
		R = rand() % 255 * E/100.0;
		G = rand() % 255 * E/100.0;
		B = rand() % 255 * E/100.0;
		time = rand() % 500 + 200;
		
		snprintf(buff, 20, "0x%.2x%.2x%.2x", R, G, B); 
		
		printf(" %s \n", buff);
		
		rbgik_send(buff);
		usleep(time*1000);
	}
	
}

void gtk_start(int argc,char **argv)
{
	gtk_init (&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	gtk_widget_show (window);
	int i;
	for(i = 0; i < 256; ++i) {
		gtk_main_iteration_do(FALSE);
	}
}

void do_fajna_zmiana(int argc, char **argv)
{
	float R=0, G=0, B=0, E=100, time, buff[20];
	float nR, nG, nB, nE;
	float krokR, krokG, krokB, krokE;
	float i;
	const int OPOZNIENIE = 2;
	int ilosc_krokow;
	
	printf(" fdnasjkdfnasjknf \n");
	sleep(1);
	
	for(;;) {
		
		nE = rand()%4;
		switch((int)nE) {
			case 0: nE = 100; break;
			case 1: nE = 30; break;
			case 2: nE = 50; break;
			case 3: nE = 60; break;
		}
		//nE = 100.0;
		nR = rand() % 255;
		nG = rand() % 255;
		nB = rand() % 255;
		
		const int war = 40;
		const int sre = (nR+nG+nB)/3;
		if ( abs(sre - nG) < war ||
				abs(sre - nB) < war ||
				abs(sre - nR) < war ) {
			printf("  ONCE AGAIN: [R;B;G;E]:[%3.0f;%3.0f;%3.0f;%3.0f] \n", nR, nG, nB, nE);
			continue;
		}
		
		nR *= nE/100.0;
		nG *= nE/100.0;
		nB *= nE/100.0;
		
		ilosc_krokow = 500;
		time = OPOZNIENIE*ilosc_krokow;
		
		krokE = (nE-E)/ilosc_krokow;
		krokR = (nR-R)/ilosc_krokow;
		krokG = (nG-G)/ilosc_krokow;
		krokB = (nB-B)/ilosc_krokow;
		
		printf("WAS: [R;B;G;E]:[%3.0f;%3.0f;%3.0f;%3.0f] will be: [R;B;G;E]:[%3.0f;%3.0f;%3.0f;%3.0f] \n", R, G, B, E, nR, nG, nB, nE);
		printf("czas[ms]:%.0f ilość_kroków:%d || kroki[R;B;G;E]:[%3.3f;%3.3f;%3.3f;%3.3f] \n", time, ilosc_krokow, krokR, krokG, krokB, krokE);
		
		for(i=0; i<ilosc_krokow; i+=1) {
			
			R += krokR;
			G += krokG;
			B += krokB;
			E += krokE;
			
			rgb(R, G, B, E);
			
			usleep(OPOZNIENIE*1000);
		}
		
		usleep(1000000);
		
		R = nR;
		E = nE;
		G = nG;
		B = nB;
		
	}
}


void do_fajna_zmiana2(int argc, char **argv)
{
	float R=0, G=0, B=0, E=100, time, buff[20];
	float nR, nG, nB, nE;
	float krokR, krokG, krokB, krokE;
	float i;
	const int OPOZNIENIE = 2;
	int ilosc_krokow;
	
	printf(" fdnasjkdfnasjknf \n");
	sleep(1);
	
	for(;;) {
		
		nE = rand()%4;
		switch((int)nE) {
			case 0: nE = 100; break;
			case 1: nE = 30; break;
			case 2: nE = 50; break;
			case 3: nE = 60; break;
		}
		
		switch((int)(rand()%3)) {
			case 0:
				nR = 255;
				nG = rand() % 255;
				nB = rand() % 255;
				break;
			case 1:
				nR = rand() % 255;
				nG = 255;
				nB = rand() % 255;
				break;
			case 2:
				nR = rand() % 255;
				nG = rand() % 255;
				nB = 255;
				break;
		}
		
		//nE = 100.0;
		//nR = rand() % 255;
		//nG = rand() % 255;
		//nB = rand() % 255;
		
		const int war = 180*3;
		if ( nG+nB+nR > war ) {
			printf("  ONCE AGAIN: [R;B;G;E]:[%3.0f;%3.0f;%3.0f;%3.0f] \n", nR, nG, nB, nE);
			continue;
		}
		
		nR *= nE/100.0;
		nG *= nE/100.0;
		nB *= nE/100.0;
		
		ilosc_krokow = 500;
		time = OPOZNIENIE*ilosc_krokow;
		
		krokE = (nE-E)/ilosc_krokow;
		krokR = (nR-R)/ilosc_krokow;
		krokG = (nG-G)/ilosc_krokow;
		krokB = (nB-B)/ilosc_krokow;
		
		printf("WAS: [R;B;G;E]:[%3.0f;%3.0f;%3.0f;%3.0f] will be: [R;B;G;E]:[%3.0f;%3.0f;%3.0f;%3.0f] \n", R, G, B, E, nR, nG, nB, nE);
		printf("czas[ms]:%.0f ilość_kroków:%d || kroki[R;B;G;E]:[%3.3f;%3.3f;%3.3f;%3.3f] \n", time, ilosc_krokow, krokR, krokG, krokB, krokE);
		
		for(i=0; i<ilosc_krokow; i+=1) {
			
			R += krokR;
			G += krokG;
			B += krokB;
			E += krokE;
			
			rgb(R, G, B, E);
			
			usleep(OPOZNIENIE*1000);
		}
		
		usleep(1000000);
		
		R = nR;
		E = nE;
		G = nG;
		B = nB;
		
	}
}

struct kolor_s {
	float R, G, B, E;
};

struct kolor_s losuj_kolor(void) 
{
	struct kolor_s n;
	while(1) {
		switch((int)(rand()%2)) {
			case 0: n.E = 100; break;
			case 1: n.E = 80; break;
		}
		
		switch((int)(rand()%3)) {
			case 0:
				n.R = 255;
				n.G = rand() % 255;
				n.B = rand() % 255;
				break;
			case 1:
				n.R = rand() % 255;
				n.G = 255;
				n.B = rand() % 255;
				break;
			case 2:
				n.R = rand() % 255;
				n.G = rand() % 255;
				n.B = 255;
				break;
		}
		
		//n.E = 100.0;
		//n.R = rand() % 255;
		//n.G = rand() % 255;
		//n.B = rand() % 255;
		
		const int war = 180*3;
		if ( n.G+n.B+n.R > war ) {
			printf("  ONCE AGAIN: [R;B;G;E]:[%3.0f;%3.0f;%3.0f;%3.0f] \n", n.R, n.G, n.B, n.E);
			continue;
		}
		
		n.R *= n.E/100.0;
		n.G *= n.E/100.0;
		n.B *= n.E/100.0;
		
		break;
	}
	return n;
}

void kolor_zmien(struct kolor_s o, struct kolor_s n)
{
	const int OPOZNIENIE = 2; /* najmniejsze opóźnienie miedzy zmianą kolorów możliwe */
	int ilosc_krokow;
	int time;
	int i;
	struct kolor_s krok;
	
	ilosc_krokow = 500;
	time = OPOZNIENIE*ilosc_krokow;
	// ilosc_krokow = time/OPOZNIENIE;
	
	krok.E = (n.E-o.E)/ilosc_krokow;
	krok.R = (n.R-o.R)/ilosc_krokow;
	krok.G = (n.G-o.G)/ilosc_krokow;
	krok.B = (n.B-o.B)/ilosc_krokow;
	
	printf("WAS: [R;B;G;E]:[%3.0f;%3.0f;%3.0f;%3.0f] will be: [R;B;G;E]:[%3.0f;%3.0f;%3.0f;%3.0f] \n", o.R, o.G, o.B, o.E, n.R, n.G, n.B, n.E);
	printf("czas[ms]:%.0f ilość_kroków:%d || kroki[R;B;G;E]:[%3.3f;%3.3f;%3.3f;%3.3f] \n", time, ilosc_krokow, krok.R, krok.G, krok.B, krok.E);
	
	for(i=0; i<ilosc_krokow; i+=1) {
		
		o.R += krok.R;
		o.G += krok.G;
		o.B += krok.B;
		o.E += krok.E;
		
		rgb((unsigned char)o.R, (unsigned char)o.G, (unsigned char)o.B, (unsigned char)o.E);
		
		usleep(OPOZNIENIE*1000);
	}
}

void do_zmieniaj_czarne_kolor(int argc, char **argv)
{
	struct kolor_s zero, n;
	zero = (struct kolor_s){0, 0, 0, 100};
	
	for(;;) {
		n = losuj_kolor();
		kolor_zmien(zero, n);
		sleep(1);
		kolor_zmien(n, zero);
	}
}

void keyboard_input(int argc, char **argv)
{
	char buff[256];
		for(;;) {
			if ( fgets(buff, sizeof(buff), stdin) != NULL ) {
				buff[strlen(buff)-1] = '\0';
				printf(" \"%s\" %d \n", buff, strlen(buff));
				rbgik_send(buff);
			}
		}
}
void mrygaj_bialo_ciemno(int argc, char** argv)
{
	
		for(;;) {
			rbgik_send("0x000000");
			rbgik_send("0xffffff");
		}
}
void nie_wiem()
{
		unsigned char R,G,B,S;
		int utime = 1000*100;
		R = 0xff;
		G = 0;
		B = 0;
		S = 0;
		for(;;) {
			for(R=0;R<=0xff;R++) {
				rgb(R, G, B, 100);
				usleep(utime);
			}
		}
		for(;;) {
			for(S=0;S<=100;++S) {
				rgb(R, G, B, S);
				usleep(utime);
			}
			for(S=100;S != 0;--S) {
				rgb(R, G, B, S);
				usleep(utime);
			}
		}
}
void nie_wiem2()
{
	char buff[256];
		float E;
		int R, G, B, time;
		for(;;) {
			E = 100.0;
			R = rand() % 255 * E/100.0;
			G = rand() % 255 * E/100.0;
			B = rand() % 255 * E/100.0;
			time = rand() % 500 + 200;
			
			snprintf(buff, 20, "0x%.2x%.2x%.2x", R, G, B); 
			
			printf(" %s \n", buff);
			
			rbgik_send(buff);
			sleep(2);
		}
}

void do_fun(int mode, int argc, char **argv)
{
	switch(mode) {
	case 0:
		keyboard_input(argc, argv);
		break;
	case 1:
		mrygaj_bialo_ciemno(argc, argv);
		break;
	case 2:
		nie_wiem();
		break;
	case 3:
		nie_wiem2();
		break;
	case 4:
		do_random(argc, argv);
		break;
	case 5:
		do_onset(argc, argv);
		break;
	case 6:
		do_track(argc, argv);
		break;
	case 7:
		break;
	case 8:
		do_fajna_zmiana(argc, argv);
		break;
	case 9:
		do_fajna_zmiana2(argc, argv);
		break;
	case 10:
		do_zmieniaj_czarne_kolor(argc, argv);
		break;
	}
}

static void parse_cmd(int argc, char *argv[])
{
	int c=0;
	extern char *optarg;
	while (c != -1) {
		c=getopt(argc, argv, "hgum:");
		switch (c) {
		case 'h':
			printf(
				"[USAGE] rbgik [OPTION]...\n"
				"łączy się przez usb z urządzeniem \n"
				"o vendorze %04x i o numerze product %04x \n"
				"\tmode = (int)\n"
				"\t\t0 - wejście z klaiwatury\n"
				"\t\t1 - mrygaj biało ciemno.\n"
				"\t\t2 - nie wiem\n"
				"\t\t3 - tez nie wiem\n"
				"\t\t4 - randomowe\n"
				"\t\t5 - do_onset(argc, argv);\n"
				"\t\t6 - do_track(argc, argv);\n"
				"\t\t7 - do_stroboskop(argc, argv);\n"
				"\t\t8 - do_fajna_zmiana - spokojnie zmienia kolory\n"
				"\n"
				"\t-h\tprint this help.\n"
				"\t-g\tdo not use gtk\n"
				"\t-u\tdo not use usb\n"
				"\t-m\tustaw jaki mod.\n"
				, VENDOR, PRODUCT );
			exit(0);
		case 'g':
			use_gtk = 0;
			break;
		case 'u':
			use_usb = 0;
			break;
		case 'm':
			mode = atoi(optarg);
			break;
		}
	}
}

int main(int argc, char **argv)
{
	
	if ( use_parse_cmd ) {
		parse_cmd(argc, argv);
	}
	
	srand (time(NULL));
	
	if ( use_usb ) {
		handle = usb_connect(ctx, VENDOR, PRODUCT);
		if ( !handle ) {
			printf(" not conected \n");
			return 0;
		}
		printf(" Connected to device !\n");
	}
	
	if ( use_gtk )
		gtk_start(argc, argv);
	
	do_fun(mode, argc, argv);
	
	handle = usb_disconnect(ctx, handle);
}
