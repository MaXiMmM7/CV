#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string>
#include <iostream>

using namespace std;

const int bSchermo = 500; //riquadro 500x500
const int hSchermo = 510; //ultime 10 righe per informazioni(passi, statistica et c.)
const int d = bSchermo+2; // +2 per bordi o per sovrapposizione toro
//.... colori
int nero;//   = makecol(0,0,0);
int blu ;// sfondo spazio vuoto  = makecol(0,128,255);
int bianco;// particelle mobili = makecol(255,255,255);
int verdescuro; // = makecol(0, 128, 50);
int verdechiaro;//= makecol( 0, 255, 128);
int rosso;// particelle fisse = makecol(255,0,0);

//..........altri colori
BITMAP *buffer;//Dichiarazioni generali: buffer
int passi=0;   // passi

int conf0[d][d]; // configurazioni
int conf1[d][d];

// variabili globali di DIFFUSIONE-AGGREGAZIONE

// ----------------------------

void toro()
{// condizione superficie toroidale
  int lim = d-1;
  for (int i=1; i<lim; i++)
     {conf0[0][i] = conf0[lim-1][i] ;
      conf0[i][0] = conf0[i][lim-1];
      conf0[lim][i] = conf0[1][i];
      conf0[i][lim] = conf0[i][1];
     }
   conf0[0][0] = conf0[lim-1][lim-1] ;
   conf0[0][lim] = conf0[lim-1][1] ;
   conf0[lim][0] = conf0[1][lim-1] ;
   conf0[lim][lim] = conf0[1][1] ;
}

void cornice_inerte()
{// condizione cornice di celle inerti
   for (int k=0; k<d; k++)
     {conf0[0][k] = -1 ;
      conf0[k][0] = -1;
      conf0[d-1][k] = -1;
      conf0[k][d-1] = -1;
     }
}

void inizial ()
{
 // DATI IN INGRESSO
    float perc=90;
    int iniziali=5;

   /* generazione pseudocasuale */
   float c;
   int lim=d-1;
   srand(time (0));
   for (int i=1; i<lim; i++)
	   for (int j=1; j<lim; j++)
		{  c=rand()%100;
		   if (c <= perc) conf0[i][j] = -1;
		   else conf0[i][j] = 1;
		}
   for (int i=0; i<iniziali; i++)
       conf0[rand()%lim+1][rand()%lim+1] = 0;
   // condizione superficie toroidale
   toro();
}

void cella_aggr (int x, int y)
{ int sini, des, alto, basso, prod=1;
  sini=x-1; des=x+1;
  basso=y-1; alto=y+1;
  for (int i=sini; i<=des; i++)
	for (int j=basso; j<=alto; j++)
	    prod=prod*conf0[i][j];
  if ((prod==0) && (conf0[x][y]==1)) conf1[x][y]=0;
}

/*void cella_trans (int x, int y)
{ switch(conf0[x][y])
       { case -1: conf1[x][y]=-1; break;
         case  0: conf1[x][y]= 2; break;
	     case  1: conf1[x][y]= contagio(x,y); break;
         case  2: conf1[x][y]= 2; break;;
       }
}

void cella_trans (int x, int y)
{ switch(conf0[x][y])
       { case -1: conf1[x][y]=-1; break;
         case  0: conf1[x][y]= 2; break;
	     case  1: conf1[x][y]= contagio(x,y); break;
         case  2: conf1[x][y]= 2; break;;
       }
}*/
void copia ()
// si copia la configurazione
{ for (int i=0; i<d; i++)
	for (int j=0; j<d; j++)
		conf0[i][j] = conf1[i][j] ;
}

/*void cella_aggr(int x, int y)
{if ((conf0[x-1][y]==0)||(conf0[x+1][y]==0)||(conf0[x][y+1]==0)||(conf0[x][y-1]==0))
     if (conf0[x][y] == 1 )conf1[x][y] = 0;
_________________________________________________
 //for (int i=x-1; i<=(x+1); i++)
	//for (int j=y-1; j<=(y+1); j++)
		//if ((conf0[i][j] == 0) && )
}*/

void cella_diff (int x, int y)
{bool clockwise=rand()%2 ;
 int aux;
 if (!((conf0[x][y]==0)||(conf0[x+1][y]==0)||(conf0[x][y+1]==0)||(conf0[x+1][y+1]==0)))
   if (clockwise)
	 {
      conf1[x][y] = conf0[x][y+1];
      conf1[x][y+1] = conf0[x+1][y+1];
      conf1[x+1][y+1] = conf0[x+1][y];
      conf1[x+1][y] = conf0[x][y];
     }
   else
	 {
      conf1[x][y] = conf0[x+1][y] ;
	  conf1[x+1][y] = conf0[x+1][y+1];
	  conf1[x+1][y+1] = conf0[x][y+1];
      conf1[x][y+1] = conf0[x][y];
     }
}

void diffus1 ()
{ for (int i=0; i<d; i+=2)
	for (int j=0; j<d; j+=2)
	  cella_diff (i,j);
}

void diffus2 ()
{for (int i=1; i<d-1; i+=2)
	for (int j=1; j<d; j+=2)
	  cella_diff (i,j);
}

void aggrega ()
{for (int i=1; i<d; i++)
     for (int j=1; j<d; j++)
	     cella_aggr (i,j);
}

void transiz ()
{ if (passi%2==0)diffus1();
  else diffus2();
// condizione superficie toroidale
  toro();
  copia();
  aggrega();
  toro();
  copia();
}

int main()
 {// inizializzazione;
  float percvive;// perc = 4
  inizial ();
  allegro_init();
  install_keyboard();
  install_mouse();
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, bSchermo, hSchermo, 0, 0);
     //Indica al computer la modalità grafica che intendiamo usare
  show_mouse(screen);
     //Mostra il mouse sullo schermo
  buffer = create_bitmap(bSchermo, hSchermo);
     // Funzione che crea il buffer dove disegniamo gli elementi
  blu    = makecol(0, 128, 255);
  nero   = makecol(0, 0, 0);
  bianco = makecol(255,255,255);
  verdescuro  = makecol( 0, 128, 50);
  verdechiaro = makecol (0, 255, 128);
  rosso = makecol(255, 0, 0);
     //Regola il colore degli elementi
  while (!key[KEY_ESC])
    {/* funzione di transizione */
     transiz();
     passi++;
     for (int y=0; y<bSchermo; y++)
	     for (int x=0; x<hSchermo; x++)
	         switch(conf0[x][y])
               { case -1: putpixel(buffer, x, y, blu); break;
                 case  0: putpixel(buffer, x, y, rosso); break;
	             case  1: putpixel(buffer, x, y, bianco); break;
                 //case  2: putpixel(buffer, x, y, verdechiaro); break;;
               }
     textprintf_ex(buffer,font,0,502,bianco,nero, "iterazioni: %i",passi);
     //textprintf_ex(buffer,font,280,502,bianco,nero, "percentuale vive : %f",percvive);       //stampa sul buffer il numero di iterazioni
     blit(buffer,screen,0,0,0,0,bSchermo,hSchermo);
     //stampa (disegna)sullo schermo il buffer d'uscita
	}
	return 0;
}
END_OF_MAIN()
