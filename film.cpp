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

        fic >> E.nbfilms;
        fic.ignore(); 
        E.T = new film[E.nbfilms];

        std::string line;
        for(int i = 0; i < E.nbfilms; i++){
            //pour le titre 
            std::getline(fic,line); // permet de récupérer la ligne
            E.T[i].titre = line;
            //std::cout << E.T[i].titre << std::endl;

            //pour l'année 
            fic >> E.T[i].annee;
            fic.ignore();
            //std::cout << E.T[i].annee << std::endl;

            //pour le réalisateur
            std::getline(fic,line); // permet de récupérer la ligne
            E.T[i].realisateur = line;
            //std::cout << E.T[i].realisateur << std::endl;

            //pour la durée 
            fic >> E.T[i].duree;
            fic.ignore();
            //std::cout << E.T[i].duree << std::endl;

            //pour la langue
            std::getline(fic,line); // permet de récupérer la ligne
            E.T[i].langue = line;
            //std::cout << E.T[i].langue << std::endl;

            //break;

        }



        fic.close();  // Close the file after reading
    } else {
        std::cout << "L'ouverture du fic a échouée." << std::endl;
        E.nbfilms = 0; 
        E.T = nullptr;
    }
}





int main(){

    std::string path = "./film.txt"; 
    ensemble E;

    importer(path, E);
        
    return 0;
}