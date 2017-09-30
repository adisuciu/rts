class jucator { public:
                int bani,locuri, locurimax,cladiri,unitati,tag;
                char nume[100];
                void Initjuc(char *nume,int bbani,int llocuri,int ccladiri,int uunitati,int ttag);
                } juc[20];

void jucator::Initjuc(char *nnume,int bbani,int llocuri,int ccladiri,int uunitati,int ttag)
{    strcpy(nume,nnume);
     bani=bbani;locuri=llocuri;cladiri=ccladiri;unitati=uunitati,tag=ttag;
     
     }
