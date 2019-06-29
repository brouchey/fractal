//  Terrain Fractal par la Méthode Diamant-Carré 
//  Roucheyrolles Benjamin
//  Licence Pro SIL Image et Son 2006/2007      

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <time.h> 
#include <string.h>

#define maxtaille 257
#define maxvalue 255

using namespace std;

// Définition du type représentant une image en niveaux de gris (ndg)
typedef int ndgIm [maxtaille][maxtaille];

void 
openFile (char *nom, FILE **desc, char *mode)
{
  *desc = fopen (nom, mode);
  if (*desc == NULL)
    {
      fprintf (stderr, 
	       "\"%s\": Nom de fichier incorrect", 
	       nom);
      if (mode [0] == 'w')
	fprintf (stderr, " ou ouverture en écriture impossible.");
      exit (EXIT_FAILURE);
    }
}

void 
writeHead (FILE *descFic, char *mode)
{
  fprintf (descFic, "%s\n", mode);
  fprintf (descFic, "%d %d\n", maxtaille, maxtaille);
  fprintf (descFic, "%d\n", maxvalue);
}

float rugosity(int taille)
{ 
	float rapport_taille_valmax=maxtaille/maxvalue;
	float res=(2.0*((float)rand()/RAND_MAX)-1.0)*(float)taille/rapport_taille_valmax;
	return res;
}

// Création d'un descripteur de fichier
void
ecrireFractalImage(char *nom){
                   
	FILE *descFic = NULL;
	openFile (nom, &descFic, "w");

	// Extension du fichier
	if (strstr(nom,".raw")==NULL) writeHead (descFic, "P2");
	ndgIm grille;

	int dep_x, dep_z,x,y;
	int taille=maxtaille;
	int ex_taille=taille;

	// Initialisation des points à 0
	for (x=0; x < maxtaille; x++) {
		for (y=0; y < maxtaille; y++) {
			grille[x][y]=0;
		} 
	}

	//
	// Méthode DIAMANT-CARRE
	//

	// Initialisation des quatre sommets
	
	grille[0][0] = (int) rugosity(0);
	grille[0][maxtaille-1] = (int) rugosity(0);
	grille[maxtaille-1][maxtaille-1] = (int) rugosity(0);
	grille[maxtaille-1][0] = (int) rugosity(0);

	while(taille>2){

	// Traitement Diamant-Carré à des pas différents (en fonction de taille)
	
	for (dep_z = 0; dep_z + taille-1 <= maxtaille; dep_z += (ex_taille+1)/2-1){
	    for (dep_x = 0; dep_x + taille-1 <= maxtaille; dep_x += (ex_taille+1)/2-1)
	    {
	        // Calcul du point MILIEU (méthode diamant)
	        grille[dep_x + (taille-1)/2][dep_z + (taille-1)/2] = \
	        abs(grille[dep_x][dep_z] \
	        + grille[dep_x + taille-1][dep_z] \
	        + grille[dep_x + taille-1][dep_z + taille-1] \
	        + grille[dep_x][dep_z + taille-1])/4 +(int)(rugosity(taille));
						
			// Calcul des milieux de chaque coté (méthode carré)
					
			//TOP
			if (grille[dep_x + (taille-1)/2][dep_z] == 0)
			grille[dep_x + (taille-1)/2][dep_z] = \
	        abs(grille[dep_x][dep_z] \
	        + grille[dep_x][dep_z + taille -1] \
	        + grille[dep_x + (taille-1)/2][dep_z + (taille-1)/2]*2)/4 +(int)(rugosity(taille)) ;\
	                        
			//BOTTOM
			if (grille[dep_x + (taille-1)/2][dep_z + taille-1] == 0)
			grille[dep_x + (taille-1)/2][dep_z + taille-1] = \
	        abs(grille[dep_x + (taille-1)/2][dep_z + (taille-1)/2]*2\
	        + grille[dep_x + taille-1][dep_z + taille-1]\
	        + grille[dep_x][dep_z + taille - 1]) /4 +(int)(rugosity(taille));\
	        
			//RIGHT
			if (grille[dep_x + taille -1][dep_z + (taille-1)/2] == 0)
			grille[dep_x + taille -1][dep_z + (taille-1)/2] = \
	        abs(grille[dep_x + taille -1][dep_z]\
	        + grille[dep_x + taille-1][dep_z + taille-1]\
	        + grille[dep_x + (taille-1)/2][dep_z + (taille-1)/2]*2)  /4 +(int)(rugosity(taille));\
	        
			//LEFT
			if (grille[dep_x][dep_z + (taille-1)/2] == 0)
			grille[dep_x][dep_z + (taille-1)/2] = abs(grille[dep_x][dep_z]\
	        + grille[dep_x + (taille-1)/2][dep_z + (taille-1)/2]*2 \
	        + grille[dep_x][dep_z + taille -1])/4  +(int)(rugosity(taille));\
	                            
	    }
	    
	  } 	
	    ex_taille = taille;
	    taille = (taille+1)/2;	    
	}

	if (strstr(nom,".raw")==NULL) {
	    for (y=0; y < maxtaille; y++)
	    {
	      for (x=0; x < maxtaille; x++){
		      fprintf (descFic, "%d ", grille[x][y]);
	          fprintf (descFic, " ");
	          } 
	    } 	   
	} else {
	     for (y=0; y < maxtaille; y++)
	         {
	         for (x=0; x < maxtaille; x++){
	         fprintf (descFic, "%d %d %d", x, y, grille[x][y]);
	         fprintf (descFic, "\n");
	         } 
	     }
	    }
	fclose (descFic);
}

int 
main ()
{ 
  // Déclaration de la gestion des nombres aléatoires pour la rugosité
  srand(time(NULL));  
  ecrireFractalImage("fractal.pgm");
  ecrireFractalImage("fractal.raw");
  return EXIT_SUCCESS;
}
