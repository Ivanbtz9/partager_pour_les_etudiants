#include <iostream>

void saisir(float &a,float &b,float &c)
{
    std::cout<<"saisir la longueur des trois côtés du triangle:" << std::endl;
	std::cout<<"a = ";
    std::cin>>a;
	std::cout<<"b = ";
    std::cin>>b;
	std::cout<<"c = ";
    std::cin>>c;
}

//2
void validite(float a,float b,float c){

    if((a+b>c )and (b+c>a) and (c+a>b)){
        std::cout<<"c'est un triangle valide";
    }
    else{
       std::cout<<"ce n'est pas un triangle valide ";
    }
}


float perim(float a, float b, float c){
 return a+b+c;

}

float aire(float a, float b, float c){
 float S=(a+b+c)/2;
return sqrt(S*(S-a)*(S-b)*(S-c));
}

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
 if(a*a+b*b==c*c or a*a+c*c==b*b or b*b+c*c==a*a){
 return true;
 }
 else return false;
}

bool plat(float a, float b, float c){
 if(a+b==c or a+c==b or b+c==a)
 return true;
else return false;
}

std::string nature(float a, float b, float c){
 if(rect(a,b,c)) return "rectangle";
 else if(equi(a,b,c)) return "equilatéral";
 else if(plat(a,b,c)) return "plat";
 else if(iso(a,b,c)) return "isocèle";
 else return "quelconque";
}

int main()
{
    float a,b,c;
    saisir(a,b,c);
    validite(a,b,c);
    return 0;
}
