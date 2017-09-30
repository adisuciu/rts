ENetHost * client;
ENetEvent event;
ENetAddress address;
ENetPeer *peer;
char Scom[250]={"NULL"};
void SendServ(char *mess){
ENetPacket *packet ;
if(retea){
packet = enet_packet_create (mess,strlen(mess)+1,ENET_PACKET_FLAG_RELIABLE);
enet_peer_send (peer, 0, packet);
enet_host_service(client, & event, 1);
}
}
     
void initnet(){
     FILE *in;
     char add[128];
     char aux[200];
     int ret;
     enet_initialize();
     in=fopen("net.in","r");
     fscanf(in,"%d",&retea);
     fscanf(in,"%s",&add);
     fscanf(in,"%s",&nume);
     fclose(in);
     client = enet_host_create (NULL , 10 ,  0, 0 );
     enet_address_set_host (& address, add );
     address.port = 2408;
     peer = enet_host_connect (client, &address, 2);    
     enet_host_service(client, & event, 1000);
     // TRIMITE PACHET DE HELLO
     sprintf(aux,"HELLO %s",nume);
     SendServ(aux);
     if(peer==NULL){ textprintf_ex(screen,font,1,160,ALB,NEGRU,
                  "NU MA POT CONNECTA LA SERVER");
                  readkey();
                  exit(0);
                  }
            
     }

void LoadUnitsfromfile(char *file, int x){
     FILE *in;
     int auxi[5],i,j;
     in=fopen(file,"r");
     for(i=1;i<=x;i++){
     fscanf(in,"%d %d %d %d",&auxi[0],&auxi[1],&auxi[2],&auxi[3]);
       u[i].LoadUnit(auxi[0],auxi[1],auxi[2],auxi[3]);
                      }
     }

void WaitForStart(){
char aux[200];
int x;
     while(1){
              enet_host_service(client,&event,1);
              if(event.type==ENET_EVENT_TYPE_RECEIVE){
              sscanf((char*)event.packet->data,"%s %d %d",&aux,&player,&x);
              
               if(strcmp(aux,"START")==0){LoadUnitsfromfile("map1.obj",x);                                                                                       
                                          return; }                 
              }
              if(key[KEY_ESC]) {sprintf(aux,"DISC %s",nume);
                                SendServ(aux);
                                deinit();
                                }
    }
}
void WaitFor(char *scom){
     char aux[200];
     while(1){
              enet_host_service(client,&event,2);
              if(event.type==ENET_EVENT_TYPE_RECEIVE){
              sscanf((char*)event.packet->data,"%s ",&aux); 
               if(strcmp(aux,scom)==0) return;

               }  
              if(key[KEY_ESC]) {sprintf(aux,"DISC %s",nume);
              SendServ(aux);
              deinit();
                                }             
              }
    }


 void MoveNetUnit(char *mess){
     char auxc[50][2];
     int auxi[5];
     if(retea){
   sscanf(mess,"%s %s %d %d %d %d %d",&auxc[0],&auxc[1],
   &auxi[0],&auxi[1],&auxi[2],&auxi[3],&auxi[4]);
     u[auxi[0]].nextx=auxi[1];
     u[auxi[0]].nexty=auxi[2];
     u[auxi[0]].urmu=auxi[3];
     u[auxi[0]].urmb=auxi[4];}
     }    
void BuildNet(char *mess){
     char auxc[50][2];
     int auxi[6];
     int selectuaux;
     int selectbaux;
     if(retea){
     sscanf(mess,"%s %s %d %d %d %d",&auxc[0],&auxc[1],&auxi[0],&auxi[1],&auxi[2],&auxi[3]);
     selectuaux=selectu;
     selectbaux=selectb;
     selectu=auxi[0];
     u[selectu].locx=auxi[2];
     u[selectu].locy=auxi[3];
     NewBuilding(auxi[1]);
     selectu=selectuaux;
     selectb=selectbaux;
     
     }
}
void KeepSendServUntil(char *mesaj,char *trigger){
     char aux[250],mess[250];
     while(1){           
     SendServ(mesaj);
     if(event.type==ENET_EVENT_TYPE_RECEIVE){
     strcpy(mess,(char*)event.packet->data);
     sscanf(mess,"%s",&aux); 
     if(strcmp(aux,trigger)==0) return;
     }
     rest(20);
}
     }
     
void Comm(char *mesaj){
     char auxc[50][2];
     int auxi[3];
     int selectuaux,selectbaux;
     selectuaux=selectu;
     selectbaux=selectb;
     if(retea){
     sscanf(mesaj,"%s %s %d %d %d",&auxc[0],&auxc[1],&auxi[0],&auxi[1],&auxi[2]);
     selectu=auxi[1];
     selectb=auxi[2];
     Comanda(auxi[0],1);
     selectu=selectuaux;
     selectb=selectbaux;
     
    }
 }    

     
     
void Retea() {
     char mess[250],aux[250];
     int i;
     if(strcmp(Scom,"NULL")!=0) for(i=0;i<8;i++){SendServ(Scom);}
     enet_host_service(client,&event,1);
     if(event.type==ENET_EVENT_TYPE_RECEIVE){
     strcpy(mess,(char*)event.packet->data);
     sscanf(mess,"%s",&aux);
     if(strcmp(aux,"MOVE")==0)MoveNetUnit(mess);
     if(strcmp(aux,"BUILDB")==0) BuildNet(mess);
     if(strcmp(aux,"COMM")==0) Comm(mess);
     sprintf(aux,"%d",countdown);
     }
     if(countdown==sync) {sprintf(aux,"WAIT %d",player);
                         KeepSendServUntil(aux,"GO");
                         countdown=0;
                         SendServ("ACK");
                         }
     strcpy(Scom,"NULL");   
}

