class msg{
public:
      char mesaj[200];
      int timp;
      int timplim;
      bool activ;
      void LoadMsg(char msj[],int ttimplim);
      void DrawMsg();      
      
      };
void msg::LoadMsg(char msj[],int ttimplim){
     sprintf(mesaj,msj);
     timp=0;
     timplim=ttimplim;
     activ=1;
     
     }

void msg::DrawMsg(){
     float aux;
     if(activ) timp++;
     aux=(float)timp/(float)timplim;
     if(timplim==timp) {activ=0;return;}
     else textprintf_ex(buffer,font,260-text_length(font,mesaj)/2,360,
     makecol((int)((float)255*(1-aux)),
             (int)((float)255*(1-aux)),
             (int)((float)255*(1-aux))),BACKG,mesaj);
     
     }
