#include "jogolabirinto.hpp"
#include <ctime>
#include <cstdlib>
using namespace std;
string **mat, **mataux, **vetconferencia;
jogolabirinto::jogolabirinto()
{
    this->profundidade = 0;
    this->tamanho = 0;
    this->verificadorehzero = true;
    this->naopassou = true;
    setvida(10);
    setbag(0);
}
void jogolabirinto::settamanho(short int tamanho)
{
    this->tamanho = tamanho;
}
short int jogolabirinto::gettamanho()
{
    return this->tamanho;
}
void jogolabirinto::setvida(short int vida)
{
    this->vida = vida;
}
short int jogolabirinto::getvida()
{
    return this->vida;
}
void jogolabirinto::setbag(short int bag)
{
    this->bag = bag;
}
short int jogolabirinto::getbag()
{
    return this->bag;
}
void jogolabirinto::setprofundidade(short int profundidade)
{
    this->profundidade = profundidade;
}
short int jogolabirinto::getprofundidade()
{
    return this->profundidade;
}
void jogolabirinto::lendolabirinto()
{
    string b;
    fstream arq;
    arq.open("dataset/input.data");
    arq >> b;
    arq >> b;
    settamanho(stoi(b));
    arq >> b;
    setprofundidade(stoi(b));
    getline(arq, b);
    vetconferencia=new string *[gettamanho()*gettamanho()];
    for(int l=0;l<(gettamanho()*gettamanho());l++){
        vetconferencia[l]=new string[getprofundidade()];
    }
    mat = new string *[gettamanho()];

    for (int l = 0; l < gettamanho(); l++)
    {
        mat[l] = new string[gettamanho()];
    }
    mataux = new string *[gettamanho()];

    for (int l = 0; l < gettamanho(); l++)
    {
        mataux[l] = new string[gettamanho()];
    }
    short int c = 0;
    short int cont = 0,k=0;
    while (cont < getprofundidade())
    {
        for (int l = 0; l < gettamanho(); l++)
        {
            getline(arq, b);
            stringstream ss(b);

            while (getline(ss, b, ' '))
            {
                mat[l][c] = b;
                vetconferencia[k][cont]=b;
                k++;
                if (c == gettamanho() - 1)
                    break;
                c++;
            }
            c = 0;
        }
        k=0;
        getline(arq, b);
        fazendo_arquivos(cont);
        cont++;
    }
    for(int i=0;i<gettamanho()*gettamanho();i++){
        cout<<vetconferencia[i][1];
    }
    andando();
}
short int l = 0, c = 0, p = 0, item = 0;
void jogolabirinto::andando()
{
    short int random, contador_de_passos = 0;
    srand(time(nullptr));
    fstream arquivo;
    string nome_arquivo = "dataset/", b;
    nome_arquivo.append(to_string(p));
    nome_arquivo.append(".data");
    cout << nome_arquivo << endl;
    arquivo.open(nome_arquivo);
    for (int l = 0; l < gettamanho(); l++)
    {
        getline(arquivo, b);
        stringstream ss(b);

        while (getline(ss, b, ' '))
        {
            mat[l][c] = b;
            if (c == gettamanho() - 1)
                break;
            c++;
        }
        c = 0;
    }
    short int verificaprofundidade = p;
    while (getvida() > 0)
    {
        if (verificaprofundidade != p)
        {
            arquivo.close();
            nome_arquivo = "dataset/";
            nome_arquivo.append(to_string(verificaprofundidade));
            nome_arquivo.append(".data");
            ofstream arquivo(nome_arquivo);
            for (short int i = 0; i < gettamanho(); i++)
            {
                for (short int j = 0; j < gettamanho(); j++)
                {
                    arquivo << mat[i][j] << " ";
                }
                arquivo << endl;
            }
            arquivo.close();
            ifstream arq1;
            string nome_arquivo = "dataset/", b;
            nome_arquivo.append(to_string(p));
            nome_arquivo.append(".data");
            arq1.open(nome_arquivo);
            for (int l = 0; l < gettamanho(); l++)
            {
                getline(arq1, b);
                stringstream ss(b);

                while (getline(ss, b, ' '))
                {
                    mat[l][c] = b;
                    if (c == gettamanho() - 1)
                        break;
                    c++;
                }
                c = 0;
            }
            for (short int i = 0; i < gettamanho(); i++)
            {
                for (short int j = 0; j < gettamanho(); j++)
                {
                    mat[i][j] = mataux[i][j];
                }
            }
            verificaprofundidade = p;
        }
        random = rand() % 8;
        if (getbag() == 4 && getvida() < 10)
        {
            setvida(getvida() + 1);
            cout << "recuperei" << endl;
            setbag(0);
        }
        if (p == 0 && c == 0 && l == 0 && verificadorehzero == true && naopassou == false)
        {
            cout << "vida=" << getvida() << endl;
            cout << "mat[" << l << "][" << c << "][" << p << "]" << endl;
            cout << "Contador de passos=" << contador_de_passos << endl;
            cout << "Items=" << item << endl;
            for (int p = 0; p < getprofundidade(); p++)
            {
                fstream arquivo;
                string nome_arquivo = "dataset/", b;
                nome_arquivo.append(to_string(p));
                nome_arquivo.append(".data");
                arquivo.open(nome_arquivo);
                for (int l = 0; l < gettamanho(); l++)
                {
                    getline(arquivo, b);
                    stringstream ss(b);

                    while (getline(ss, b, ' '))
                    {
                        mat[l][c] = b;
                        if (c == gettamanho() - 1)
                            break;
                        c++;
                    }
                    c = 0;
                }
                for (int l = 0; l < gettamanho(); l++)
                {
                    for (int c = 0; c < gettamanho(); c++)
                    {
                        cout << mat[l][c] << "\t";
                    }
                    cout << endl;
                }
                cout << "========================================" << endl;
            }
            exit(1);
        }
        if (p > 0)
        {
            naopassou = false;
        }
        else if (p == 0 && c == 0 && l == 0)
        {
            naopassou = true;
        }
        if (p == 0 && l == 0 && c == 0 && verificadorehzero == false)
        {
            verificadorehzero = true;
        }
        else if (getbag() == 4 && getvida() == 10)
        {
            setbag(0);
        }
        switch (random)
        {
        case 0:
            if (c != gettamanho() - 1)
            {
                c++;
                if (andando3())
                {
                    cout << "Direita" << endl;
                }
                else
                {
                    c--;
                }
            }
            else
            {
                contador_de_passos = andando2(contador_de_passos);
            }
            break;
        case 1:
            if (c != gettamanho() - 1 && l != gettamanho() - 1)
            {
                c++;
                l++;
                if (andando3())
                {
                    cout << "Diagonal" << endl;
                }
                else
                {
                    c--;
                    l--;
                }
            }
            else
            {
                contador_de_passos = andando2(contador_de_passos);
            }
            break;
        case 2:
            if (l != gettamanho() - 1)
            {
                l++;
                if (andando3())
                {
                    cout << "Pra baixo" << endl;
                }
                else
                {
                    l--;
                }
            }
            else
            {
                contador_de_passos = andando2(contador_de_passos);
            }
            break;
        case 3:
            if ((c != 0 && l != gettamanho() - 1))
            {
                c--;
                l++;
                if (andando3())
                {
                    cout << "Diagonal de baixo esquerda" << endl;
                }
                else
                {
                    c++;
                    l--;
                }
            }
            else
            {
                contador_de_passos = andando2(contador_de_passos);
            }
            break;
        case 4:
            if (c != 0)
            {
                c--;
                if (andando3())
                {
                    cout << "Pra tras" << endl;
                }
                else
                {
                    c++;
                }
            }
            else
            {
                contador_de_passos = andando2(contador_de_passos);
            }
            break;
        case 5:
            if (c != 0 && l != 0)
            {
                c--;
                l--;
                if (andando3())
                {
                    cout << "Diagonal de cima esquerda" << endl;
                }
                else
                {
                    c++;
                    l++;
                }
            }
            else
            {
                contador_de_passos = andando2(contador_de_passos);
            }
            break;
        case 6:
            if (l != 0)
            {
                l--;
                if (andando3())
                {
                    cout << "Pra cima" << endl;
                }
                else
                {
                    l++;
                }
            }
            else
            {
                contador_de_passos = andando2(contador_de_passos);
            }
            break;
        case 7:
            if (c != gettamanho() - 1 && l != 0)
            {
                c++;
                l--;
                if (andando3())
                {
                    cout << "Diagonal de cima direita" << endl;
                }
                else
                {
                    c--;
                    l++;
                }
            }
            else
            {
                contador_de_passos = andando2(contador_de_passos);
            }
            break;
        }
        cout << "vida=" << getvida() << endl;
        cout << "mat[" << l << "][" << c << "][" << p << "]" << endl;
        cout << "Contador de passos=" << contador_de_passos << endl;
        cout << "Items=" << item << endl;
        vetconferencia[(gettamanho()*l)+c][p]="p";
        short int k=0;
        for(int profundidade=0;profundidade<getprofundidade();profundidade++){
            for(int i=0;i<gettamanho()*gettamanho();i++){
                cout<<vetconferencia[i][profundidade]<<"\t";
                k++;
                if(k==gettamanho()){
                    cout<<endl;
                    k=0;
                }
            }
            cout<<"========================="<<endl;
        }
    }
    arquivo.close();
    short int contador = 0;
    for (int prof = 0; prof < getprofundidade(); prof++)
    {
        while (contador < 1)
        {
            string nome_arquivo = "dataset/", b;
            nome_arquivo.append(to_string(verificaprofundidade));
            nome_arquivo.append(".data");
            ofstream arquivo(nome_arquivo);
            for (short int i = 0; i < gettamanho(); i++)
            {
                for (short int j = 0; j < gettamanho(); j++)
                {
                    arquivo << mat[i][j] << " ";
                }
                arquivo << endl;
            }
            arquivo.close();
            contador++;
        }
        fstream arq1;
        string nome_arquivo = "dataset/", b;
        nome_arquivo.append(to_string(prof));
        nome_arquivo.append(".data");
        arq1.open(nome_arquivo);
        for (int l = 0; l < gettamanho(); l++)
        {
            getline(arq1, b);
            stringstream ss(b);
            c = 0;
            while (getline(ss, b, ' '))
            {
                mat[l][c] = b;
                if (c == gettamanho() - 1)
                    break;
                c++;
            }
            c = 0;
        }
        for (int l = 0; l < gettamanho(); l++)
        {
            for (int c = 0; c < gettamanho(); c++)
            {
                cout << mat[l][c] << "\t";
            }
            cout << endl;
        }
        cout << "========================================" << endl;
    }
    cout<<casasnaovisitadas();
}
bool jogolabirinto::consertandobug(string a)
{
    if ((a[0] != '*'))
    {
        if (a[0] == '#')
        {
            cout << "retornou 0" << a << endl;
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}
bool jogolabirinto::naoehperigo(string a)
{
    if ((a[0] != '*'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool jogolabirinto::ehparede(string a)
{
    if ((a[0] == '#'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
short int jogolabirinto::andando2(short int contador_de_passos)
{
    short int prof = 0;
    if (p == getprofundidade() - 1)
    {
        prof = 0;
    }
    else
    {
        prof = (p + 1);
    }
    fstream arquivo;
    string nome_arquivo = "dataset/", b;
    nome_arquivo.append(to_string(prof));
    nome_arquivo.append(".data");
    arquivo.open(nome_arquivo);
    for (int l = 0; l < gettamanho(); l++)
    {
        getline(arquivo, b);
        stringstream ss(b);
        short int coluna = 0;
        while (getline(ss, b, ' '))
        {
            mataux[l][coluna] = b;
            if (coluna == gettamanho() - 1)
                break;
            coluna++;
        }
        coluna = 0;
    }
    if (p == getprofundidade() - 1 && consertandobug(mataux[l][c]))
    {
        cout << "Passou de matriz" << endl;
        cout << mataux[l][c] << endl;
        contador_de_passos++;
        p = 0;
        transformador = stoi(mataux[l][c]);
        cout << "valor:" << mataux[l][c] << endl;
        if (transformador > 0)
        {
            setbag(getbag() + 1);
            cout << "Achei um item" << getbag() << endl;
            item++;
            transformador = transformador - 1;
            verificadorehzero = false;
        }
        mataux[l][c] = to_string(transformador);
        cout << "valor depois:" << mataux[l][c] << endl;
    }
    else if (p == getprofundidade() - 1 && ehparede(mataux[l][c]) == false && naoehperigo(mataux[l][c]) == false)
    {
        cout << "Passou de matriz e tomou dano" << endl;
        naopassou = false;
        cout << mataux[l][c] << endl;
        setvida(getvida() - 1);
        contador_de_passos++;
        p = 0;
    }
    else if (p == getprofundidade() - 1 && ehparede(mataux[l][c]))
    {
        cout << "Nao Passou de matriz1" << mataux[l][c][0] << endl;
    }
    else if (ehparede(mataux[l][c]) == false && naoehperigo(mataux[l][c]) == false)
    {
        cout << "Passou de matriz2 e tomou dano" << mataux[l][c] << endl;
        naopassou = false;
        setvida(getvida() - 1);
        contador_de_passos++;
        p++;
    }
    else if (ehparede(mataux[l][c]) == false)
    {
        cout << "Passou de matriz" << endl;
        naopassou = false;
        transformador = stoi(mataux[l][c]);
        if (transformador > 0)
        {
            setbag(getbag() + 1);
            cout << "Achei um item" << getbag() << endl;
            item++;
            transformador = transformador - 1;
            verificadorehzero = false;
        }
        mataux[l][c] = to_string(transformador);
        contador_de_passos++;
        p++;
    }
    else
    {
        cout << "Não deu nada" << endl;
    }
    return contador_de_passos;
}
void jogolabirinto::fazendo_arquivos(short int cont)
{
    string nomearq;
    nomearq = "dataset/";
    nomearq.append(to_string(cont));
    nomearq.append(".data");
    ofstream arq(nomearq);
    for (short int i = 0; i < gettamanho(); i++)
    {
        for (short int j = 0; j < gettamanho(); j++)
        {
            arq << mat[i][j] << " ";
        }
        arq << endl;
    }
    arq.close();
}
bool jogolabirinto::andando3()
{
    if (ehparede(mat[l][c]))
    {
        cout << "parede" << endl;
        cout << mat[l][c] << endl;
        return 0;
    }
    else if (naoehperigo(mat[l][c]) == false)
    {
        setvida(getvida() - 1);
        return 1;
    }
    else if ((naoehperigo(mat[l][c])) && (ehparede(mat[l][c]) == false))
    {
        transformador = stoi(mat[l][c]);
        cout << "valor:" << mat[l][c] << endl;
        if (transformador > 0)
        {
            setbag(getbag() + 1);
            cout << "Achei um item agora tenho" << getbag() << endl;
            item++;
            transformador = transformador - 1;
            verificadorehzero = false;
        }
        mat[l][c] = to_string(transformador);
        cout << "valor depois:" << mat[l][c] << endl;
        return 1;
    }
    return 0;
}
short int jogolabirinto::casasnaovisitadas(){
    short int casasnaovisitadas=0;
    for(int profundidade=0;profundidade<getprofundidade();profundidade++){
        for(int k=0;k<gettamanho()*gettamanho();k++){
            if(vetconferencia[k][profundidade]!="p" && vetconferencia[k][profundidade]!="#"){
                casasnaovisitadas++;
            }
        }
    }
    return casasnaovisitadas;
}