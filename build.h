
void build::Build(){
     int i,j;
     if(hp<=0) {activ=0;explst=72;
     juc[player].cladiri--;
     if(tip==REACTOR||tip==BAZAPRINC) juc[player].locurimax-=8;
     for(i=0;i<lx;i++)
     for(j=0;j<ly;j++)  map.obs[i+locx][j+locy]=0;   
     return;}
     if(tip==SONDA){ if(contor==cmax){ contor=0;juc[player].bani+=600;}
                      contor++;
                    }
     if(construieste){timp--;release=0;}
     if(timp==0&&construieste){int selectuaux,selectbaux;
                               if(player==::player)
                               mesaj.LoadMsg("UNITATE CREATA.",100);     
                               release=1;construieste=0;
                               selectuaux=selectu;
                               selectbaux=selectb;
                               selectb=tag;
                               Comanda(12,1);
                               selectb=selectbaux;}
     }
void build::LoadBuild(int x,int y,int ttip,int pplayer,int ttag){
     int i,j;
     locx=x;locy=y;
     player=pplayer;
     juc[player].cladiri++;
     cmax=700;
     contor=0;
     tip=ttip;
     tag=ttag;
     if(tip==REACTOR||tip==BAZAPRINC) juc[player].locurimax+=8;
     lx=tb[tip].lx;
     ly=tb[tip].ly;     
     hp=hpmax=tb[tip].hpmax;
     dmg=tb[tip].dmg;
     delay=tb[tip].delay;
     range=tb[tip].range;
     nrbit=tb[tip].nrbit;
     activ=1;
     construieste = timp = unit =0;
     for(i=0;i<lx;i++)
     for(j=0;j<ly;j++)  map.obs[i+locx][j+locy]=pplayer;             
                       
     }

void build::DrawBuild(){
     int auxx1,auxx2,auxx3,auxy1,auxy2,auxy3;
   if(intre(locx,map.cx,map.cx+limitax-lx,1)
   &&intre(locy,map.cy+1,map.cy+limitay-ly+1,1)&&activ)
     {
  /*   auxx1=(locx-map.cx)*patrat;
     auxy1=(locy-map.cy)*patrat;
     if(auxx1<=0)auxx2=0;
     else auxx2=0-auxx1;
     if(auxy1<=0) auxy2=0;
     else auxy2=0-auxy1;*/
//    blit((BITMAP*)cladiri[nrbit].dat,buffer,auxx1,auxy1,auxx2,auxy2,
//    abs(auxx2-auxx1),abs(auxy2-auxy1));
     draw_sprite(buffer,(BITMAP*)cladiri[nrbit].dat,
     (locx-map.cx)*patrat,(locy-map.cy)*patrat);   
     if(player==::player)rectfill(buffer,(locx-map.cx)*patrat,(locy-map.cy)*patrat,
             (locx-map.cx)*patrat+4,(locy-map.cy)*patrat+4,VERDEDESCHIS);
       else rectfill(buffer,(locx-map.cx)*patrat,(locy-map.cy)*patrat,
             (locx-map.cx)*patrat+4,(locy-map.cy)*patrat+4,ROSU);
     }
   if(intre(locx,map.cx,map.cx+limitax-1,1)&&intre(locy,map.cy,map.cy+limitay,1)&&explst>0) {
   stretch_sprite(buffer,(BITMAP*)expl[15-explst/6].dat,(locx-map.cx)*patrat,
   (locy-map.cy)*patrat,lx*patrat,ly*patrat);
   explst--;
}
if(explst<10&&explst!=0) activ=0;
 }

