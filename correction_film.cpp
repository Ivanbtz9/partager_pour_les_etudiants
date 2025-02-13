#include <iostream>
#include <fstream>
#include <string>

struct film { std::string titre, langue, realisateur; int annee, duree; };// 1
struct ensemble { film * T; int nbfilms; };
struct selection { film ** T; int nbfilms; };

void importer (std::string nom_fichier, ensemble & E)// 2
{
	std::ifstream fichier(nom_fichier);
	if (fichier)// on suppose le fichier correct syntaxiquement
	{
		std::string ligne;
		fichier >> E.nbfilms; fichier.ignore();
		E.T = new film [E.nbfilms];
		for (int i = 0; i < E.nbfilms; ++i)
		{
			std::getline(fichier,ligne); E.T[i].titre = ligne;
			fichier >> E.T[i].annee; fichier.ignore();
			std::getline(fichier,ligne); E.T[i].realisateur = ligne;
			fichier >> E.T[i].duree; fichier.ignore();
			std::getline(fichier,ligne); E.T[i].langue = ligne;
		}
	}
	else
	{
		std::cout << "Fichier introuvable" << std::endl;
		E.nbfilms = 0; E.T = nullptr;
	}
}

void selectionIntegrale (ensemble & E, selection & S)// 3
{
	S.T = new film * [E.nbfilms];
	S.nbfilms = E.nbfilms;
	for (int i = 0; i < E.nbfilms; ++i) S.T[i] = &E.T[i];
}

void selectionPersonnalisee (ensemble & E, selection & S)// 4
{
	std::string real, ch; int anneemin, anneemax, dureemin, dureemax;
	std::cout << "Realisateur : "; std::getline(std::cin,real);
	std::cout << "Annee min : "; std::getline(std::cin,ch); anneemin = std::stoi(ch);
	std::cout << "Annee max : "; std::getline(std::cin,ch); anneemax = std::stoi(ch);
	std::cout << "Duree min : "; std::getline(std::cin,ch); dureemin = std::stoi(ch);
	std::cout << "Duree max : "; std::getline(std::cin,ch); dureemax = std::stoi(ch);
	S.nbfilms = 0;
	for (int i = 0; i < E.nbfilms; ++i)
		if ((real == "X" or real == E.T[i].realisateur) and anneemin <= E.T[i].annee
            and anneemax >= E.T[i].annee and dureemin <= E.T[i].duree and dureemax >= E.T[i].duree)
                ++S.nbfilms;
	if (S.nbfilms > 0)
	{
		S.T = new film * [S.nbfilms];
		// variante : initialiser avec une taille max et ne parcourir qu'une seule fois
		int j = 0;
		for (int i = 0; i < E.nbfilms; ++i)
			if ((real == "X" or real == E.T[i].realisateur) and anneemin <= E.T[i].annee
                and anneemax >= E.T[i].annee and dureemin <= E.T[i].duree and dureemax >= E.T[i].duree)
                    { S.T[j] = &E.T[i]; ++j; }
	}
	else S.T = nullptr;
}

void affichage (const film & F)// 5
{ std::cout << F.titre << " (" << F.realisateur << ", " << F.annee << ")" << std::endl; }
void affichage (const selection & S) { for (int i = 0; i < S.nbfilms; ++i) affichage(*S.T[i]); }

void enregistrer (std::string nom_fichier, const selection & S)// 6
{
	std::ofstream fichier(nom_fichier);
	if (fichier)
	{
		fichier << S.nbfilms << std::endl;
		for (int i = 0; i < S.nbfilms; ++i)
		{
			fichier << S.T[i]->titre << std::endl << S.T[i]->annee << std::endl;
			fichier << S.T[i]->realisateur << std::endl << S.T[i]->duree << std::endl;
			fichier << S.T[i]->langue << std::endl;
		}
	}
	else std::cout << "Erreur cr閍tion fichier" << std::endl;
}

int nbcommun (const selection & S1, const selection & S2)// 7
{
	int j, nbcom = 0; bool trouve;
	for (int i = 0; i < S1.nbfilms; ++i)
	{
		trouve = false; j = 0;
		while ((not trouve) and j < S2.nbfilms)
			if (S1.T[i] == S2.T[j]) trouve = true;
			else ++j;
		if (trouve) ++nbcom;
	}
	return nbcom;
}

void tri (selection & S)// 8
{
	for (int i = 1; i < S.nbfilms; ++i)
	{
		film * p = S.T[i]; int j = i;
		while (j > 0 and S.T[j-1]->annee > p->annee)
            { S.T[j] = S.T[j-1]; --j; }
		S.T[j] = p;
    }
}

int main ()
{
	ensemble E;
	std::string nom_fichier;
	std::cout << "Nom du fichier : "; std::getline(std::cin,nom_fichier);
	importer(nom_fichier,E);
	selection S,S1,S2;
	selectionIntegrale(E,S);
	tri(S); affichage(S);
	selectionPersonnalisee(E,S1);
	std::string nom_fichier_sauvegarde;
	std::cout << "Nom du fichier de sauvegarde : "; std::getline(std::cin,nom_fichier_sauvegarde);
	enregistrer(nom_fichier_sauvegarde+".txt",S1);
	selectionPersonnalisee(E,S2);
	std::cout << "Films en commun : " << nbcommun(S1,S2);
	return 0;
}
