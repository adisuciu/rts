void SendP(char *mesaj,int p);
void InitServer(){
char aux[250];
bool b;
b=enet_initialize();
if(!b)sprintf(aux,"Initializare ENet ... OK ");
else sprintf(aux,"Initializare ENet ... EROARE ");
put_ecran(aux);
address.host=ENET_HOST_ANY;
address.port = 2408;
server = enet_host_create (& address , 32 , 0 , 0 );
enet_host_service(server,&event,1000);
if(server) put_ecran("Initializare Server ... OK");
else put_ecran("Initializare Server ... ERROR");
       }
void Hello(char *mesaj){
     char aux[50][2];
     put_ecran(mesaj);
      sscanf(mesaj,"%s %s",&aux[0],&aux[1]);
      if(FindPlayer(aux[1])==-1) LoadPlayer(aux[1],event.peer);
      else  enet_peer_disconnect(event.peer);
     }
     
void Disc(char *mesaj){
     char aux[50][2];
       sscanf((char*)event.packet->data,"%s %s",&aux[0],&aux[1]);
       put_ecran(mesaj);
       DeletePlayer(FindPlayer(aux[1]));
       enet_peer_disconnect(event.peer);
       sprintf(aux[0],"Playerul %s s-a deconectat",aux[1]);
     
     }
void SendAll(char *mesaj,int who){
     ENetPacket *packet;  
     int i;
     char aux[300];
     sprintf(aux,"SENDALL %s", mesaj);
     for(i=0;i<20;i++)
     if(player[i].activ&&i!=who){
     packet=enet_packet_create (mesaj,strlen(mesaj)+1,ENET_PACKET_FLAG_RELIABLE);
     enet_peer_send (player[i].peer, 0, packet);
     enet_host_service(server, & event, 2);
     } 
}
void SendP(char *mesaj,int p){
     ENetPacket *packet;  
     int i;
     char aux[300];
     sprintf(aux,"SEND %d %s",p, mesaj);
     put_ecran(aux);
     packet=enet_packet_create (mesaj,strlen(mesaj)+1,ENET_PACKET_FLAG_RELIABLE);
     enet_peer_send (player[p].peer, 0, packet);
     enet_host_service(server, & event, 2);
     }
void KeepSendUntil(char *mesaj,int p, char *until){
     char aux[250],mess[250];
     while(1){           
     SendP(mesaj,p);
     if(event.type==ENET_EVENT_TYPE_RECEIVE){
     strcpy(mess,(char*)event.packet->data);
     sscanf(mess,"%s",&aux); 
     if(strcmp(aux,until)==0) return;
     }
}
}
void KeepSendAllUntil(char *mesaj,int p, char *until){
     char aux[250],mess[250];
     while(1){           
     SendAll(mesaj,p);
     if(event.type==ENET_EVENT_TYPE_RECEIVE){
     strcpy(mess,(char*)event.packet->data);
     sscanf(mess,"%s",&aux); 
     if(strcmp(aux,until)==0) return;
     } 
 }
}
void Move(char *mesaj){
    char aux[50][2];
    sscanf((char*)event.packet->data,"%s %s",&aux[0],&aux[1]);
         put_ecran(mesaj);
    SendAll(mesaj,FindPlayer(aux[1]));
}
void BuildB(char *mesaj){
    char aux[50][2];
    sscanf((char*)event.packet->data,"%s %s",&aux[0],&aux[1]);
         put_ecran(mesaj);
    SendAll(mesaj,FindPlayer(aux[1]));
     }
void Comm(char *mesaj){
    char aux[50][2];
    sscanf((char*)event.packet->data,"%s %s",&aux[0],&aux[1]);
         put_ecran(mesaj);
    SendAll(mesaj,FindPlayer(aux[1]));
     }

void Wait(char *mesaj){
   char aux[50];
   int auxi;
    sscanf((char*)event.packet->data,"%s %d",&aux,&auxi);
    sync[auxi]=1;     
     
     }
void VerifSync(){
     int b;
     int i;
     b=1; 
     for(i=0;i<20;i++){
               if(player[i].activ&&(sync[i]==0)){ b=0;}
                       }
        
     if(b) {for(i=0;i<4;i++){SendAll("GO",-1);rest(3);syncb=0;}
/*     for(i=0;i<20;i++){
         if(player[i].activ&&(sync[i])) KeepSendUntil("GO",i,"ACK");sync[i]=0;
                       }*/
     for(i=0;i<20;i++) sync[i]=0;
     }
}
void Ciclu(){
     int i;     
     char mesaj[250];
     char aux[250];
if(!start){     
     if(status==1&&!start) {start=1;
     for(i=0;i<20;i++){
     if(player[i].activ){
         sprintf(aux,"START %d %d",i,nrplayers);
         SendP(aux,i);}}
     }
     enet_host_service (server, & event, 100);
     if(event.type==ENET_EVENT_TYPE_CONNECT){
       put_ecran("Cineva se conecteaza... Astept hello");
       }
     if(event.type==ENET_EVENT_TYPE_RECEIVE){
     strcpy(mesaj,(char*)event.packet->data);
     
     sscanf(mesaj,"%s",&aux);

     if(strcmp(aux,"HELLO")==0){ Hello(mesaj); }
     if(strcmp(aux,"DISC")==0)  {Disc(mesaj);}                
                }
    }
     else {
          enet_host_service (server, & event, 100);
     if(event.type==ENET_EVENT_TYPE_RECEIVE){
     strcpy(mesaj,(char*)event.packet->data);
     sscanf(mesaj,"%s",&aux);
     if(strcmp(aux,"MOVE")==0&&!syncb) {Move(mesaj);} 
     if(strcmp(aux,"BUILDB")==0&&!syncb){BuildB(mesaj);}  
     if(strcmp(aux,"DISC")==0)  {Disc(mesaj);}  
     if(strcmp(aux,"COMM")==0)  {Comm(mesaj);}
     if(strcmp(aux,"WAIT")==0) {syncb=1;Wait(mesaj);}
     if(syncb) VerifSync();
     }

      
     }
}
