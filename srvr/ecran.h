bool intre(int x,int a,int b,bool e){
     if(e) if(x<=b&&x>=a) return 1;
     else if(x<b&&x>a) return 1;
     return 0;
     }

void draw_players(){
     int i,j;
     j=0;
     for(i=0;i<20;i++)
     if(player[i].activ) {
         rectfill(buffer,499,195+16*j,623,195+16*(j+1),VERDE);
         line(buffer,499,195+16*j,623,195+16*(j),ROSU);
         textprintf_ex(buffer,font,510,200+16*j,ALB,BACKG,"%d %s",i,player[i].name);
        line(buffer,499,195+16*(j+1),623,195+16*(j+1),ROSU);
         j++;
     }
}   
void draw_ecran(){
     int i;
     for(i=0;i<=pozecr;i++)
     textprintf_ex(buffer,font,18,34+i*10,ALB,BACKG,"%s",ecran[i]);
}

void put_ecran(char *aux){
int i;
     if(pozecr==38){
     for(i=1;i<39;i++)
     strcpy(ecran[i-1],ecran[i]);
                   }
     else pozecr++;
     strcpy(ecran[pozecr],aux);
          
     }

void desenareecran(){
     draw_sprite(buffer,ecr,0,0);
     draw_players();
     draw_ecran();
     show_mouse(NULL);
     draw_sprite(screen,buffer,0,0);  
     show_mouse(screen);
     clear_bitmap(buffer);
     }

int Mouse()
{
     if(intre(mouse_x,500,624,1)&& (mouse_b&1))
     {
      if(intre(mouse_y,32,64,1)) return 1;
      if(intre(mouse_y,128,150,1)) return 4;                    
     }
   return 0;  
}
