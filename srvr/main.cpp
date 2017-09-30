#include <allegro.h>
#include <winalleg.h>
#include <enet.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include "culori.h"
    ENetAddress address;
    ENetHost * server;
    ENetEvent event;
bool start=0;
int nrplayers;
int sync[25];
int syncb;
int status;
int countd=10;
struct {
       char name[50];
       ENetPeer *peer;       
       int chann;
       bool activ;
       }player[20];
BITMAP *ecr,*buffer;     
char ecran[60][40];
char comm[250][20];
int pozecr;  
#include "player.h"
#include "ecran.h"
#include "net.h"

void init();
void deinit();

int main() {

	init();
	put_ecran("Program pornit .. asteptati init ..");
	desenareecran();
	InitServer();
	status=0;
    while (status!=4) {
    Ciclu();
    if(countd==0){countd=10;}
    else countd--;
    status=Mouse();
	if(countd==10)desenareecran();
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	allegro_init();
	set_color_depth(16);
	install_keyboard();
	set_keyboard_rate(0, 0);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	set_display_switch_mode(SWITCH_BACKGROUND);
install_timer();
install_mouse();
select_mouse_cursor(MOUSE_CURSOR_ARROW);
buffer=create_bitmap(640,480);
ecr=load_bitmap("ecran.bmp",NULL);
enet_initialize();

}

void deinit() {
    destroy_bitmap(buffer);
	clear_keybuf();
    enet_deinitialize();
	/* add other deinitializations here */
}
