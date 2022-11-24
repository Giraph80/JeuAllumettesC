#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;


int game = 1;
int nb_allumettes, nb_allumettes_partie;
char nom[30], niv, prem[30], buffer[256], tour;


void parametre() {   //procédure d'initialisation des paramètres du jeu

    printf("\033c");    //fonction qui permet d'enlever le texte anciennement affiché dans la console
    cout << "Quel est votre nom ?\n";
    cin >> nom;
    cout << endl;
    printf("\033c");

    do {    //choix du niveau de l'ordinateur
        cout << "Choississez le niveau de l'ordinateur N pour naif ou E pour expert : \n";
        cin >> niv;
        if (niv != 'E' && niv != 'e' && niv != 'n' && niv != 'N') {
            cout << "Saisie incorrecte." << endl;
        }
    } while (niv != 'E' && niv != 'e' && niv != 'n' && niv != 'N');   //contrôle de saisie
    cout << endl;
    printf("\033c");

    if (niv == 'E' || niv == 'e') {
        niv = 1;  //définition du niveau de l'ordinateur à expert
    }
    else {
        niv = 0;  //définition du niveau de l'ordinateur à novice
    }


    do {    //choix du nombre d'allumettes dans la partie

        cout << "Choississez le nombre d'allumettes (entre 1 et 30): \n";
        cin >> buffer;
        nb_allumettes = atoi(buffer);
        nb_allumettes_partie = nb_allumettes;
        if (nb_allumettes == 0 || nb_allumettes < 1 || nb_allumettes>30) {
            cout << "Valeur incorrecte." << endl;
        }
    } while (nb_allumettes < 1 || nb_allumettes>30);
    cout << endl;

    do {    //le joueur choisi le premier à jouer entre l'ordinateur ou le joueur
        printf("\033c");
        cout << "Quel joueur commence ? " << nom << " ou Ordinateur ?\n";
        cin >> prem;
        if (strcmp(prem, nom) && strcmp(prem, "Ordinateur") && strcmp(prem, "ordinateur") && strcmp(prem, "ordi") && strcmp(prem, "o") && strcmp(prem, "O")) {
            cout << "Réponse invalide." << endl;
        }
    } while (strcmp(prem, nom) && strcmp(prem, "Ordinateur") && strcmp(prem, "ordinateur") && strcmp(prem, "ordi") && strcmp(prem, "o") && strcmp(prem, "O"));  //contrôle de saisie
    cout << endl;

    printf("\033c");
    cout << "Les paramètres de la partie sont définis, vous pouvez commencer à jouer :" << endl << endl;
    if (strcmp(prem, nom)) {
        tour = 1;
    }

    else {
        tour = 0;
    }
}




void restart() {     //procédure qui permet de relancer la partie à la fin de la précédente
    char rejouer, changerParametres;
    do {
        cout << "Voulez vous rejouer ? (o/n) : " << endl;   //le joueur choisi s'il veux relancer une partie
        cin >> rejouer;


    } while (rejouer != 'o' && rejouer != 'n');  //contrôle de saisie

    if (rejouer == 'o') {
        nb_allumettes = nb_allumettes_partie;

        do {
            cout << "Souhaitez rejouer avec les mêmes paramètres ? (o/n)" << endl;  //le joueur choisi s'il veut garder les mêmes paramètres que la partie précédente
            cin >> changerParametres;
        } while (changerParametres != 'o' && changerParametres != 'n');  //contrôle de saisie

        if (changerParametres == 'o') {    //relancer la partie
            game = 1; //la partie est lancée
        }
        else if (changerParametres == 'n') {   //ne relance pas la partie et met fin au programme
            game = 1;
            parametre();
        }
    }

    else {
        cout << "Merci d'avoir joué" << endl;
        tour = 3;
    }
}




void affichage(int nb_allumettes) {  //procédure qui permet d'afficher les allumettes tout au long de la partie
    int nb_lignes, i, j, derniere_ligne;
    if (nb_allumettes > 0) {

        nb_lignes = floor(nb_allumettes / 5);
        for (i = 1; i <= nb_lignes; i++) {
            for (j = 1; j <= 5; j++) {
                cout << " ! ";
            }
            cout << endl;
        }

        for (derniere_ligne = 1; derniere_ligne <= nb_allumettes % 5; derniere_ligne++) {
            cout << " ! ";
        }
    }

    if (nb_allumettes == 0) {  //contrôle du vainqueur de la partie lorsque qu'il ne reste plus aucune allumette
        game = 0; //la partie se termine
        cout << "La partie est terminée." << endl;

        if (tour == 0) {
            cout << nom << " a gagné la partie." << endl;
        }

        if (tour == 1) {
            cout << "L'ordinateur a gagné la partie." << endl;
        }
        restart();
    }
    cout << endl;
}




void tourOrdinateur() {  //procédure définissant les actions de l'ordinateur lors de son tour
    int choix_allumettes;

    cout << "C'est à l'ordinateur de jouer." << endl << endl;
    usleep(2500000);    //définition d'un délai d'action pour l'ordinateur
    printf("\033c");
    if (niv == 0) {    //
        do {
            choix_allumettes = rand() % 3 + 1;
        }


        while (choix_allumettes > nb_allumettes);
        cout << "L'ordinateur a enlevé " << choix_allumettes << " allumettes." << endl << endl;


    }

    if (niv == 1) { //expert
        if (nb_allumettes % 4 > 1) {
            choix_allumettes = nb_allumettes % 4 - 1;

        }
        else if (nb_allumettes % 4 == 0) {
            choix_allumettes = 3;
        }
        else {
            choix_allumettes = rand() % 3 + 1;

        }
    }
    cout << "L'ordinateur a enlevé " << choix_allumettes << " allumettes." << endl << endl;
    nb_allumettes = nb_allumettes - choix_allumettes;
    tour = 0;


}

void tourJoueur() {  //procédure définissant le tour du joueur et controlant ses saisies
    cout << "C'est à " << nom << " de jouer." << endl << endl;
    int choix_allumettes;
    char repAbandon;
    do {
        cout << "Entrez le nombre d'allumettes que vous souhaitez enlever : " << endl;
        cin >> choix_allumettes;
        if (choix_allumettes < 0 || choix_allumettes>3 || choix_allumettes > nb_allumettes) {
            cout << "valeur incorrecte" << endl;
        }
        if (choix_allumettes == 0) {
            do {



                cout << "Confirmez-vous l'abandon (o/n) ?" << endl;
                cin >> repAbandon;
                if (repAbandon == 'o') {
                    game = 0;
                    restart();
                }

            } while (repAbandon != 'o' && repAbandon != 'n');
            //else if (repAbandon=='n'{
               // restart
            //}

        }
    } while (choix_allumettes > 3 || choix_allumettes > nb_allumettes || choix_allumettes <= 0);   //contrôle de saisie

    printf("\033c");
    cout << endl;
    nb_allumettes = nb_allumettes - choix_allumettes;
    tour = 1;

}





void jeualterne(int tour) { //procédure d'alternance entre le joueur et l'odinateur
    if (tour == 0) {
        tourJoueur();
    }
    if (tour == 1) {
        tourOrdinateur();
    }
}




int main()
{

    parametre();


    while (game == 1) { // boucle principale du jeu.
        affichage(nb_allumettes);
        jeualterne(tour);

    }

    return 0;
}



