#include <iostream>
#include <fstream> //to read and write in a file 
#include <string>
#include <typeinfo>  // Required for typeid

//Q1
// Define a structure to store information about a film
struct film { 
    std::string titre;        // The title of the film
    std::string langue;       // The language in which the film is produced
    std::string realisateur;  // The director of the film
    int annee;                // The release year of the film
    int duree;                // The duration of the film in minutes
};

// Define a structure to store a collection of films
struct ensemble { 
    film * T;       // Pointer to an array of `film` objects (dynamic array of films)
    int nbfilms;   // Number of films currently stored in the array
    // `T` will be dynamically allocated with `new film[...]` to store multiple films.
    // The `nbfilms` keeps track of how many films are currently in the collection.
};

// Define a structure for a selection (subset) of films
struct selection { 
    film * *T;      // Pointer to an array of pointers to `film` objects
                   // Each pointer in the array points to a specific `film` object.
    int nbfilms;   // Number of films included in the selection

    // This structure allows for creating subsets or filtered lists of films
    // without duplicating the actual film objects.
    // For example, we can select films of a certain genre or by a specific director
    // and store only the references (pointers) to the films we want.
};

//Q2
// Function to read films from a file and store them in the ensemble
void importer(std::string path, ensemble& E) {
    std::ifstream fic;  // Input file stream to read the file

    fic.open(path);
    if (fic.is_open()){
        std::cout << "L'ouverture du fic s'est bien passée." << std::endl;

        // Read the number of films (first line of the file)
        //std::cout << "Type of fic: " << typeid(fic).name() << std::endl;
        fic >> E.nbfilms;
        fic.ignore();  // Ignore the newline after the number of films

        // Dynamically allocate memory for the array of films
        E.T = new film[E.nbfilms];

        std::string ligne;

        for (int i = 0; i < E.nbfilms;i++){
            std::getline(fic,ligne); 
            E.T[i].titre = ligne;
			fic >> E.T[i].annee; 
            fic.ignore();
			std::getline(fic,ligne); 
            E.T[i].realisateur = ligne;
			fic >> E.T[i].duree; 
            fic.ignore();
			std::getline(fic,ligne); 
            E.T[i].langue = ligne;   
        }
        fic.close();  // Close the file after reading
    } else {
        std::cout << "L'ouverture du fic a échouée." << std::endl;
        E.nbfilms = 0; 
        E.T = nullptr;
    }
}

//Q3
// Function to display information about all films in the ensemble
void afficher_films(ensemble & E) {
    for (int i = 0; i < E.nbfilms; ++i) {
        std::cout << "Film #" << (i + 1) << ":" << std::endl;
        std::cout << "  Titre: " << E.T[i].titre << std::endl;
        std::cout << "  Année: " << E.T[i].annee << std::endl;
        std::cout << "  Réalisateur: " << E.T[i].realisateur << std::endl;
        std::cout << "  Durée: " << E.T[i].duree << " min" << std::endl;
        std::cout << "  Langue: " << E.T[i].langue << std::endl;
        std::cout << std::endl;
    }
}


//Q4
// Function to construct a selection containing all films from an ensemble
void construire_selection(ensemble& E, selection& S) {
    // Set the number of films in the selection to be the same as in the ensemble
    S.nbfilms = E.nbfilms;

    // Dynamically allocate memory for the array of pointers to films
    S.T = new film*[S.nbfilms];
    // Assign pointers in the selection to point to the corresponding films in the ensemble
    for (int i = 0; i < S.nbfilms; ++i) {
        S.T[i] = &E.T[i];
    }
}


//Q6
// Function to display the films in a selection
void afficher_selection(const selection& S) {
    for (int i = 0; i < S.nbfilms; ++i) {
        std::cout << "Film #" << (i + 1) << ":" << std::endl;
        std::cout << "  Titre: " << S.T[i]->titre << std::endl;
        std::cout << "  Année: " << S.T[i]->annee << std::endl;
        std::cout << "  Réalisateur: " << S.T[i]->realisateur << std::endl;
        std::cout << "  Durée: " << S.T[i]->duree << " min" << std::endl;
        std::cout << "  Langue: " << S.T[i]->langue << std::endl;
        std::cout << std::endl;
    }
}

//Q5
void selectionPersonnalisee (ensemble & E, selection & S, std::string real,const int anneemin, const int anneemax){
    S.nbfilms = 0;
	for (int i = 0; i < E.nbfilms; ++i){
        if ((E.T[i].realisateur == real) && (anneemin <= E.T[i].annee) && (anneemax >= E.T[i].annee)){
            S.nbfilms ++;
            }
    S.T = new film*[S.nbfilms];
    int j = 0;
    if(S.nbfilms >0 ){
        for (int i = 0; i < E.nbfilms; ++i){
        if ((E.T[i].realisateur == real) && (anneemin <= E.T[i].annee) && (anneemax >= E.T[i].annee)){
            S.T[j] = &E.T[i];
            j++;
            }
        }
    }else{S.T = nullptr;}
    
    }
    std::cout << S.nbfilms << std::endl;
}



int main(){

    std::string path = "./film.txt"; 

    ensemble E;

    importer(path, E);

    // Display the films
    afficher_films(E);

    // Create a selection containing all films
    selection S;
    construire_selection(E, S);

    /*std::cout << "Type of E.T: " << typeid(E.T).name() << std::endl;
    std::cout << "E.T = " << E.T << std::endl;
    std::cout << "Type of E.T[0]: " << typeid(E.T[0]).name() << std::endl;
    std::cout << "E.T[0].titre = " << E.T[0].titre << std::endl;
    std::cout << "E.T[1].titre = " << E.T[1].titre << std::endl;
    std::cout << std::endl;


    std::cout << "Type of S.T: " << typeid(S.T).name() << std::endl;
    std::cout << "S.T = " << S.T << std::endl;
    std::cout << "Type of S.T[0]: " << typeid(S.T[0]).name() << std::endl;
    std::cout << "S.T[0] = " << S.T[0] << std::endl;
    std::cout << "S.T[0]->titre = " << S.T[0]->titre << std::endl;
    std::cout << "Type of S.T[1]: " << typeid(S.T[1]).name() << std::endl;
    std::cout << "S.T[1] = " << S.T[1] << std::endl;
    std::cout << "S.T[1]->titre = " << S.T[1]->titre << std::endl;
    */

    // Display the films in the selection
    //std::cout << "\nSélection des films (tous les films de l'ensemble) :\n";
    //afficher_selection(S);

    selection MyS;
    std::string real = "Quentin Tarantino";
    int anneemin = 1800;
    int anneemax = 2025; 

    std::cout << "\nSélection personnalisée :\n";
    selectionPersonnalisee(E, MyS, real, anneemin, anneemax);
    afficher_selection(MyS);

    // Clean up dynamically allocated memory
    delete[] E.T;
    delete[] S.T;
    delete[] MyS.T;

        
    return 0;
}