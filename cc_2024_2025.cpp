#include<iostream>
#include<array>
#include<string>
#include<fstream>

const int nbligne=6;
const int nbcolonne=6;
using ligne=std::array<char,nbcolonne>;
using plateau=std::array<ligne,nbligne>;

void initialisePlateau(plateau &P)
{
    for (int i=0; i<nbligne; i++)
        for (int j=0; j<nbcolonne; j++)
            P[i][j]=' ';
}

void placeVoiture(plateau &P)
{
  //voiture A
  P[0][3]='A';
  P[1][3]='A';
  P[2][3]='A';
  //voiture X
  P[2][0]='X';
  P[2][1]='X';
  //voiture  B
  P[3][0]='B';
  P[4][0]='B';
  P[5][0]='B';
  // voiture C
  P[3][1]='C';
  P[3][2]='C';
  P[3][3]='C';
}

void affiche(plateau &P)
{
    std::cout<<"   1 2 3 4 5 6"<<std::endl;
    for (int i=0; i<nbligne; i++)
        {
            std::cout<<"  -------------"<<std::endl;
            std::cout<<i+1<<" ";
        for (int j=0; j<nbcolonne; j++)
        {
            std::cout<<"|"<<P[i][j];
        }
        std::cout<<"|"<<std::endl;
        }
        std::cout<<"  -------------"<<std::endl;
}

void lirePlateau(plateau &P, std::string &ch)
{
    std::ifstream fic;
    fic.open(ch);
    if (fic.is_open())
        std::cout << "L'ouverture du fichier s'est bien passée." << std::endl;
    else
    std::cout << "L'ouverture du fichier a échouée." << std::endl;
    unsigned l,c;
    char s;
    while (fic.good()){
        fic>>l;
        fic>>c;
        fic>>s;
        P[l-1][c-1]=s;
    }
}




int main ()
{
    plateau P;
    initialisePlateau(P);
    affiche(P);
    //placeVoiture(P);
    std::string ch = "./plat1.txt";
    lirePlateau(P, ch);
    affiche(P);
    return 0;

}
