/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 06 Circuit
 Fichier     : Labo_06_Labie_Rouvinez.cpp
 Auteur(s)   : Marc Labie & Sven Rouvinez
 Date        : 28.11.2016

 But         : 1. Demande à l'utilisateur et saisit une longueur de circuit, une amplitude
 *                de virage, une largeur de route, ainsi qu'une largeur du circuit, toutes
 *                devant être comprises dans un intervalle prédéfinis.
 *                Si une valeure saisie n'est pas comprises dans les bornes exigée,
 *                demande à l'utilisateur de saisir à nouveau cette dernière.
 *             2. Génère et affiche un circuit aléatoire à partir des valeurs saisies.
 *                une borne numérique indique la progression du circuit une fois chaque
 *                10 mètres.
 *             3. Propose à l'utilsateur de recommencer l'opération. S'il accèpte, 
 *                recommence à partir du point de saisie. Sinon, quitte le programme.

 Remarque(s) : -

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




//=================================================================================//
//======================<     Déclaration des prototypes     >=====================//
//=================================================================================//


//Affiche le circuit
void afficheCircuit(int espaceGauche, int espaceDroite, const string& route,
                    int etapeCircuit, int espaceCircuit, int espaceMetre,
                    int frequenceMetre);


// Fonction qui permet de générer un texte de saisie pour la fonction saisie().
string aligneTexte(const string& texte, const int borneInf, const int borneSup,
                   const int espaceAligne, const int espaceBorne);


//calcul le nombre de chiffres dans un nombre
int enumerationChiffre(const int nombre);


// Fonction qui demande à l'utilisateur d'entrée une valeur comprise dans les bornes
// données en paramètres et la retourne.
int saisie(const int borneInf, const int borneSup, const string& textSaisie);


// Permet d'afficher le circuit
void afficheCircuit(const int espaceGauche, const int espaceDroite, const string& route, 
                    const int etapeCircuit, const int espaceCircuit, const int espaceMetre,
                    const int frequenceMetre);


// Retourne un entier aléatoire dans un intervalle compris entre les bornes données en
// paramètre.
int entierAleatoire(const int borneInf, const int borneSup);


// Demande à l'utilisateur s'il souhaite recommencer, retourne vrai si oui, faux sinon.
bool recommencer(const char OUI, const char NON);





//=================================================================================//
//===============================<       main      >===============================//
//=================================================================================//


int main() {

   
   
   /*------------------------------------------------------------------------------*/
   /*---------------------     Déclaration des constantes     ---------------------*/
   /*------------------------------------------------------------------------------*/
   
   
   const char OUI  =  'O';
   const char NON  =  'N';

   const int LONG_CIRC_MIN  =     0;
   const int LONG_CIRC_MAX  =  1000;

   const int AMPLI_MIN  =  1;
   const int AMPLI_MAX  =  3;

   const int LARG_ROUTE_MIN  =   3;
   const int LARG_ROUTE_MAX  =  10;

   const int LARG_TOTALE_MIN  =  20;
   const int LARG_TOTALE_MAX  =  50;

   const int FREQUENCE_METRE  =  10;

   const int ESPACE_CIRCUIT  =  0;
   
   const int ESPACE_TEXTE_SAISIE  =  25;
   const int ESPACE_BORNE_SAISIE  =   5;

   
   
   
   /*------------------------------------------------------------------------------*/
   /*---------------------     Déclaration des variables     ----------------------*/
   /*------------------------------------------------------------------------------*/
   
   
   int longueurCircuit;
   int amplitudeVirage;
   int largeurRoute;
   int largeurTotale;

   float espaceSymetrique;       // Espace à gauche et à droite de la route

   int espaceGauche;             // Espace à gauche de la route
   int espaceDroite;             // Espace à droite de la route
   int espaceMetre;              // Espacement nécessaire pour afficher les mètres
   
   int amplitudeActuel;
   
   string route;

   
   

   do { /*----------------------     Boucle Recommencer     -----------------------*/
      
      
      
      /*---------------------------------------------------------------------------*/
      /*-----------------------     Saisie des Valeurs     ------------------------*/
      /*---------------------------------------------------------------------------*/
      

      longueurCircuit  =  saisie(LONG_CIRC_MIN,
                                 LONG_CIRC_MAX,
                                 aligneTexte("Longueur du Circuit",
                                             LONG_CIRC_MIN,
                                             LONG_CIRC_MAX,
                                             ESPACE_TEXTE_SAISIE,
                                             ESPACE_BORNE_SAISIE));
      
      
      amplitudeVirage  =  saisie(AMPLI_MIN,
                                 AMPLI_MAX, 
                                 aligneTexte("Amplitude max des virages",
                                             AMPLI_MIN,
                                             AMPLI_MAX,
                                             ESPACE_TEXTE_SAISIE,
                                             ESPACE_BORNE_SAISIE));
      
      
      largeurRoute     =  saisie(LARG_ROUTE_MIN,
                                 LARG_ROUTE_MAX,
                                 aligneTexte("Largeur de la route",
                                             LARG_ROUTE_MIN,
                                             LARG_ROUTE_MAX,
                                             ESPACE_TEXTE_SAISIE,
                                             ESPACE_BORNE_SAISIE));
      
      
      largeurTotale    =  saisie(LARG_TOTALE_MIN,
                                 LARG_TOTALE_MAX,
                                 aligneTexte("Largeur Totale",
                                             LARG_TOTALE_MIN,
                                             LARG_TOTALE_MAX,
                                             ESPACE_TEXTE_SAISIE,
                                             ESPACE_BORNE_SAISIE));
      
      
      
      
      /*---------------------------------------------------------------------------*/
      /*-------------------    Initialisation des espacement    -------------------*/
      /*---------------------------------------------------------------------------*/
      
      
      //Divise la route en 2 afin de pouvoir fixer l'espace à gauche et droite
      espaceSymetrique = (largeurTotale - largeurRoute) / 2.0f;

      
      //Défini les espaces
      espaceGauche = floor(espaceSymetrique);
      espaceDroite = ceil(espaceSymetrique);

      
      //Défini l'espacement nécessaire pour afficher des bordures de routes alignées.
      espaceMetre = enumerationChiffre(longueurCircuit);
      
      
      
      
      
      /*---------------------------------------------------------------------------*/
      /*-----------------------    Création de la route    ------------------------*/
      /*---------------------------------------------------------------------------*/
      
      route = "";
      
      for (int segmentRoute = 1; segmentRoute <= largeurRoute; segmentRoute++) {
         route += "=";
      }
      
      
      
      
      /*---------------------------------------------------------------------------*/
      /*-----------------------    Affichage du Circuit    ------------------------*/
      /*---------------------------------------------------------------------------*/
      
      
      for (int etapeCircuit = LONG_CIRC_MIN; etapeCircuit <= longueurCircuit; etapeCircuit++) {

         afficheCircuit(espaceGauche, espaceDroite, route, etapeCircuit,
                        ESPACE_CIRCUIT, espaceMetre, FREQUENCE_METRE);

         //Génère une amplitude de virage aléatoire tant que les les bordures de route
         //sont respectées.
         do {
            amplitudeActuel = entierAleatoire(-amplitudeVirage, amplitudeVirage);
         } while (!(espaceGauche > -amplitudeActuel && espaceDroite > amplitudeActuel));

	 espaceGauche += amplitudeActuel;
	 espaceDroite -= amplitudeActuel;
      }
      
   } while (recommencer(OUI, NON));
   
   return EXIT_SUCCESS;
}




//=================================================================================//
//==============================<     texteSaise     >=============================//
//=================================================================================//


string aligneTexte(const string& texte, const int borneInf, const int borneSup,
                   const int espaceAligne, const int espaceBorne) {

   int espace;
   string texteSaisie = texte;
   
   //Ajoute un nombre d'espace nécessaire pour que les ":" de chaques saisies soient
   //alignés.
   for (espace = texte.size(); espace <= espaceAligne; espace++) {
      texteSaisie += " ";
   }

   texteSaisie += "[";


   string borneInfToStr = "y"; //A remplacer par to_string(borne_inf);
   //string borneInfToStr = to_string(borneInf);

   for (espace = borneInfToStr.size(); espace <= espaceBorne; espace++) {
      texteSaisie += " ";
   }

   texteSaisie += (borneInfToStr + " et ");


   string borneSupToStr = "y"; //A remplacer par to_string(borne_sup);
   //string borneSupToStr = to_string(borneSup);

   for (espace = borneSupToStr.size(); espace <= espaceBorne; espace++) {
      texteSaisie += " ";
   }

   texteSaisie += (borneSupToStr + "] : ");

   return texteSaisie;
}



//=================================================================================//
//================================<     saisie     >===============================//
//=================================================================================//


int saisie(const int borneInf, const int borneSup, const string& textSaisie) {

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

   } while (val < borneInf || val > borneSup || cinFail);

   return val;
}





//=================================================================================//
//==========================<       nombreChiffre        >=========================//
//=================================================================================//


int enumerationChiffre(const int nombre) {

	return floor(log10(nombre)) + 1;

}




//=================================================================================//
//===========================<      afficheCircuit      >==========================//
//=================================================================================//


void afficheCircuit(const int espaceGauche, const int espaceDroite, const string& route,
                    const int etapeCircuit, const int espaceCircuit, const int espaceMetre,
                    const int frequenceMetre) {

   //Affiche les bornes métriques
   cout << setw(espaceCircuit) << "" << right << setw(espaceMetre);

   if (!(etapeCircuit % frequenceMetre)) {
      cout << etapeCircuit;
   }
   
   //Affiche les "pipe" sur le côté
   cout << "" << "|" << setw(espaceGauche) << "" << route << setw(espaceDroite) << "|"
        << endl;
}




//=================================================================================//
//=========================<       entierAleatoire        >========================//
//=================================================================================//


int entierAleatoire(const int borneInf, const int borneSup) {
   
   static bool initRand = true;
   
   if(initRand){
       
      //Iinitialisation du générateur aléatoire 
      srand((unsigned) time(NULL));

      initRand = false;
   }
   //le % permet de retourner trouver un intervalle
   return (rand() % (borneSup - borneInf + 1)) +borneInf;
}




//=================================================================================//
//===========================<       recommencer        >==========================//
//=================================================================================//


bool recommencer(const char OUI, const char NON) {

   char recommencer;
   bool sortie;

   do {

      cout << "Voulez vous recommencer ? [" << OUI << "/" << NON << "] : ";
      cin  >> recommencer;
      VIDER_BUFFER;

      recommencer = (char) toupper(recommencer);

      sortie = recommencer == OUI || recommencer == NON;

   } while (!sortie);

   return recommencer == OUI;
}