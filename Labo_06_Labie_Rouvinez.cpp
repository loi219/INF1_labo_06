/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 06 Circuit
 Fichier     : Labo_06_Labie_Rouvinez.cpp
 Auteur(s)   : Marc Labie & Sven Rouvinez
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

//Valide l'entrée de l'utilisateur
string texteSaisie(string texte, int borne_inf, int borne_sup, int espaceAlligne,
                  int espaceBorne);

//Retourne la saisie de l'utilisteur si elle est valide
int saisie(int borne_inf, int borne_sup, string textSaisie);

//Affiche le circuit
void afficheCircuit(int espaceGauche, int espaceDroite, string route, int etapeCircuit,
                    int espaceCircuit, int espaceMetre, int frequenceMetre);

//Retourne un entier aléatoire dans un intervalle
int entierAleatoire(int borne_min, int borne_max);

//Demande à l'utilisateur s'il souhaite recommencer
bool recommencer(char OUI, char NON);


int main() {

   //Définition des constantes
   const char OUI = 'O';
   const char NON = 'N';

   const int LONG_CIRC_MIN = 0;
   const int LONG_CIRC_MAX = 1000;

   const int AMPLI_MIN = 1;
   const int AMPLI_MAX = 3;

   const int LARG_ROUTE_MIN = 3;
   const int LARG_ROUTE_MAX = 10;

   const int LARG_TOTALE_MIN = 20;
   const int LARG_TOTALE_MAX = 50;

   const int FREQUENCE_METRE = 10;

   const int ESPACE_CIRCUIT = 0;

   //Définition des variables
   int longueurCircuit;
   int amplitudeVirage;
   int largeurRoute;
   int largeurTotale;


   float espaceSymetrique; // Espace à gauche et à droite de la route

   int espaceGauche; // Espace à gauche de la route
   int espaceDroite; // Espace à droite de la route
   int espaceMetre; // Espacement nécessaire pour afficher les mètres

   int amplitudeActuel;

   string route;


   //Iinitialisation du générateur aléatoire
   srand((unsigned) time(NULL));


   do {


      longueurCircuit = saisie(LONG_CIRC_MIN, LONG_CIRC_MAX, texteSaisie("Longueur du Circuit", LONG_CIRC_MIN, LONG_CIRC_MAX, 25, 5));
      amplitudeVirage = saisie(AMPLI_MIN, AMPLI_MAX, texteSaisie("Amplitude max des virages", AMPLI_MIN, AMPLI_MAX, 25, 5));
      largeurRoute = saisie(LARG_ROUTE_MIN, LARG_ROUTE_MAX, texteSaisie("Largeur de la route", LARG_ROUTE_MIN, LARG_ROUTE_MAX, 25, 5));

      /*amplitudeVirage = saisie(AMPLI_MIN, AMPLI_MAX, "Amplitue [ " +to_string(AMPLI_MIN)+ " - " +to_string(AMPLI_MAX)+" ] : ");
      largeurRoute = saisie(LARG_ROUTE_MIN, LARG_ROUTE_MAX, "Largueur Route [ "+to_string(LARG_ROUTE_MIN)+  " - " +to_string(LARG_ROUTE_MAX)+  " ] : ");
      largeurTotale = saisie(LARG_TOTALE_MIN, LARG_TOTALE_MAX, "Largeur Totale [ " +to_string(LARG_TOTALE_MIN)+ " - " +to_string(LARG_TOTALE_MAX)+  " ] : ");*/

      //Divise la route en 2 afin de pouvoir fixer l'espace à gauche et droite
      espaceSymetrique = (largeurTotale - largeurRoute) / 2.0;

      //Défini les espaces
      espaceGauche = floor(espaceSymetrique);
      espaceDroite = ceil(espaceSymetrique);

      //Permet de trouver le nombre de chiffre à chaque fois qu'on affiche une borne et défini l'espace selon
      espaceMetre = floor(log10(longueurCircuit)) + 1;



      //Affiche le circuit
      route = "";
      for (int segmentRoute = 1; segmentRoute <= largeurRoute; segmentRoute++) {
         route += "=";
      }

      for (int etapeCircuit = LONG_CIRC_MIN; etapeCircuit <= longueurCircuit; etapeCircuit++) {

         afficheCircuit(espaceGauche, espaceDroite, route, etapeCircuit,
                 ESPACE_CIRCUIT, espaceMetre, FREQUENCE_METRE);

         do {
            amplitudeActuel = entierAleatoire(-amplitudeVirage, amplitudeVirage);
         } while (!(espaceGauche > -amplitudeActuel && espaceDroite > amplitudeActuel));

         espaceGauche += amplitudeActuel;
         espaceDroite -= amplitudeActuel;
      }


   } while (recommencer(OUI, NON));
   return EXIT_SUCCESS;
}




//===============================     texteSaise     ==============================//

string texteSaisie(string texte, int borne_inf, int borne_sup, int espaceAlligne,
                  int espaceBorne) {

	string texteSaisie = texte;


	for (int espace = texteSaisie.size(); espace <= espaceAlligne; espace++) {
		texteSaisie += " ";
	}

	texteSaisie += "[";


	string borne_inf_txt = "y";    //A remplacer par to_string(borne_inf);

	for (int espace = borne_inf_txt.size(); espace <= espaceBorne; espace++) {
		texteSaisie += " ";
	}

	texteSaisie += (borne_inf_txt + " et ");


	string borne_sup_txt = "y";    //A remplacer par to_string(borne_sup);

	for (int espace = borne_sup_txt.size(); espace <= espaceBorne; espace++) {
		texteSaisie += " ";
	}

	texteSaisie += (borne_sup_txt + "] : ");

	return texteSaisie;
}




//=================================     saisie     ================================//

int saisie(int borne_inf, int borne_sup, string textSaisie) {

	int val;
	bool cinFail;

	do {

		cinFail = false;

		cout << textSaisie;
		cin >> val;

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

	//Affiche les bornes métriques
	cout << setw(espaceCircuit) << "" << right << setw(espaceMetre);

	if (!(etapeCircuit % frequenceMetre)) {
		cout << etapeCircuit;
	}
	//Affiche les "pipe" sur le côté
	cout << "" << "|" << setw(espaceGauche) << "" << route << setw(espaceDroite) << "|"
	     << endl;
}




//==========================       entierAleatoire        =========================//

int entierAleatoire(int borne_min, int borne_max) {
	//le % permet de retourner trouver un intervalle
	return (rand() % (borne_max - borne_min + 1)) + borne_min;
}




//============================       recommencer        ===========================//

bool recommencer(char OUI, char NON) {

	char recommencer;
	bool sortie;

	do {

		cout << "Voulez vous recommencer ? [" << OUI << "/" << NON << "] : ";
		cin >> recommencer;
		VIDER_BUFFER;

		recommencer = (char)toupper(recommencer);  //met le char entré en majuscule, cast car toupper retourne un int

		sortie = recommencer == OUI || recommencer == NON;

	} while (!sortie);

	return recommencer == OUI;
}
