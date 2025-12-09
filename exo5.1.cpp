#include<iostream>
#include<fstream>
#include<string>

using namespace std;

bool iden (string ch1 ,string ch2 )
{
    ifstream fic1;
    ifstream fic2;

    fic1.open(ch1);
    fic2.open(ch2);

    string l1,l2;
    getline(fic1,l1);
    getline(fic2,l2);

    if(fic1.is_open() and fic2.is_open())
    {
        while(fic1.good() && fic2.good()){
            cout << l1 << endl;
            cout << l2 << endl;

            if(l1!=l2){
                return false;
            }
            getline(fic1,l1);
            getline(fic2,l2);
        }
        return true;
        
    }
    else{
        return false;
    }
    
 }

int main ()
{
 string ch1 = "./fic1.txt";
 string ch2 = "./fic3.txt";
 bool statut_fic = iden(ch1, ch2);

 cout << statut_fic << endl;

 return 0;
}