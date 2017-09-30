void AfisCursor();
bool Click();
void Termometru(int x,int y, int lx, int ly,float aux){
     int cul;
     rect(buffer,x,y,lx+x,ly+y,ALB);
     cul=makecol((int)(float)(255*(1-aux)),(int)(float)(255*aux),0);
     rectfill(buffer,x+1,y+1,(int)((float)aux*lx+x-1),ly+y-1,cul);
     textprintf_ex(buffer,font,lx/2+x-8,ly-8+y,ALB,BACKG,"%.0f ",aux*100);

     }
void LoadTip(){
     FILE *in;
     int nru,nrb,i,j,nrc;
     in=fopen("tipuri.in","r");
     if(!in){textprintf_ex(screen,font,200,90,ROSU,NEGRU,"... EROARE");return;}
     fscanf(in,"%d %d",&nru,&nrb);
     for(i=0;i<nru;i++){fscanf(in,"%s",&tu[i].nume);
          fscanf(in,"%d %d",&tu[i].cmax,&tu[i].speed);
          fscanf(in,"%d %d %d",&tu[i].nrbit1,&tu[i].nrbit2,&tu[i].atimg);
          fscanf(in,"%d %d",&tu[i].timp,&tu[i].cost);
          fscanf(in,"%d %d %d %d",&tu[i].hpmax,&tu[i].dmg,&tu[i].delay,&tu[i].range);
          fscanf(in,"%d",&tu[i].nrcom);
                        for(j=0;j<tu[i].nrcom;j++){
                                           fscanf(in,"%d",&tu[i].com[j]);
                                           }
                        }
     for(i=0;i<nrb;i++){fscanf(in,"%s",&tb[i].nume);
         fscanf(in,"%d %d %d",&tb[i].nrbit,&tb[i].lx,&tb[i].ly);
         fscanf(in,"%d %d %d %d",&tb[i].hpmax,&tb[i].dmg,&tb[i].delay,&tb[i].range);
         fscanf(in,"%d",&tb[i].nrcom);
                       for(j=0;j<tb[i].nrcom;j++){
                                           fscanf(in,"%d",&tb[i].com[j]);
                                           }
                        }
     fclose(in);
      in=fopen("comenzi.in","r");
      if(!in){textprintf_ex(screen,font,200,90,ROSU,NEGRU,"... EROARE");return;}
      fscanf(in,"%d",&nrc);
      for(i=0;i<nrc;i++){
       fscanf(in,"%d",&j);
       fscanf(in,"%s",&comm[j]);
       }
      textprintf_ex(screen,font,200,90,VERDEDESCHIS,NEGRU,"... INCARCAT");
      fclose(in);
     }

void Taste(){
     bool b;
     if(key[KEY_UP]) if(map.cy!=0&&!ftaste)     
                     {map.cy--;b=1;}
     if(key[KEY_DOWN]) if(map.cy<(map.y-limitay)&&!ftaste) 
                       {map.cy++;b=1;}
     if(key[KEY_LEFT]) if(map.cx!=0&&!ftaste)   {map.cx--;b=1;}
     if(key[KEY_RIGHT]) if(map.cx<(map.x-limitax)&&!ftaste) {map.cx++;b=1;}
     if(ftaste>0)ftaste--;
     if(b) ftaste=keyscroll;
     clear_keybuf();
     }


int Unitatexy(int selx,int sely){
int i;
               for(i=1;i<200;i++)
               if((u[i].locx==selx)&&(u[i].locy==sely)&&u[i].activ)
               { return i;}  
return -1;
}

int Buildxy(int selx,int sely){
int i;
               for(i=1;i<50;i++)
               if(intre(selx,b[i].locx,b[i].locx+b[i].lx-1,1)&&
                  intre(sely,b[i].locy,b[i].locy+b[i].ly-1,1)&&b[i].activ)
                  return i;
return -1;      
    
}

void SetLoc(int &locx,int &locy, int unghi){
                         if(unghi==0) {locy--; } 
                         if(unghi==1) {locy--;locx++; } 
                         if(unghi==2) {locx++; } 
                         if(unghi==3) {locy++;locx++; } 
                         if(unghi==4) {locy++; } 
                         if(unghi==5) {locy++;locx--; } 
                         if(unghi==6) {locx--; } 
                         if(unghi==7) {locy--;locx--; }
     }
bool NewUnit(){
     int i,j,auxx,auxy,locx,locy,lx,ly;
     auxx=auxy=0;
     locx=b[selectb].locx;
     locy=b[selectb].locy;
     lx=b[selectb].lx;
     ly=b[selectb].ly;     

     for(i=-1;i<=ly;i++)
     if(!map.obs[locx-1][i+locy]){ auxx=locx-1;auxy=i+locy;break;} 
     if(auxx==auxy&&auxx==0)
     for(i=-1;i<=lx;i++)
     if(!map.obs[i+locx][locy-1]){ auxx=i+locx;auxy=locy-1;break;} 
     if(auxx==auxy&&auxx==0)
     for(i=-1;i<=ly;i++)
     if(!map.obs[locx+lx][i+locy]){ auxx=locx+lx;auxy=i+locy;break;} 
     
     if(auxx==auxy&&auxx==0)
     for(i=-1;i<=lx;i++)                         
     if(!map.obs[i+locx][locy+ly]){ auxx=i+locx;auxy=locy+ly;break;} 
     if(auxx==auxy&&auxx==0)
     {mesaj.LoadMsg("NU EXISTA DESTUL LOC PENTRU LANSAREA UNITATE",100);return 1;}     
//     textprintf_ex(buffer,font,530,356,ALB,BACKG,"%d",but1);
     for(i=2;i<200;i++){
  if(!u[i].activ) {u[i].LoadUnit(auxx,auxy,b[selectb].unit,b[selectb].player);
  if(sound&&b[selectb].player==player) play_sample((SAMPLE*)sunete[0].dat,255,128,1000,0);
  return 0;}}
     
     
}

bool NewBuilding(int tip){
     int locx,locy,lx,ly,i,j;
          locx=u[selectu].locx;
          locy=u[selectu].locy;
          lx=tb[tip].lx;
          ly=tb[tip].ly;
                        
       for(i=0;i<lx;i++)
       for(j=0;j<ly;j++){
       if(i==0&&j==0) continue;
       if(map.obs[i+locx][j+locy]) {
       if(u[selectu].player==player)
       mesaj.LoadMsg("NU ESTE DESTUL LOC PENTRU A DESFASURA CLADIREA",100); 
       return 1;}}
       for(i=2;i<50;i++){
       if(!b[i].activ){b[i].LoadBuild(locx,locy,tip,u[selectu].player,i);
       u[selectu].activ=0;
       juc[u[selectu].player].unitati--;
       selectu=0;
       selectb=i; break;}
       }
       if(b[selectb].player==player){
       mesaj.LoadMsg("CLADIRE CONSTRUITA CU SUCCES",100);
       if(sound) play_sample((SAMPLE*)sunete[1].dat,255,128,1000,0);
       }
       return 0;       
     }

void Comanda(int item,bool primit){
     int auxx,auxy,aux;
     char messret[250];
     bool b1;
     int i,j;
/*STAI*/     if(item==2) {             
                  auxx=u[selectu].locx;
                  auxy=u[selectu].locy;
                  aux=u[selectu].unghi;
                  if(u[selectu].parcurs)SetLoc(auxx,auxy,aux);
                  u[selectu].nextx=auxx;
                  u[selectu].nexty=auxy;
                  if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                  }
/*BULLP*/     if(item==11) {if(!b[selectb].construieste&&!b[selectb].release){
                if(juc[b[selectb].player].bani>0){
                   b[selectb].construieste=1;
                   b[selectb].unit=BULLP;
                   b[selectb].timp=tu[BULLP].timp;
             if(!primit)juc[b[selectb].player].bani=juc[b[selectb].player].bani-tu[BULLP].cost;
                   if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                   } 
                   else mesaj.LoadMsg("NU AI DESTUL TITEI",100);
                   }
                   }

/*BULLF*/     if(item==14) {if(!b[selectb].construieste&&!b[selectb].release){
                              if(juc[b[selectb].player].bani>0){
                   b[selectb].construieste=1;
                   b[selectb].unit=BULLFA;
                   b[selectb].timp=tu[BULLFA].timp;
            if(!primit)juc[b[selectb].player].bani=juc[b[selectb].player].bani-tu[BULLFA].cost;
                   if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                   } 
                   else mesaj.LoadMsg("NU AI DESTUL TITEI",100);
                   }}

/*BULLL*/     if(item==15) {if(!b[selectb].construieste&&!b[selectb].release){
                              if(juc[b[selectb].player].bani>0){
                   b[selectb].construieste=1;
                   b[selectb].unit=BULLFT;
                   b[selectb].timp=tu[BULLFT].timp;
            if(!primit)juc[b[selectb].player].bani=juc[b[selectb].player].bani-tu[BULLFT].cost;
                   if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                   } 
                   else mesaj.LoadMsg("NU AI DESTUL TITEI",100);
                   }}
 
/*REACTOR*/     if(item==16) {if(!b[selectb].construieste&&!b[selectb].release){
                                if(juc[b[selectb].player].bani>0){
                   b[selectb].construieste=1;
                   b[selectb].unit=BULLR;
                   b[selectb].timp=tu[BULLR].timp;
  if(!primit)     juc[b[selectb].player].bani=juc[b[selectb].player].bani-tu[BULLR].cost;
                   if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                   } 
                   else mesaj.LoadMsg("NU AI DESTUL TITEI",100);
                   }}

/*SONDA*/     if(item==17) {if(!b[selectb].construieste&&!b[selectb].release){
                              if(juc[b[selectb].player].bani>0){
                   b[selectb].construieste=1;
                   b[selectb].unit=BULLS;
                   b[selectb].timp=tu[BULLS].timp;
if(!primit)        juc[b[selectb].player].bani=juc[b[selectb].player].bani-tu[BULLS].cost;
                   if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                   } 
                   else mesaj.LoadMsg("NU AI DESTUL TITEI",100);
                   }}
/*LASER*/     if(item==19) {if(!b[selectb].construieste&&!b[selectb].release){
                   if(juc[b[selectb].player].locurimax>juc[b[selectb].player].unitati
                   +3*juc[b[selectb].player].cladiri){
                   if(juc[b[selectb].player].bani>0){
                   b[selectb].construieste=1;
                   b[selectb].unit=LASER;
                   b[selectb].timp=tu[LASER].timp;
if(!primit)        juc[b[selectb].player].bani=juc[b[selectb].player].bani-tu[LASER].cost;
                   if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                   } 
                   else mesaj.LoadMsg("NU AI DESTUL TITEI",100);
                   }
              else mesaj.LoadMsg("NU AI DESTULA PUTERE. CONSTRUIESTE MAI MULTE REACTOARE",100);
                   }}
/*PW*/     if(item==20) {if(!b[selectb].construieste&&!b[selectb].release){
                   if(juc[b[selectb].player].locurimax>juc[b[selectb].player].unitati
                   +3*juc[b[selectb].player].cladiri){
                   if(juc[b[selectb].player].bani>0){
                   b[selectb].construieste=1;
                   b[selectb].unit=PW;
                   b[selectb].timp=tu[PW].timp;
if(!primit)        juc[b[selectb].player].bani=juc[b[selectb].player].bani-tu[PW].cost;
                   if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                   } 
                   else mesaj.LoadMsg("NU AI DESTUL TITEI",100);
                   }
              else mesaj.LoadMsg("NU AI DESTULA PUTERE. CONSTRUIESTE MAI MULTE REACTOARE",100);
                   }}
/*RACHETE*/     if(item==21) {if(!b[selectb].construieste&&!b[selectb].release){
                   if(juc[b[selectb].player].locurimax>juc[b[selectb].player].unitati
                   +3*juc[b[selectb].player].cladiri
                   ){
                   if(juc[b[selectb].player].bani>0){
                   b[selectb].construieste=1;
                   b[selectb].unit=RACHETE;
                   b[selectb].timp=tu[RACHETE].timp;
if(!primit)        juc[b[selectb].player].bani=juc[b[selectb].player].bani-tu[RACHETE].cost;
                   if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                   } 
              else mesaj.LoadMsg("NU AI DESTUL TITEI",100);     
                   }
              else mesaj.LoadMsg("NU AI DESTULA PUTERE. CONSTRUIESTE MAI MULTE REACTOARE",100);
                   }}

/*TAB*/     if(item==22) {if(!b[selectb].construieste&&!b[selectb].release){
                   if(juc[b[selectb].player].locurimax>juc[b[selectb].player].unitati
                   +3*juc[b[selectb].player].cladiri
                   ){
                   if(juc[b[selectb].player].bani>0){
                   b[selectb].construieste=1;
                   b[selectb].unit=TAB;
                   b[selectb].timp=tu[TAB].timp;
if(!primit)        juc[b[selectb].player].bani=juc[b[selectb].player].bani-tu[TAB].cost;
                   if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                   } 
             else mesaj.LoadMsg("NU AI DESTUL TITEI",100);
                   }
              else mesaj.LoadMsg("NU AI DESTULA PUTERE. CONSTRUIESTE MAI MULTE REACTOARE",100);
                   }}
/*TANK*/     if(item==23) {if(!b[selectb].construieste&&!b[selectb].release){
                   if(juc[b[selectb].player].locurimax>juc[b[selectb].player].unitati
                   +3*juc[b[selectb].player].cladiri
                   ){
                   if(juc[b[selectb].player].bani>0){
                   b[selectb].construieste=1;
                   b[selectb].unit=TANK;
                   b[selectb].timp=tu[TANK].timp;
if(!primit)        juc[b[selectb].player].bani=juc[b[selectb].player].bani-tu[TANK].cost;
                   if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                   } 
                   else mesaj.LoadMsg("NU AI DESTUL TITEI",100);
                   }
              else mesaj.LoadMsg("NU AI DESTULA PUTERE. CONSTRUIESTE MAI MULTE REACTOARE",100);
                   }}
                   
/*RELEASE*/  if(item==12) {if(b[selectb].release){b[selectb].release=NewUnit();
             if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);
                                                     }}
/*CANCEL*/   if(item==13) {
             if(b[selectb].construieste||b[selectb].release){
if(!primit)  juc[b[selectb].player].bani=juc[b[selectb].player].bani+tu[b[selectb].unit].cost;
             b[selectb].construieste=0;b[selectb].release=0;
             if(!primit)sprintf(Scom,"COMM %s %d %d %d",nume,item,selectu,selectb);}}
/*COMM*/    if(item==30) { 
              b1=0;
              for(i=0;i<tb[BAZAPRINC].lx;i++)
              for(j=0;j<tb[BAZAPRINC].ly;j++)  
              if(map.map[i+u[selectu].locx][j+u[selectu].locy]==27) b1=1;             
                         if(!b1){ 
                         sprintf(Scom,"BUILDB %s %d %d %d %d",nume,selectu,BAZAPRINC,u[selectu].locx,u[selectu].locy);
                         NewBuilding(BAZAPRINC);
                             }
                          else
                          mesaj.LoadMsg("NU POT CONSRUI CLADIRE PESTE TITEI",100);
                          }
                  
/*FABRICA*/ if(item==31) {              b1=0;
 if(juc[u[selectu].player].locurimax>(juc[u[selectu].player].unitati
                   +3*juc[u[selectu].player].cladiri)){
              for(i=0;i<tb[FABRICA].lx;i++)
              for(j=0;j<tb[FABRICA].ly;j++)  
              if(map.map[i+u[selectu].locx][j+u[selectu].locy]==27) b1=1;             

                         if(!b1){ 
                          sprintf(Scom,"BUILDB %s %d %d %d %d",nume,selectu,FABRICA,u[selectu].locx,u[selectu].locy);
                          NewBuilding(FABRICA);
                             }
                          else
                          mesaj.LoadMsg("NU POT CONSRUI CLADIRE PESTE TITEI",100);
                          }
else mesaj.LoadMsg("NU AI DESTULA PUTERE. CONSTRUIESTE MAI MULTE REACTOARE",100);
}
/*LAB*/ if(item==32) {
                      b1=0;
 if(juc[u[selectu].player].locurimax>(juc[u[selectu].player].unitati
                   +3*juc[u[selectu].player].cladiri)){
              for(i=0;i<tb[LAB].lx;i++)
              for(j=0;j<tb[LAB].ly;j++)  
              if(map.map[i+u[selectu].locx][j+u[selectu].locy]==27) b1=1;             

                      if(!b1){ 
                     sprintf(Scom,"BUILDB %s %d %d %d %d",nume,selectu,LAB,u[selectu].locx,u[selectu].locy);
                            NewBuilding(LAB);
                             }
                          else
                          mesaj.LoadMsg("NU POT CONSRUI CLADIRE PESTE TITEI",100);
                          }
else mesaj.LoadMsg("NU AI DESTULA PUTERE. CONSTRUIESTE MAI MULTE REACTOARE",100);
}
/*REACTOR*/ if(item==33) {
                          b1=0;
              for(i=0;i<tb[REACTOR].lx;i++)
              for(j=0;j<tb[REACTOR].ly;j++)  
              if(map.map[i+u[selectu].locx][j+u[selectu].locy]==27) b1=1;             

                         if(!b1){
                           sprintf(Scom,"BUILDB %s %d %d %d %d",nume,selectu,REACTOR,u[selectu].locx,u[selectu].locy);
                            NewBuilding(REACTOR);
                             }
                          else
                          mesaj.LoadMsg("NU POT CONSRUI CLADIRE PESTE TITEI",100);
                          }
/*SONDA*/ if(item==34) { 
 if(juc[u[selectu].player].locurimax>(juc[u[selectu].player].unitati
                   +3*juc[u[selectu].player].cladiri)){
                        b1=0;
              for(i=0;i<tb[SONDA].lx;i++)
              for(j=0;j<tb[SONDA].ly;j++)  
              if(map.map[i+u[selectu].locx][j+u[selectu].locy]==27) b1=1;             

                       if(b1){
                       sprintf(Scom,"BUILDB %s %d %d %d %d",nume,selectu,SONDA,u[selectu].locx,u[selectu].locy);
                            NewBuilding(SONDA);
                            }
                       else mesaj.LoadMsg("NU EXISTA TITEI SUB SONDA",100);
                             }
       else mesaj.LoadMsg("NU AI DESTULA PUTERE. CONSTRUIESTE MAI MULTE REACTOARE",100);
                             }



     }
void Desenare(){
    AfisCursor(); 
/*    textprintf_ex(buffer, font, 360, 430,ALB,BACKG, 
    "%d %d %d %d" ,mouse_x,mouse_y,selectu,selectb);
    textprintf_ex(buffer,font,300,400,ALB,BACKG,
    "%d %d ",u[3].locx-map.cx,u[3].locy-map.cy);*/
    draw_sprite(buffer,ecran,0,0);
    textprintf_ex(buffer,font,10,10,ALB,BACKG,"NUME:  %s",juc[player].nume); 
    if(juc[player].bani<100)
    textprintf_ex(buffer,font,180,10,ROSU,BACKG,"TITEI: %d tone",juc[player].bani);
    else if(juc[player].bani<1000)
    textprintf_ex(buffer,font,180,10,ALB,BACKG,"TITEI: %d tone",juc[player].bani);
    else 
    textprintf_ex(buffer,font,180,10,VERDEDESCHIS,BACKG,"TITEI: %d tone",juc[player].bani);
    if(juc[player].locurimax-juc[player].unitati-3*juc[player].cladiri<2)
    textprintf_ex(buffer,font,440,10,ROSU,BACKG,"PUTERE %d / %d MW "
    ,juc[player].unitati+3*juc[player].cladiri,juc[player].locurimax);
    else
    if(juc[player].locurimax-juc[player].unitati-3*juc[player].cladiri<4)
    textprintf_ex(buffer,font,440,10,ALB,BACKG,"PUTERE %d / %d MW "
    ,juc[player].unitati+3*juc[player].cladiri,juc[player].locurimax);
    else 
    textprintf_ex(buffer,font,440,10,VERDEDESCHIS,BACKG,"PUTERE %d / %d MW "
    ,juc[player].unitati+3*juc[player].cladiri,juc[player].locurimax);
    show_mouse(buffer);
    draw_sprite(screen,buffer,0,0); 
    show_mouse(NULL);
    clear_bitmap(buffer);
    }  

void DrawMenu(){
     int i;
     float aux;
   if(selectu){
   textprintf_ex(buffer,font,505,210,ALB,BACKG,"%s",tu[u[selectu].tip].nume);
   rectfill(buffer,580,195,620,235,ALB);
   rotate_sprite(buffer,(BITMAP*)unitdat[u[selectu].nrbit1+u[selectu].frame/2].dat,
   586,200,itofix(u[selectu].unghi*32));
   Termometru(510,240,100,10,(float)u[selectu].hp/(float)u[selectu].hpmax);
//     Termometru(510,250,100,10,u[u[selectu].urmu].hp/u[u[selectu].urmu].hpmax);
     // TERMOMETRU CU HP;
     if(u[selectu].player==player){
     for(i=0;i<tu[u[selectu].tip].nrcom;i++){
     rectfill(buffer,499,256+16*i,623,256+16*(i+1),VERDE);
     line(buffer,499,256+16*i,623,256+16*(i),ROSU);
     textprintf_ex(buffer,font,510,260+16*i,ALB,BACKG,"%s",
     comm[tu[u[selectu].tip].com[i]]);
     line(buffer,499,256+16*(i+1),623,256+16*(i+1),ROSU);
     }
     }
     }


     if(selectb){
     textprintf_ex(buffer,font,510,210,ALB,BACKG,"%s",tb[b[selectb].tip].nume);       
     Termometru(510,240,100,10,(float)b[selectb].hp/(float)b[selectb].hpmax);
     // TERMOMETRU CU HP;
     if(b[selectb].player==player){
     for(i=0;i<tb[b[selectb].tip].nrcom;i++){
     rectfill(buffer,499,256+16*i,623,256+16*(i+1),VERDE);
     line(buffer,499,256+16*i,623,256+16*(i),ROSU);
     if(!(b[selectb].release||b[selectb].construieste)&&
     (tb[b[selectb].tip].com[i]==12||tb[b[selectb].tip].com[i]==13)){
          textprintf_ex(buffer,font,510,260+16*i,GRIINCHIS,BACKG,"%s",
          comm[tb[b[selectb].tip].com[i]]);     
          }
          

     else                                                  
                                                                    
     if(b[selectb].release&&tb[b[selectb].tip].com[i]==12)
     textprintf_ex(buffer,font,510,260+16*i,ALB,BACKG,"%s",
     comm[tb[b[selectb].tip].com[i]]);     
     else 
   if((b[selectb].construieste||b[selectb].release)&&tb[b[selectb].tip].com[i]==13)
     textprintf_ex(buffer,font,510,260+16*i,ALB,BACKG,"%s",
          comm[tb[b[selectb].tip].com[i]]);     
     else 
     if(b[selectb].construieste||b[selectb].release){
     textprintf_ex(buffer,font,510,260+16*i,GRIINCHIS,BACKG,"%s",
     comm[tb[b[selectb].tip].com[i]]);
     aux=(float)(tu[b[selectb].unit].timp-b[selectb].timp)/
         (float)(tu[b[selectb].unit].timp);
     Termometru(510,390,100,10,aux);
     }
     else
     textprintf_ex(buffer,font,510,260+16*i,ALB,BACKG,"%s",
          comm[tb[b[selectb].tip].com[i]]);     
     line(buffer,499,256+16*(i+1),623,256+16*(i+1),ROSU);
     }     
}
}
}

void DrawSelect(){
     if(selectu){
     int auxx,auxy,parcurs,unghi;
     auxx=auxy=0;
/*     textprintf_ex(buffer, font, 510, 220,ALB,BACKG, 
    "Coord:%d %d" ,u[selectu].locx,u[selectu].locy);
     textprintf_ex(buffer, font, 510, 230,ALB,BACKG, 
     "Or: %d Tag: %d",u[selectu].unghi,selectu);*/
     DrawMenu();
     if(
     intre(u[selectu].locx,map.cx,map.cx+limitax-1,1)&&
     intre(u[selectu].locy,map.cy,map.cy+limitay,1)){
     parcurs=u[selectu].parcurs;                           
     unghi=u[selectu].unghi;
     if(parcurs!=0){if(unghi==0) auxy=+parcurs;
                    if(unghi==1) {auxy=+parcurs;auxx=-parcurs;}
                    if(unghi==2) auxx=-parcurs;
                    if(unghi==3){ auxx=-parcurs; auxy=-parcurs;}
                    if(unghi==4) auxy=-parcurs;
                    if(unghi==5) {auxy=-parcurs; auxx=+parcurs;}
                    if(unghi==6) auxx=+parcurs;
                    if(unghi==7) {auxx=+parcurs;auxy=+parcurs;}
                    }
     
     auxx=-auxx+(u[selectu].locx-map.cx)*patrat+16;//auxx=auxx+u[selectu].parcurs;
     auxy=-auxy+(u[selectu].locy-map.cy)*patrat+14;//auxy=auxy+u[selectu].parcurs;
     circle(buffer,(auxx),(auxy),18,
     makecol(255-parcurs*5,255-parcurs*5,255-parcurs*5));
     circle(buffer,(auxx),(auxy),19,
     makecol(255-parcurs*5,255-parcurs*5,255-parcurs*5));
     }
     }
     if(selectb){
          int locx,locy,cx,cy,lx,ly;
          float auxx,auxy;     
          locx=b[selectb].locx;
          locy=b[selectb].locy;
          cx=map.cx;
          cy=map.cy;
          lx=b[selectb].lx;
          ly=b[selectb].ly;
          DrawMenu();
          if(intre(locx,cx,cx+limitax-1,1)
          &&intre(locy,cy,cy+limitay-1,1)){
          auxx=(locx-cx)*patrat+lx*16;
          auxy=(locy-cy)*patrat+ly*16;
        
          ellipse(buffer,(int)auxx,(int)auxy,lx*20,ly*20,ALB);
          }
     }
     
}


void AfisCursor()
{if(intre(cur.locx,map.cx,map.cx+limitax-1,1)
    &&intre(cur.locy,map.cy,map.cy+limitay,1)
    &&cur.frame)
{
    draw_sprite(buffer,(BITMAP*)curs[(cur.frame/5)+1].dat,
    (cur.locx-map.cx)*patrat,(cur.locy-map.cy)*patrat);
    cur.frame--;

}
}
