typedef class unit{
public:
        int locx,locy; // locatia actuala
        int destx,desty; // incotro merge
        int nextx,nexty; // in cazul in care s-a dat click intre patrate aici se salveaza
        int unghi; // unghiu in care se misca
        int player;
        int hp,hpmax,dmg,delay,range;
        int del;
        int urmu,urmb;
        int explst;
        int atacimg;
        int atimg;
        float c1,cmax; // contor .. odata la cate cicluri face miscare
        int speed; // cati pixeli sare /  ciclu
        int parcurs; // cat o mers intre patratele
        bool repaus; // daca sta pe loc sau nu
        int activ,frame,nrbit1,nrbit2;
        int tip;
         // frame,nrbit1,nrbit2 pt imagini
        void LoadUnit(int x,int y,int ttip,int pplayer);
        void SetareUnghi(int auxx,int auxy);
        void SetareParcurs(int &auxy,int &auxx);
        void SetareLoc();
        bool VerifUrm();
        void DrawUnit();
        void DrawProj();
        void Atac(int urm,bool bol);
        void MoveUnit(); 
        };



typedef class harta{
  public:

// V A R I A B I L E
      int x,y;// dimensiune
      int map[200][200];// harta
      int obs[200][200];//obstacole      
      int cx,cy; // afisarea 
      float ratiax,ratiay;
// M E T O D E  
      void load_map(char fis[]);
      bool obstacol(int item);
      void fill_obs();
      void draw_map(); 
      void Minimap();
      };
      
      
      
      
      typedef class build 
              { public:
                int locx,locy;
                int lx,ly;
                int nrbit;
                int tip;
                int player;
               int hp,hpmax,dmg,delay,range;
               int del;
               int contor,cmax;
               int explst;
               int tag;
                bool activ;
                bool construieste;
                bool release;
                int unit;
                int timp;
                void LoadBuild(int x,int y,int ttip,int pplayer,int ttag);
                void DrawBuild();
                void Build();
                };
bool NewBuilding(int tip);
void Comanda(int item,bool primit);
void init();
void deinit();
