/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 06 Circuit
 Fichier     : Labo_06_Labie_Rouvinez.cpp
 Auteur(s)   : <prénom> <nom>
 Date        : 28.11.2016

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


string textSaisie(string texte, int borne_inf, int borne_sup, int espaceAlligne,
                  int espaceBorne);

int saisie(int borne_inf, int borne_sup, string textSaisie);

void afficheCircuit(int espaceGauche, int espaceDroite, string route, int etapeCircuit,
                    int espaceCircuit, int espaceMetre, int frequenceMetre);

int entierAleatoire(int borne_min, int borne_max);

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
   
   const int FREQUENCE_METRE  =  10;
   
   const int ESPACE_CIRCUIT   =  0;
   
   
   int longueurCircuit;
   int amplitudeVirage;
   int largeurRoute;
   int largeurTotale;
   
   
   float espaceSymetrique;          // Espace à gauche et à droite de la route
   
   int espaceGauche;                // Espace à gauche de la route
   int espaceDroite;                // Espace à droite de la route
   int espaceMetre;                 // Espacement nécessaire pour afficher les mètres
   
   int amplitudeActuel;
   
   string route;
  
   
   //Iinitialisation du générateur aléatoire
   srand((unsigned)time(NULL));
   
   
   
   do{
      
      longueurCircuit  =  saisie(LONG_CIRC_MIN, LONG_CIRC_MAX, "Longueur Circuit [ 0 - 1000 ]: ");
      amplitudeVirage  =  saisie(AMPLI_MIN, AMPLI_MAX, "Amplitue [ 1 - 3 ] : ");
      largeurRoute     =  saisie(LARG_ROUTE_MIN, LARG_ROUTE_MAX, "Largueur Route [ 3 - 10 ] : ");
      largeurTotale    =  saisie(LARG_TOTALE_MIN, LARG_TOTALE_MAX, "Largeur Totale [ 20 - 50 ] : ");
      
      
      
      espaceSymetrique  =  (largeurTotale - largeurRoute)/2.0;
   
      espaceGauche      =  floor(espaceSymetrique);
      espaceDroite      =  ceil(espaceSymetrique);
   
      espaceMetre       =  floor(log10(longueurCircuit))+1;
      
      
      route  =  "";
   
      
      for(int segmentRoute = 1; segmentRoute <= largeurRoute; segmentRoute++){
         route += "=";
      }
   
      for(int etapeCircuit = LONG_CIRC_MIN; etapeCircuit <= longueurCircuit; etapeCircuit++){
      
         afficheCircuit(espaceGauche, espaceDroite, route, etapeCircuit,
                        ESPACE_CIRCUIT, espaceMetre, FREQUENCE_METRE);
      
         do{
            amplitudeActuel  = entierAleatoire(-amplitudeVirage, amplitudeVirage);
         }while(!(espaceGauche > -amplitudeActuel && espaceDroite > amplitudeActuel));
      
         espaceGauche += amplitudeActuel;
         espaceDroite -= amplitudeActuel;
      }
      
      
   }while(recommencer(OUI,NON)); 
   return EXIT_SUCCESS;
}




//===============================     texteSaise     ==============================//

string textSaisie(string texte, int borne_inf, int borne_sup, int espaceAlligne,
                  int espaceBorne){
   
   string textSaisie = texte;
   
   
   for(int espace = textSaisie.size(); espace <= espaceAlligne; espace ++){
      textSaisie += " ";
   }
   
   textSaisie += "[";
   
   
   string borne_inf_txt = "y";    //A remplacer par to_string(borne_inf);
   
   for(int espace = borne_inf_txt.size(); espace <= espaceBorne; espace++){
      textSaisie += " ";
   }
   
   textSaisie += (borne_inf_txt + " et ");
   
   
   string borne_sup_txt = "y";    //A remplacer par to_string(borne_sup);
   
   for(int espace = borne_sup_txt.size(); espace <= espaceBorne; espace++){
      textSaisie += " ";
   }
   
   textSaisie += (borne_sup_txt + "] : ");
   
   return textSaisie;
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

void afficheCircuit(int espaceGauche, int espaceDroite, string route, int etapeCircuit,
   int espaceCircuit, int espaceMetre, int frequenceMetre) {
   
   cout << setw(espaceCircuit) << "" << right << setw(espaceMetre);
      
   if(!(etapeCircuit % frequenceMetre)){
      cout << etapeCircuit;
   }
   cout << "" << "|" << setw(espaceGauche) << "" << route << setw(espaceDroite)<< "|"
        << endl;
}




//==========================       entierAleatoire        =========================//

int entierAleatoire(int borne_min, int borne_max){
   return (rand() % (borne_max - borne_min + 1)) + borne_min;
}




//============================       recommencer        ===========================//

bool recommencer(char OUI, char NON) {

   char recommencer;
   bool sortie;

   do {

      cout << "Voulez vous recommencer ? [" << OUI << "/" << NON << "] : ";
      cin  >> recommencer;
      VIDER_BUFFER;
      
      recommencer = toupper(recommencer);  //met le char entré en majuscule

      sortie = recommencer == OUI || recommencer == NON;

   } while (!sortie);

   return recommencer == OUI;
}