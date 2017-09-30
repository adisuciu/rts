
void unit::LoadUnit(int x,int y,int ttip,int pplayer){
     locx=nextx=destx=x;
     locy=nexty=desty=y;
     player=pplayer;
     urmu = -1;
     urmb = -1;
     map.obs[locx][locy]=player;
     juc[player].unitati++;
     explst=0;
     tip=ttip;
     speed=tu[tip].speed;
     cmax=tu[tip].cmax;c1=cmax;
     atimg=tu[tip].atimg;
     repaus=1;activ=1;
     unghi=0;frame=0;parcurs=0;
     nrbit1=tu[tip].nrbit1;
     nrbit2=tu[tip].nrbit2;
     hp=hpmax=tu[tip].hpmax;
     dmg=tu[tip].dmg;
     delay=tu[tip].delay;
     del=delay;
     range=tu[tip].range;

     }
void unit::SetareParcurs(int &auxx,int &auxy){
      if(unghi==0){auxy=+parcurs;}
      if(unghi==1){auxy=+parcurs;auxx=-parcurs;}
      if(unghi==2){auxx=-parcurs;}
      if(unghi==3){auxx=-parcurs;auxy=-parcurs;}
      if(unghi==4){auxy=-parcurs;}
      if(unghi==5){auxx=+parcurs;auxy=-parcurs;}
      if(unghi==6){auxx=+parcurs;}
      if(unghi==7){auxx=+parcurs;auxy=+parcurs;}
     
     }
void unit::DrawProj(){
     if(urmu!=-1){
                  rotate_sprite(buffer,(BITMAP*)proj[tip].dat,
                  ((locx-map.cx)-(float)(locx-u[urmu].locx)/(float)atacimg)*patrat,
                  ((locy-map.cy)-(float)(locy-u[urmu].locy)/(float)atacimg)*patrat,                  
                  itofix(unghi*32));
                  }
     if(urmb!=-1){
                  rotate_sprite(buffer,(BITMAP*)proj[tip].dat,
                  ((locx-map.cx)-(float)(locx-b[urmb].locx-b[urmb].lx/2)/(float)atacimg)*patrat,
                  ((locy-map.cy)-(float)(locy-b[urmb].locy-b[urmb].ly/2)/(float)atacimg)*patrat,
                  itofix(unghi*32));
                  }
     }
void unit::DrawUnit(){
   int auxx,auxy;
   auxx=auxy=0;
   if(intre(locx,map.cx,map.cx+limitax-1,1)&&intre(locy,map.cy,map.cy+limitay,1)&&activ)
     {
      SetareParcurs(auxx,auxy);      
      auxx=-auxx+(locx-map.cx)*patrat;
      auxy=-auxy+(locy-map.cy)*patrat;
if(atacimg) {rotate_sprite(buffer,(BITMAP*)unitdat[atimg].dat,auxx,auxy,itofix(unghi*32));
            DrawProj();
             atacimg--;}
else   {rotate_sprite(buffer,(BITMAP*)unitdat[nrbit1+frame/2].dat,auxx,auxy,
       itofix(unghi*32));
       if(player==::player)rectfill(buffer,auxx,auxy,auxx+4,auxy+4,VERDEDESCHIS);
       else rectfill(buffer,auxx,auxy,auxx+4,auxy+4, ROSU);
       }
   }
if(intre(locx,map.cx,map.cx+limitax-1,1)&&intre(locy,map.cy,map.cy+limitay,1)&&explst>0) {
   draw_sprite(buffer,(BITMAP*)expl[15-explst/6].dat,(locx-map.cx)*patrat,(locy-map.cy)*patrat);
explst--;
}
//if(explst<10&&explst!=0) activ=0;
 }
void unit::SetareUnghi(int auxx,int auxy){if(auxx==0&&auxy<0){unghi=4;}
                         if(auxx>0&&auxy<0) {unghi=5;}
                         if(auxx>0&&auxy==0){unghi=6;}
                         if(auxx>0&&auxy>0) {unghi=7;}
                         if(auxx==0&&auxy>0){unghi=0;}
                         if(auxx<0&&auxy>0) {unghi=1;}
                         if(auxx<0&&auxy==0){unghi=2;}
                         if(auxx<0&&auxy<0) {unghi=3;}
     
     }
void unit::SetareLoc(){ int auxx,auxy;
                        auxx=locx;auxy=locy;
                         if(!repaus){
                         if(unghi==0) {locy--; } 
                         if(unghi==1) {locy--;locx++; } 
                         if(unghi==2) {locx++; } 
                         if(unghi==3) {locy++;locx++; } 
                         if(unghi==4) {locy++; } 
                         if(unghi==5) {locy++;locx--; } 
                         if(unghi==6) {locx--; } 
                         if(unghi==7) {locy--;locx--; } 
                         if(map.obs[locx][locy]) {locx=destx=nextx=auxx;
                                                  locy=desty=nexty=auxy;  }
                         else {map.obs[auxx][auxy]=0;map.obs[locx][locy]=player;
                         parcurs=-speed;
                         }
                         }
     
     }
bool unit::VerifUrm(){int auxx,auxy,ex,ey;
                      
                      auxx=locx;auxy=locy;
                      ex=locx;ey=locy;
                         if(unghi==0) {auxy--; } 
                         if(unghi==1) {auxy--;auxx++; } 
                         if(unghi==2) {auxx++; } 
                         if(unghi==3) {auxy++;auxx++; } 
                         if(unghi==4) {auxy++; } 
                         if(unghi==5) {auxy++;auxx--; } 
                         if(unghi==6) {auxx--; } 
                         if(unghi==7) {auxy--;auxx--; }    
                         if(map.obs[auxx][auxy]) {locx=destx=nextx=ex;
                                                  locy=desty=nexty=ey; return 0; }
return 1;

                         
     
     }

void unit::Atac(int urm,bool bol){
     if(bol==0){
    
     if(abs(locx-u[urm].locx)<=range&&abs(locy-u[urm].locy)<=range&&u[urm].activ&&repaus) {
     SetareUnghi(locx-u[urm].locx,locy-u[urm].locy);
     if(del>0){del--;
               if(u[urmu].hp<=0) urmu=-1;
               nextx=destx=locx;nexty=desty=locy;}
     if(del==0&&urmu!=-1){
     u[urm].hp=u[urm].hp-dmg;
     if(u[urmu].hp<=0) {urmu=-1;nextx=destx=locx;nexty=desty=locy;}
     atacimg=8;
     del=delay;} 
     }
  else { nextx=locx;nexty=locy;}    
     }
     else 
     if(abs(locx-b[urm].locx)<=range&&abs(locy-b[urm].locy)<=range&&b[urm].activ&&repaus) {
     SetareUnghi(locx-b[urm].locx,locy-b[urm].locy);
     if(del>0){del--;nextx=destx=locx;nexty=desty=locy;
     if(b[urmb].hp<=0) urmb=-1;
     }
     if(del==0&&urmb!=-1){
     b[urm].hp=b[urm].hp-dmg;
     if(b[urmb].hp<=0) {urmb=-1;nextx=destx=locx;nexty=desty=locy;}
     atacimg=8;
     del=delay;}
 
     }
      else { nextx=locx;nexty=locy;}    
     }
     

void unit::MoveUnit(){
int auxx,auxy;
if(hp<=0) {juc[player].unitati--;;activ=0;explst=90;map.obs[locx][locy]=0;return;}

     if(c1<=0) c1=cmax;
     else {c1--;return;}
     
     if(parcurs==0) {repaus=1;destx=nextx;desty=nexty;}
     if(urmu!=-1) {if(u[urmu].activ){destx=u[urmu].locx;desty=u[urmu].locy;}} 
     if(urmb!=-1) {if(b[urmb].activ){destx=b[urmb].locx;desty=b[urmb].locy;}}
     if(u[urmu].player!=player&&urmu!=-1) {Atac(urmu,0);}
     if(b[urmb].player!=player&&urmb!=-1) Atac(urmb,1);
     if(locx==destx&&locy==desty){ repaus=1;return;}
     auxx=locx-destx;
     auxy=locy-desty;
     if(repaus){SetareUnghi(auxx,auxy);if(!VerifUrm()) {parcurs=-speed;}
                 repaus=0;}
     if(parcurs>=patrat){parcurs=-speed;
                         SetareLoc();
                         auxx=locx-destx;
                         auxy=locy-desty;
                         SetareUnghi(auxx,auxy);
                         }
     
     if(frame==(nrbit2-nrbit1)*2) frame=0;
     else frame++;
     parcurs+=speed;
     
     
     }
//void Comanda(int item,int selectu,int selectb);

