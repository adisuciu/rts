#include <allegro.h>
#include <winalleg.h>
#include <enet.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include "jucator.h"
#include "culori.h"
#include "objdef.h"
#define patrat 32
 build b[50];
 unit u[200];
 harta map;
 BITMAP *buffer,*ecran,*minimap,*credits,*meniu;
 DATAFILE *ter,*unitdat,*curs,*cladiri,*expl,*proj,*sunete;
 bool sound;
 char comm[40][40];
 char nume[200];
 int but1;
 int player;
 int ftaste,fmouse;
 int selectu,selectb;
 int countdown;
 bool retea;
 struct cursor{ int locx,locy; int frame; }cur;

#include "tip.h"
#include "mesaj.h"
msg mesaj;
tipu tu[15];
tipb tb[15];
#include "terdat.h"
#include "unitsdat.h"
#include "map.h"

#include "build.h"
#include "units.h"


 #include "retea.h"

#include "game.h"
#include "mousef.h"

volatile long speed_counter = 0;
void increment_speed_counter(){speed_counter++;}

END_OF_FUNCTION(increment_speed_counter);

int main() {
    init();	
	int i;
    set_mouse_sprite((BITMAP*)curs[0].dat);
    meniu=load_bitmap("meniu.bmp",NULL);
    credits=load_bitmap("credits.bmp",NULL);
        show_mouse(screen);
	while(!key[KEY_ESC]){
    if(intre(mouse_x,154,448,1)&&(mouse_b&1) )
    if(intre(mouse_y,104,172,1)){key[KEY_ESC]=1;}
    else if(intre(mouse_y,183,251,1)){    draw_sprite(screen,credits,0,0);readkey();continue;}
    else if(intre(mouse_y,259,329,1)){ deinit();}
    draw_sprite(screen,meniu,0,0);

     }            
     key[KEY_ESC]=0;
     clear_bitmap(screen);
	textprintf_ex(screen,font,1,90,ALB,NEGRU,"SE INCARCA UNITATILE");
	LoadTip();	
    textprintf_ex(screen,font,1,100,ALB,NEGRU,"SE INCARCA HARTA");
	map.load_map("map1.map");
	map.fill_obs();
	
	minimap=create_bitmap(map.x,map.y);
    initnet();


    if(retea) {textprintf_ex(screen,font,1,150,ALB,NEGRU,
            "ASTEPTAM SERVERUL SA PORNEASCA JOCUL");
              WaitForStart();}
    else{textprintf_ex(screen,font,1,150,ALB,NEGRU,
            "APASA ORICE TASTA PENTRU A INTRA IN JOC");
            LoadUnitsfromfile("map1.obj",1);
            player=1;
    
     readkey();
     }
     
     char aux[10];
      for(int i=0;i<20;i++){
       sprintf(aux,"%d",i);
       juc[i].Initjuc(aux,10000,0,0,0,i);}
       juc[player].Initjuc(nume,2000,0,0,1,player);
    while(!key[KEY_ESC]){
    
    map.draw_map();
//    while(speed_counter>0){
    Taste();
    Mouse();
    if(retea){Retea();}
  //  speed_counter--;
   // }
    for(i=0;i<200;i++){
                       if(u[i].activ){ u[i].MoveUnit();
                                       }
                                       u[i].DrawUnit();
                       }
    for(i=0;i<50;i++){
                      if(b[i].activ){ b[i].Build();
                                      }
                                      b[i].DrawBuild();
                      }
    countdown++;
    DrawSelect();
    mesaj.DrawMsg();
    vsync();
    for(i=0;i<20;i++){
        if((juc[i].locuri+juc[i].cladiri<0) && juc[i].tag==player) 
        {allegro_message("Ai pierdut"); 
        key[KEY_ESC]=1; }
                      }
    Desenare();
}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
// atexit(deinit);
	set_color_depth(16);
	install_keyboard();
	set_keyboard_rate(0, 0);
	set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
	set_display_switch_mode(SWITCH_BACKGROUND);
    textprintf_ex(screen,font,1,1,ALB,NEGRU,"INITIALARE MODUL GRAFIC");	
	textprintf_ex(screen,font,200,1,VERDEDESCHIS,NEGRU,"... INCARCAT");
	install_timer();
    
    textprintf_ex(screen,font,1,10,ALB,NEGRU,"INCARCARE MOUSE");	
	install_mouse();
    textprintf_ex(screen,font,200,10,VERDEDESCHIS,NEGRU,"... INCARCAT");
    
    textprintf_ex(screen,font,1,20,ALB,NEGRU,"INITIALIZARE SUNET");	
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
//      allegro_message("Eroare la incarcarea sunetului\n%s\n", allegro_error);
         sound=0;
          textprintf_ex(screen,font,200,20,ROSU,NEGRU,"... EROARE");
   }
    else{ textprintf_ex(screen,font,200,20,VERDEDESCHIS,NEGRU,"... INCARCAT");   
    sound=1;
    sunete=load_datafile("sunet.dat");
}
    
	LOCK_VARIABLE(speed_counter);
    LOCK_FUNCTION(increment_speed_counter);
	install_int_ex(increment_speed_counter, BPS_TO_TIMER(100));
	
    textprintf_ex(screen,font,1,30,ALB,NEGRU,"CREARE BUFFER VIDEO");
	buffer=create_bitmap(640,480);
    if(buffer)textprintf_ex(screen,font,200,30,VERDEDESCHIS,NEGRU,"... INCARCAT");
    else textprintf_ex(screen,font,200,30,ROSU,NEGRU,"... EROARE");
    
    textprintf_ex(screen,font,1,40,ALB,NEGRU,"INCARCARE TER.DAT");
	ter=load_datafile("ter.dat");
    if(ter)textprintf_ex(screen,font,200,40,VERDEDESCHIS,NEGRU,"... INCARCAT");
    else textprintf_ex(screen,font,200,40,ROSU,NEGRU,"... EROARE");
    
    textprintf_ex(screen,font,1,50,ALB,NEGRU,"INCARCARE UNITS.DAT");
	unitdat=load_datafile("units.dat");
	if(unitdat)textprintf_ex(screen,font,200,50,VERDEDESCHIS,NEGRU,"... INCARCAT");
	else textprintf_ex(screen,font,200,50,ROSU,NEGRU,"... EROARE");
	
	expl=load_datafile("expl.dat");
	proj=load_datafile("proj.dat");
	textprintf_ex(screen,font,1,60,ALB,NEGRU,"INCARCARE CUR.DAT ");
	curs=load_datafile("cur.dat");
	if(curs)textprintf_ex(screen,font,200,60,VERDEDESCHIS,NEGRU,"... INCARCAT");
	else textprintf_ex(screen,font,200,60,ROSU,NEGRU,"... EROARE");
	
    textprintf_ex(screen,font,1,70,ALB,NEGRU,"INCARCARE CLADIRI.DAT ");
	cladiri=load_datafile("build.dat");
	if(cladiri) textprintf_ex(screen,font,200,70,VERDEDESCHIS,NEGRU,"... INCARCAT");
	else textprintf_ex(screen,font,200,70,ROSU,NEGRU,"... EROARE");

	textprintf_ex(screen,font,1,80,ALB,NEGRU,"INCARCARE ECRAN ");
	ecran=load_bitmap("ecran.bmp",NULL);
	if(ecran)textprintf_ex(screen,font,200,80,VERDEDESCHIS,NEGRU,"... INCARCAT");
	else textprintf_ex(screen,font,200,80,ROSU,NEGRU,"... EROARE");



}

void deinit() {
	clear_keybuf();
	char aux[250];
    sprintf(aux,"DISC %s",nume);
    if(retea)SendServ(aux);
	destroy_bitmap(buffer);
	destroy_bitmap(ecran);
	destroy_bitmap(minimap);
	enet_deinitialize();
	exit(0);

}
