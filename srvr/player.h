bool LoadPlayer(char *aux,ENetPeer *iip){
     int i;
     for(i=1;i<20;i++)
       if(!player[i].activ)
       {
           strcpy(player[i].name,aux);
           player[i].peer=iip;
           player[i].activ=1;
           nrplayers++;
     
           return 1;
           
        }
       return 0;     
}

void DeletePlayer(int i){
     player[i].activ=0;
     nrplayers--;
     }

int FindPlayer(char *name){
int i;
 
for(i=0;i<20;i++)
if(strcmp(name,player[i].name)==0&&player[i].activ)return i;
     return -1;
}
