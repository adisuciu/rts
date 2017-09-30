
bool intre(int x,int a,int b,bool e){
     if(e) if(x<=b&&x>=a) return 1;
     else if(x<b&&x>a) return 1;
     return 0;
     }



void harta::load_map(char fis[])
{
     FILE *fisier;
     fisier=fopen(fis,"r");
     if(!fisier) 
      {textprintf_ex(screen,font,200,100,ROSU,NEGRU,"... EROARE");return;}
     int i,j;
     float ix,iy;
     fscanf(fisier,"%d %d",&x,&y);
     cx=cy=1;
     ix=x;iy=y;
     ratiax=125./ix;
     ratiay=125./iy;
     for(i=0;i<x;i++)
     for(j=0;j<y;j++){
     fscanf(fisier,"%d",&map[j][i]);    
                   }
     textprintf_ex(screen,font,200,100,VERDEDESCHIS,NEGRU,"... INCARCAT");
     }
bool harta::obstacol(int item){
/* APA  */ if(item==2||intre(item,23,26,1)||intre(item,11,18,1)) return 1;
return 0;
     
     }
void harta::fill_obs(){
     int i,j;
     for(i=0;i<x;i++){
       for(j=0;j<y;j++){
                        if(i==0||j==0||i==x-1||j==y-1) obs[i][j]=10;
                        if(obstacol(map[i][j])) obs[i][j]=10;
                        }
       }
}
void harta::Minimap(){
     int i,j,item;
     for(i=0;i<x;i++)
      for(j=0;j<y;j++){
      item=map[i][j];
    if(obs[i][j]==player){ item=VERDEDESCHIS;putpixel(minimap,i,j,item);continue;}
   else if(obs[i][j]&&!obstacol(map[i][j])&&obs[i][j]!=10) 
   {item=ROSU;   putpixel(minimap,i,j,item);continue;}
/* IARBA*/ if(item==0||item==10){ item=VERDE;putpixel(minimap,i,j,item);continue;}
/* NOROI*/ if(item==1||intre(item,3,10,1)||intre(item,19,22,1)) {item=MARO;
                                          putpixel(minimap,i,j,item);continue;}
/* APA  */ if(item==2||intre(item,11,18,1)||intre(item,23,26,1))  {item=ALBASTRU;
                                         putpixel(minimap,i,j,item);continue;}
     


     putpixel(minimap,i,j,item);
     }
     rect(minimap,cx,cy,cx+limitax-1,cy+limitay-1,ALB);
     stretch_blit(minimap,buffer,0,0,x,y,498,33,125,125);
     }


void harta::draw_map(){
     int i,j;
     int item,bufx,bufy;
     for(i=cx;(i<cx+limitax);i++)
      for(j=cy;(j<cy+limitay);j++){
      if(i>=x||j>=y) break;
      item=map[i][j];
      
      bufx=(i-cx)*patrat;
      bufy=(j-cy)*patrat;
       rotate_sprite(buffer,(BITMAP*)ter[item].dat,bufx,bufy,itofix(0));
       } 
           Minimap();
           textprintf_ex(buffer, font, 400, 400,ALB,BACKG, "%d %d" ,cx,cy);   
     }
