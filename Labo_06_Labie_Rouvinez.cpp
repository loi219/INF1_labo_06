/*
 -----------------------------------------------------------------------------------
 Laboratoire : <nn>
 Fichier     : <nom du fichier>.cpp
 Auteur(s)   : <prénom> <nom>
 Date        : <jj.mm.aaaa>

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 4.8.1
 -----------------------------------------------------------------------------------
 */


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>


//Méthode permettant de vider le Buffer
#define VIDER_BUFFER while(cin.get() != '\n')

using namespace std;


int saisie(int borne_inf, int borne_sup, string textSaisie);

void afficheCircuit(int longueurCircuit, int amplituteVirage, int largeurRoute, int largeurTotale);

bool recommencer(char OUI, char NON);


int main() {
   
   const char OUI = 'O';
   const char NON = 'N';
   
   const int LONG_CIRC_MIN  =  0; 
   const int LONG_CIRC_MAX  =  1000; 
   
   const int AMPLI_MIN  =  1; 
   const int AMPLI_MAX  =  3; 
   
   const int LARG_ROUTE_MIN  =  3; 
   const int LARG_ROUTE_MAX  =  10; 
   
   const int LARG_TOTALE_MIN  =  20; 
   const int LARG_TOTALE_MAX  =  50; 
   
   
   int longueurCircuit;
   int amplitudeVirage;
   int largeurRoute;
   int largeurTotale;
  
   
   
   do{
      
      
      longueurCircuit  =  saisie(LONG_CIRC_MIN, LONG_CIRC_MAX, "Longueur Circuit [ 0 - 1000 ]: ");
      amplitudeVirage  =  saisie(AMPLI_MIN, AMPLI_MAX, "Amplitue [ 1 - 3 ] : ");
      largeurRoute     =  saisie(LARG_ROUTE_MIN, LARG_ROUTE_MAX, "Largueur Route [ 3 - 10 ] : ");
      largeurTotale    =  saisie(LARG_TOTALE_MIN, LARG_TOTALE_MAX, "Largeur Totale [ 20 - 50 ] : ");
      
      afficheCircuit(longueurCircuit, amplitudeVirage, largeurRoute, largeurTotale);
      
      
   }while(recommencer(OUI,NON)); 
   return EXIT_SUCCESS;
}


//=================================     saisie     ================================//

int saisie(int borne_inf, int borne_sup, string textSaisie) {

   int val;
   bool cinFail;

   do {

      cinFail = false;

      cout << textSaisie;
      cin  >> val;

      //répare le buffer en cas de nécessité
      if (cin.fail()) {

         cinFail = true;
         cin.clear();
      }
      VIDER_BUFFER;

   } while (val < borne_inf || val > borne_sup || cinFail);

   return val;
}


//============================      AfficheCircuit      ===========================//

void afficheCircuit(int longueurCircuit, int amplitudeVirage, int largeurRoute, int largeurTotale) {
   
   double espace = (largeurTotale - largeurRoute)/2.0;
   
   int espaceGauche = floor(espace);
   int espaceDroite = ceil(espace);
   
   
   int espaceCircuit = floor(log10(longueurCircuit))+1;
   
   cout << espaceCircuit << endl;
   
   
   int amplitude;
   
   string route;
   
   for(int i = 1; i <= largeurRoute; i++){
      route += "=";
   }
   
   bool espaceOk;
   
   //Iinitialisation du générateur aléatoire
   srand((unsigned)time(NULL));
   
   for(int etapeCircuit = 0 ; etapeCircuit <= longueurCircuit; etapeCircuit++){
      
      cout << setw(0) << "" << right << setw(espaceCircuit);
      
      if(!(etapeCircuit%10)){
         cout << etapeCircuit;
      }else{
         cout << "";
      }
      
      cout << "|" << setw(espaceGauche) << "" << route << setw(espaceDroite) << "|" << endl;
      
      do{
         amplitude  = rand() % (2*amplitudeVirage+1);
         amplitude -= amplitudeVirage;
         espaceOk   = espaceGauche > -1*amplitude && espaceDroite > amplitude;
      }while(!espaceOk);
      
      espaceGauche += amplitude;
      espaceDroite -= amplitude;
   }
}

//============================       recommencer        ===========================//

bool recommencer(char OUI, char NON) {

   char recommencer;
   bool sortie;

   do {

      cout << "Voulez vous recommencer ? [" << OUI << "/" << NON << "] : ";
      cin >> recommencer;
      VIDER_BUFFER;
      
      recommencer = toupper(recommencer);  //met le char entré en majuscule

      sortie = recommencer == OUI || recommencer == NON;

   } while (!sortie);

   return recommencer == OUI;
}