bool ScrollMouse(){
     bool b;
     b=0;
    if(mouse_x<16) {//position_mouse(5,mouse_y);
                     if(map.cx!=0&&!fmouse) {b=1;
                                  map.cx--;}
                      }
     if(mouse_x>624){//position_mouse(635,mouse_y);
                     if(map.cx<(map.x-limitax)&&!fmouse) {b=1;
                                  map.cx++;}
                     }
     if(mouse_y<16) {//position_mouse(mouse_x,5);
                     if(map.cy!=0&&!fmouse) {b=1;
                                  map.cy--;}
                                  }
     if(mouse_y>464){//position_mouse(mouse_x,475);
                     if(map.cy<(map.y-limitay)&&!fmouse) {b=1;
                                  map.cy++;}}

     return b;
     }

bool MiniMouse(){
     float acx,acy;
     if(intre(mouse_x,495,625,1)&&intre(mouse_y,30,160,1)&&!fmouse){     
     if(mouse_b&1&&Click()){
     acx=map.cx;
     acy=map.cy;
     acx=-((495+(limitax*map.ratiax)/2+(acx*map.ratiax))-mouse_x);
     acy=-((30+(limitay*map.ratiay)/2+(acy*map.ratiay))-mouse_y);
     map.cx=(int)(map.cx+acx/map.ratiax);
     map.cy=(int)(map.cy+acy/map.ratiay);
     if(map.cx<0) map.cx=0;
     if(map.cy<0) map.cy=0;
     if(map.cx>=map.x-limitax) map.cx=map.x-limitax;
     if(map.cy>=map.y-limitay) map.cy=map.y-limitay;
     return 1;
     }
     if(mouse_b&2&&Click()){
       if(selectu&&u[selectu].player==player){
                   acx=(mouse_x-495)/map.ratiax;
                   acy=(mouse_y-30)/map.ratiay;
                   u[selectu].nextx=(int)acx;
                   u[selectu].nexty=(int)acy;
                   cur.locx=u[selectu].nextx;
                   cur.locy=u[selectu].nexty;
                   cur.frame=24;
       sprintf(Scom,"MOVE %s %d %d %d -1 -1",nume,selectu,u[selectu].nextx,u[selectu].nexty);
                   }            
                   }
     }
     return 0;
     }
     
     
bool MapMouse(){
int selx,sely,i;
char aux[250];
     selx=mouse_x/patrat;
     sely=mouse_y/patrat;
  if(intre(mouse_x,16,480,1)&&intre(mouse_y,32,464,1)){
   rect(buffer,selx*patrat,sely*patrat,(selx+1)*patrat,(sely+1)*patrat,ALB);
     if(mouse_b&1&&Click()){
      selectu=0;
      selectb=0;
       selectu=Unitatexy(selx+map.cx,sely+map.cy);
       selectb=Buildxy(selx+map.cx,sely+map.cy);
      if(selectu==-1)selectu=0;
      if(selectb==-1)selectb=0;

     }
     if(mouse_b&2&&Click()){
      if(selectu&&u[selectu].player==player) 
                  {int urmu,urmb;
                   urmb=Buildxy(selx+map.cx,sely+map.cy);
                   urmu=Unitatexy(selx+map.cx,sely+map.cy);
                   if(urmu==-1&&urmb==-1){u[selectu].nextx=selx+map.cx;
                               u[selectu].nexty=sely+map.cy;  }
                   else u[selectu].parcurs=0;
                   u[selectu].urmu=urmu;
                   u[selectu].urmb=urmb;

                   cur.locx=selx+map.cx;
                   cur.locy=sely+map.cy;
                   cur.frame=24;
sprintf(Scom,"MOVE %s %d %d %d %d %d",nume,selectu,u[selectu].nextx,u[selectu].nexty,urmu,urmb);
                   }
                   }
     return 1;
     }
     return 0;
     }
   
bool MenuMouse(){
     int i;
     if(selectu){
     for(i=0;i<tu[u[selectu].tip].nrcom;i++)
     if(intre(mouse_x,499,623,1)&&intre(mouse_y,256+16*i,256+16*(i+1),1)&&
     (mouse_b&1)&&u[selectu].player==player){
     Comanda(tu[u[selectu].tip].com[i],0);
     return 1;
     }
     
     }
     if(selectb) {
      for(i=0;i<tb[b[selectb].tip].nrcom;i++)
     if(intre(mouse_x,499,623,1)&&intre(mouse_y,256+16*i,256+16*(i+1),1)&&
     (mouse_b&1)&&b[selectb].player==player){
     Comanda(tb[b[selectb].tip].com[i],0);
     return 1;
     }
                 }
     return 0;
     }
bool Click(){
but1=0;return 1;


}

void Mouse(){
     bool b;
     b=(MiniMouse()||ScrollMouse()||MapMouse()||MenuMouse());                  
     if(fmouse>0)fmouse--;
     if(b) fmouse=mousescroll;
 
     }

