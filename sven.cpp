/*
 -----------------------------------------------------------------------------------
 Laboratoire : <nn>
 Fichier     : <nom du fichier>.cpp
 Auteur(s)   : <prénom> <nom>
 Date        : <jj.mm.aaaa>

 But         : <à compléter>

 Remarque(s) :
               La route est initialement positionnée au milieu de la largeur totale
               Une borne numérique indiquera tous les 10 mètres.
               La route est en tout temps comprise à l’intérieur de la largeur totale et conserve sa largeur.
               En cas d’erreur de saisie, le programme doit offrir la possibilité de recommencer en indiquant clairement les valeurs possibles.
               En fin de programme, l’utilisateur a le choix de quitter ou de recommencer le programme.

 Compilateur : MinGW-g++ 4.8.1
 -----------------------------------------------------------------------------------
 */


#include <cstdlib>
#include <iostream>
#include <ctime>
#include <limits>
#include <cmath>


//Méthode permettant de vider le Buffer
#define VIDER_BUFFER while(cin.get() != '\n')

using namespace std;


int saisie(int borneMin, int borneMax, string textSaisie);

bool recommencer(char OUI, char NON);

int calculAleatoire(const int maxValue);


int main() {

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


	int longueurCircuit;
	int amplituteVirage;
	int largeurRoute;
	int largeurTotale;

	do {


		longueurCircuit = saisie(LONG_CIRC_MIN, LONG_CIRC_MAX, "Longueur Circuit [ 0 - 1000 ]: ");
		amplituteVirage = saisie(AMPLI_MIN, AMPLI_MAX, "Amplitue [ 1 - 3 ] : ");
		largeurRoute = saisie(LARG_ROUTE_MIN, LARG_ROUTE_MAX, "Largueur Route [ 3 - 10 ] : ");
		largeurTotale = saisie(LARG_TOTALE_MIN, LARG_TOTALE_MAX, "Largeur Totale [ 20 - 50 ] : ");


	} while (recommencer(OUI, NON));


	return EXIT_SUCCESS;
}


//=================================     saisie     ================================//


int calculAleatoire(const int maxValue) {
	srand(time(0)); //use current time as seed for random generator

	int random_variable = rand();

	std::cout << "Random value on [0 " << maxValue << "]: "
	          << random_variable << '\n';

}

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