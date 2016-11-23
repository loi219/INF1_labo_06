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
string aligneTexte(const string& texte, int borneMin, int borneMax, int espaceAligne,
                   int espaceBorne);

//Retourne la saisie de l'utilisteur si elle est valide
int saisie(int borneMin, int borneMax, string textSaisie);

//Affiche le circuit
void afficheCircuit(int espaceGauche, int espaceDroite, const string& route, int etapeCircuit,
                    int espaceCircuit, int espaceMetre, int frequenceMetre);

//Retourne un entier aléatoire dans un intervalle
int entierAleatoire(int borneMin, int borneMax);

//Demande à l'utilisateur s'il souhaite recommencer
bool recommencer(char OUI, char NON);

//calcul le nombre de chiffres dans un nombre
int nombreChiffre(int nombre);

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

	//frequence d'affichage de la borne
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

	int amplitudeActuel = 0;

	string route;

	//Iinitialisation du générateur aléatoire
	srand((unsigned) time(NULL));


	do {


		longueurCircuit = saisie(LONG_CIRC_MIN, LONG_CIRC_MAX,
		                         aligneTexte("Longueur du Circuit", LONG_CIRC_MIN, LONG_CIRC_MAX, 25, 5));
		amplitudeVirage = saisie(AMPLI_MIN, AMPLI_MAX,
		                         aligneTexte("Amplitude max des virages", AMPLI_MIN, AMPLI_MAX, 25, 5));
		largeurRoute = saisie(LARG_ROUTE_MIN, LARG_ROUTE_MAX,
		                      aligneTexte("Largeur de la route", LARG_ROUTE_MIN, LARG_ROUTE_MAX, 25, 5));

		/*amplitudeVirage = saisie(AMPLI_MIN, AMPLI_MAX, "Amplitue [ " +to_string(AMPLI_MIN)+ " - " +to_string(AMPLI_MAX)+" ] : ");
		largeurRoute = saisie(LARG_ROUTE_MIN, LARG_ROUTE_MAX, "Largueur Route [ "+to_string(LARG_ROUTE_MIN)+  " - " +to_string(LARG_ROUTE_MAX)+  " ] : ");
		largeurTotale = saisie(LARG_TOTALE_MIN, LARG_TOTALE_MAX, "Largeur Totale [ " +to_string(LARG_TOTALE_MIN)+ " - " +to_string(LARG_TOTALE_MAX)+  " ] : ");*/

		//Divise la route en 2 afin de pouvoir fixer l'espace à gauche et droite
		espaceSymetrique = ((float) largeurTotale - (float) largeurRoute) / float(2.0);

		//Défini les espaces
		espaceGauche = (int) floor(espaceSymetrique);
		espaceDroite = (int) ceil(espaceSymetrique);

		//Permet de trouver le nombre de chiffre à chaque fois qu'on affiche une borne et défini l'espace selon
		espaceMetre = nombreChiffre(longueurCircuit);


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

string aligneTexte(const string& texte, int borneMin, int borneMax, int espaceAligne,
                   int espaceBorne) {

	string texteSaisie = texte;


	//int espacement = textLen - espaceAligne;

	for (int espace = (int) texteSaisie.size(); espace <= espaceAligne; espace++) {
		texteSaisie += " ";
	}

	texteSaisie += " :[";


	//string borneInfToStr = "y";    //A remplacer par to_string(borneMin);
	string borneInfToStr = to_string(borneMin);

	for (int espace = (int) borneInfToStr.size(); espace <= espaceBorne; espace++) {
		texteSaisie += " ";
	}

	texteSaisie += (borneInfToStr + " et ");


	//string borneMaxToStr = "y";    //A remplacer par to_string(borneMax);
	string borneMaxToStr = to_string(borneMax);
	for (int espace = (int) borneMaxToStr.size(); espace <= espaceBorne; espace++) {
		texteSaisie += " ";
	}

	texteSaisie += (borneMaxToStr + "] : ");

	return texteSaisie;
}




//=================================     saisie     ================================//

int saisie(int borneMin, int borneMax, string textSaisie) {

	const string ERREUR_ENTIER = "Veuillez entrer un entier";
	const string ERREUR_BORNE = "Veuillez entrer une valeur dans l'intervalle";

	int val;
	bool cinFail;

	do {

		cinFail = false;

		cout << textSaisie;
		cin >> val;

		//répare le buffer en cas de nécessité
		if (cin.fail()) {
			cout << ERREUR_ENTIER << endl;
			cinFail = true;
			cin.clear();
		} else if (val < borneMin || val > borneMax) {
			cout << ERREUR_BORNE << endl;
			cinFail = true;
		}
		VIDER_BUFFER;

	} while (cinFail);

	return val;
}




//============================      AfficheCircuit      ===========================//

void afficheCircuit(int espaceGauche, int espaceDroite, const string& route, int etapeCircuit,
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

int entierAleatoire(int borneMin, int borneMax) {
	//le % permet de retourner trouver un intervalle
	return (rand() % (borneMax - borneMin + 1)) + borneMin;
}




//============================       recommencer        ===========================//

bool recommencer(char OUI, char NON) {

	char recommencer;
	bool sortie;

	do {

		cout << "Voulez vous recommencer ? [" << OUI << "/" << NON << "] : ";
		cin >> recommencer;
		VIDER_BUFFER;

		recommencer = (char) toupper(recommencer);  //met le char entré en majuscule, cast car toupper retourne un int

		sortie = recommencer == OUI || recommencer == NON;

	} while (!sortie);

	return recommencer == OUI;
}

int nombreChiffre(int nombre) {

	return floor(log10(nombre)) + 1;

}