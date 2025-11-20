
// CPP code to illustrate the use of sqrt function
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std; //utiliser cette commande pour ne pas avoir à mettre std:: 

void saisir(float &a,float &b,float &c)
{
    cout<<"saisir la longueur des trois côtés du triangle:" << endl;
	cout<<"a = ";
    cin>>a;
	cout<<"b = ";
    cin>>b;
	cout<<"c = ";
    cin>>c;
}

//2
void validite(float a,float b,float c){

    if((a+b>c )and (b+c>a) and (c+a>b)){
        cout<<"c'est un triangle valide" << endl;
    }
    else{
       cout<<"ce n'est pas un triangle valide " << endl;
    }
}

//3
float perim(float a, float b, float c){
 return a+b+c;

}

float aire(float a, float b, float c){
 float S=(a+b+c)/2;
return sqrt(S*(S-a)*(S-b)*(S-c));
}

//4
bool equi(float a, float b, float c){
 if(a==b && a==c && b==c){
 return true;
 }
 else return false;

}

bool iso( float a, float b, float c){
 if(a==b or a==c or b==c){
 return true;
 }
 else return false;
}

bool rect(float a, float b, float c){
 if(a*a+b*b==c*c or a*a+c*c==b*b or b*b+c*c==a*a){//theoreme de pythagore 
 return true;
 }
 else return false;
}

bool plat(float a, float b, float c){
 if(a+b==c or a+c==b or b+c==a)
 return true;
else return false;
}

//6
string nature(float a, float b, float c){
 if(rect(a,b,c)) return "rectangle";
 else if(equi(a,b,c)) return "equilatéral";
 else if(plat(a,b,c)) return "plat";
 else if(iso(a,b,c)) return "isocèle";
 else return "quelconque";
}

int main()
{
    float a=3,b=4,c=5;
    string nature_du_triangle;
    // saisir(a,b,c);
    validite(a,b,c);
    nature_du_triangle = nature(a, b, c);
    cout << "Le triangle est : " << nature_du_triangle << endl;
    return 0;
}
