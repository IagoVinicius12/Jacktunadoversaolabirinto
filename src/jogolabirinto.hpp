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
    void lendolabirinto();
    void andando();
    bool consertandobug(string a);
    bool naoehperigo(string a);
    bool ehparede(string a);
    void andando2(short int rand);
    bool andando3();
    void fazendo_arquivos(short int cont);
    short int casasnaovisitadas();
    bool verificandosenaoconseguiuandar();
};
#endif

