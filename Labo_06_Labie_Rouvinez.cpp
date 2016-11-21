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

//Méthode permettant de vider le Buffer
#define VIDER_BUFFER while(cin.get() != '\n')

using namespace std;


int saisie(int borne_inf, int borne_sup, string textSaisie);

bool recommencer(char OUI, char NON);


int main() {

   
   
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


//============================       recommencer        ===========================//

bool recommencer(char OUI, char NON) {

   char recommencer;
   bool sortie;

   do {

      cout << "Voulez vous recommencer ? [" << OUI << "/" << NON << "] : ";
      cin >> recommencer;
      VIDER_BUFFER;

      sortie = recommencer == OUI || recommencer == NON;

   } while (!sortie);

   return recommencer == OUI;
}