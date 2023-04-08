#ifndef JOGOLABIRINTO_HPP
#define JOGOLABIRINTO_HPP
#include<string.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include <vector>
using namespace std;
class jogolabirinto
{
private:
    short int tamanho, profundidade, vida,bag,transformador;
    bool verificadorehzero, naopassou;
public:
    jogolabirinto();
    void settamanho(short int tamanho);
    short int gettamanho();
    void setprofundidade(short int profundidade);
    short int getprofundidade();
    void setvida(short int vida);
    short int getvida();
    void setbag(short int bag);
    short int getbag();
    void setverificadorehzero(bool verificadorehzero);
    bool getverificadorehzero();
    void lendolabirinto();
    void andando();
    bool consertandobug(string a);
    bool naoehperigo(string a);
    bool ehparede(string a);
    short int andando2(short int contador_de_passos);
    bool andando3();
    bool verificandovetor();
    void fazendo_arquivos(short int cont);
    short int casasnaovisitadas();
};
#endif

