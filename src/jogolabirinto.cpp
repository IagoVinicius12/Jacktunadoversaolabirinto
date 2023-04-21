#include "jogolabirinto.hpp"
#include <ctime>
#include <cstdlib>
using namespace std;
string **mat, **mataux, **vetconferencia;
bool passouportodas[8]={false,false,false,false,false,false,false,false};
bool naosaiudapos=true;
short int contador_de_passos=0, perigos_enfrentados=0;
jogolabirinto::jogolabirinto()
{
    this->profundidade = 0;
    // this->perigos_enfrentados = 0;
    this->tamanho = 0;
    this->verificadorehzero = true;
    // this->contador_de_passos = 0;
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
    vetconferencia = new string *[gettamanho() * gettamanho()];
    for (int l = 0; l < (gettamanho() * gettamanho()); l++)
    {
        vetconferencia[l] = new string[getprofundidade()];
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
    short int cont = 0, k = 0;
    while (cont < getprofundidade())
    {
        for (int l = 0; l < gettamanho(); l++)
        {
            getline(arq, b);
            stringstream ss(b);

            while (getline(ss, b, ' '))
            {
                mat[l][c] = b;
                vetconferencia[k][cont] = b;
                k++;
                if (c == gettamanho() - 1)
                    break;
                c++;
            }
            c = 0;
        }
        k = 0;
        getline(arq, b);
        fazendo_arquivos(cont);
        cont++;
    }
    andando();
}
short int l = 0, c = 0, p = 0, item = 0;
void jogolabirinto::andando()
{
    short int random;
    srand(time(nullptr));
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
            cout<<mat[l][c]<<"\t";
            if (c == gettamanho() - 1)
                break;
            c++;
        }
        cout<<endl;
        c = 0;
    }
    cout<<"Por favor, digite a linha e a coluna que voce quer comecar na primeira matriz, (lembre-se caso a posição seja uma parede voce terá que digitar novamente):"<<endl;
    cout<<"Caso seja um * o player nao tomara dano ate que saia de la:"<<endl;
    short int cinicial=0, linicial=0;
    do{
        cin>>linicial;
        cin>>cinicial;
    }while(mat[l][c]=="#");
    c=cinicial;
    l=linicial;
    short int verificaprofundidade = p;
    vetconferencia[(gettamanho()*l)+(c)][p]="p";
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
                short int coluna=0;
                while (getline(ss, b, ' '))
                {
                    mat[l][coluna] = b;
                    if (coluna == gettamanho() - 1)
                        break;
                    coluna++;
                }
                coluna = 0;
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
        if(naosaiudapos==true && verificandosenaoconseguiuandar()==true){
            cout << "vida=" << getvida() << endl;
            cout << "mat[" << l << "][" << c << "][" << p << "]" << endl;
            cout << "Contador de passos=" << contador_de_passos << endl;
            cout << "Items=" << item << endl;
            cout<<"O player não conseguiu andar naquela posição pois está cercado, encerrando..."<<endl;
            exit(1);
        }
        if (p == 0 && c == cinicial && l == linicial && verificadorehzero == true && naopassou == false)
        {
            cout << "vida=" << getvida() << endl;
            cout << "mat[" << l << "][" << c << "][" << p << "]" << endl;
            cout << "Contador de passos=" << contador_de_passos << endl;
            cout << "Items=" << item << endl;
            ofstream arq2("dataset/output.data");
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
                        arq2<<mat[l][c]<<" ";
                    }
                    cout << endl;
                    arq2<<endl;
                }
                arq2<<endl;
                cout << "========================================" << endl;
            }
            cout << "Quantidade de casas que nao foram visitadas sem contar as paredes: "<<casasnaovisitadas() << endl;
            cout << "Contador de passos: " << contador_de_passos << endl;
            cout << "Perigos enfrentado: " << perigos_enfrentados << endl;
            cout << "Quantidade de items pegos: "<< item<<endl;
            //fazendo_arquivo_de_saida();
            exit(1);
        }
        if (p > 0)
        {
            naopassou = false;
        }
        else if (p == 0 && c == cinicial && l == linicial)
        {
            naopassou = true;
        }
        if (p == 0 && l == linicial && c == cinicial && verificadorehzero == false)
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
                    contador_de_passos++;
                    cout << "Direita" << endl;
                    naosaiudapos=false;
                    for(int m=0;m<8;m++){
                        passouportodas[m]=false;
                    }
                }
                else
                {
                    c--;
                    naosaiudapos=true;
                    passouportodas[0]=true;
                }
            }
            else
            {
                andando2(random);
            }
            break;
        case 1:
            if (c != gettamanho() - 1 && l != gettamanho() - 1)
            {
                c++;
                l++;
                if (andando3())
                {
                    contador_de_passos++;
                    cout << "Diagonal" << endl;
                    naosaiudapos=false;
                    for(int m=0;m<8;m++){
                        passouportodas[m]=false;
                    }
                }
                else
                {
                    c--;
                    l--;
                    naosaiudapos=true;
                    passouportodas[1]=true;
                }
            }
            else
            {
                andando2(random);
            }
            break;
        case 2:
            if (l != gettamanho() - 1)
            {
                l++;
                if (andando3())
                {
                    contador_de_passos++;
                    cout << "Pra baixo" << endl;
                    naosaiudapos=false;
                    for(int m=0;m<8;m++){
                        passouportodas[m]=false;
                    }
                }
                else
                {
                    l--;
                    naosaiudapos=true;
                    passouportodas[2]=true;
                }
            }
            else
            {
                andando2(random);
            }
            break;
        case 3:
            if ((c != 0 && l != gettamanho() - 1))
            {
                c--;
                l++;
                if (andando3())
                {
                    contador_de_passos++;
                    cout << "Diagonal de baixo esquerda" << endl;
                    naosaiudapos=false;
                    for(int m=0;m<8;m++){
                        passouportodas[m]=false;
                    }
                }
                else
                {
                    c++;
                    l--;
                    naosaiudapos=true;
                    passouportodas[3]=true;
                }
            }
            else
            {
                andando2(random);
            }
            break;
        case 4:
            if (c != 0)
            {
                c--;
                if (andando3())
                {
                    contador_de_passos++;
                    cout << "Pra tras" << endl;
                    naosaiudapos=false;
                    for(int m=0;m<8;m++){
                        passouportodas[m]=false;
                    }
                }
                else
                {
                    c++;
                    naosaiudapos=true;
                    passouportodas[4]=true;
                }
            }
            else
            {
                andando2(random);
            }
            break;
        case 5:
            if (c != 0 && l != 0)
            {
                c--;
                l--;
                if (andando3())
                {
                    contador_de_passos++;
                    cout << "Diagonal de cima esquerda" << endl;
                    naosaiudapos=false;
                    for(int m=0;m<8;m++){
                        passouportodas[m]=false;
                    }
                }
                else
                {
                    c++;
                    l++;
                    naosaiudapos=true;
                    passouportodas[5]=true;
                }
            }
            else
            {
                andando2(random);
            }
            break;
        case 6:
            if (l != 0)
            {
                l--;
                if (andando3())
                {
                    contador_de_passos++;
                    cout << "Pra cima" << endl;
                    naosaiudapos=false;
                    for(int m=0;m<8;m++){
                        passouportodas[m]=false;
                    }
                }
                else
                {
                    l++;
                    naosaiudapos=true;
                    passouportodas[6]=true;
                }
            }
            else
            {
                andando2(random);
            }
            break;
        case 7:
            if (c != gettamanho() - 1 && l != 0)
            {
                c++;
                l--;
                if (andando3())
                {
                    contador_de_passos++;
                    cout << "Diagonal de cima direita" << endl;
                    naosaiudapos=false;
                    for(int m=0;m<8;m++){
                        passouportodas[m]=false;
                    }
                }
                else
                {
                    c--;
                    l++;
                    naosaiudapos=true;
                    passouportodas[7]=true;
                }
            }
            else
            {
                andando2(random);
            }
            break;
        }
        cout << "vida=" << getvida() << endl;
        cout << "mat[" << l << "][" << c << "][" << p << "]" << endl;
        cout << "Items=" << item << endl<<endl;
        vetconferencia[(gettamanho() * l) + c][p] = "p";
    }
    arquivo.close();
    short int contador = 0;
    ofstream arq2("dataset/output.data");
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
                arq2<< mat[l][c]<<" ";
            }
            cout << endl;
            arq2<<endl;
        }
        arq2<<endl;
        cout << "========================================" << endl;
    }
    cout<<"SUA VIDA CHEGOU A ZERO"<<endl;
    cout << "Quantidade de casas que nao foram visitadas: "<<casasnaovisitadas() << endl;
    cout << "Contador de passos: " << contador_de_passos << endl;
    cout << "Perigos enfrentado: " << perigos_enfrentados << endl;
    cout << "Quantidade de items pegos: "<< item<<endl<<endl;
    arq2.close();
    //fazendo_arquivo_de_saida();
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
void jogolabirinto::andando2(short int random)
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
        contador_de_passos++;
        p = 0;
        transformador = stoi(mataux[l][c]);
        if (transformador > 0)
        {
            setbag(getbag() + 1);
            cout << "Achei um item agora tenho:" << getbag() << endl;
            item++;
            transformador = transformador - 1;
            verificadorehzero = false;
        }
        naosaiudapos=false;
        for(int m=0;m<7;m++){
            passouportodas[m]=false;
        }
        mataux[l][c] = to_string(transformador);
    }
    else if (p == getprofundidade() - 1 && ehparede(mataux[l][c]) == false && naoehperigo(mataux[l][c]) == false)
    {
        //cout << "Passou de matriz e tomou dano" << endl;
        naopassou = false;
        //cout << mataux[l][c] << endl;
        setvida(getvida() - 1);
        contador_de_passos++;
        perigos_enfrentados++;
        p = 0;
        naosaiudapos=false;
        for(int m=0;m<7;m++){
            passouportodas[m]=false;
        }
    }
    else if (p == getprofundidade() - 1 && ehparede(mataux[l][c]))
    {
        //cout << "Nao Passou de matriz1" << mataux[l][c][0] << endl;
        naosaiudapos=true;
        passouportodas[random]=true;
    }
    else if (ehparede(mataux[l][c]) == false && naoehperigo(mataux[l][c]) == false)
    {
        //cout << "Passou de matriz2 e tomou dano" << mataux[l][c] << endl;
        naopassou = false;
        setvida(getvida() - 1);
        contador_de_passos++;
        perigos_enfrentados++;
        p++;
        naosaiudapos=false;
        for(int m=0;m<7;m++){
            passouportodas[m]=false;
        }
    }
    else if (ehparede(mataux[l][c]) == false)
    {
        //cout << "Passou de matriz" << endl;
        naopassou = false;
        transformador = stoi(mataux[l][c]);
        if (transformador > 0)
        {
            setbag(getbag() + 1);
            cout << "Achei um item agora tenho:" << getbag() << endl;
            item++;
            transformador = transformador - 1;
            verificadorehzero = false;
        }
        mataux[l][c] = to_string(transformador);
        contador_de_passos++;
        p++;
        naosaiudapos=false;
        for(int m=0;m<7;m++){
            passouportodas[m]=false;
        }
    }
    else
    {
        //cout << "Não deu nada" << endl;
        naosaiudapos=true;
        passouportodas[random]=true;
    }
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
        //cout << "parede" << endl;
        //cout << mat[l][c] << endl;
        return 0;
    }
    else if (naoehperigo(mat[l][c]) == false)
    {
        setvida(getvida() - 1);
        perigos_enfrentados++;
        return 1;
    }
    else if ((naoehperigo(mat[l][c])) && (ehparede(mat[l][c]) == false))
    {
        transformador = stoi(mat[l][c]);
        if (transformador > 0)
        {
            setbag(getbag() + 1);
            cout << "Achei um item agora tenho:" << getbag() << endl;
            item++;
            transformador = transformador - 1;
            verificadorehzero = false;
        }
        mat[l][c] = to_string(transformador);
        return 1;
    }
    return 0;
}
short int jogolabirinto::casasnaovisitadas()
{
    short int casasnaovisitadas = 0;
    for (int profundidade = 0; profundidade < getprofundidade(); profundidade++)
    {
        for (int k = 0; k < gettamanho() * gettamanho(); k++)
        {
            if (vetconferencia[k][profundidade] != "p" && vetconferencia[k][profundidade] != "#")
            {
                casasnaovisitadas++;
            }
        }
    }
    return casasnaovisitadas;
}
bool jogolabirinto::verificandosenaoconseguiuandar(){
    int cont=0;
    for(int m=0;m<8;m++){
        if(passouportodas[m]==true){
            cont++;
        }
    }
    if(cont==8){
        return true;
    }
    else{
        return false;
    }
}
// void jogolabirinto::fazendo_arquivo_de_saida(){
//     ofstream arquivo("dataset/output.data");
//     short int contador=0;
//     for (int profundidade = 0; profundidade < getprofundidade(); profundidade++)
//     {
//         for (int k = 0; k < gettamanho() * gettamanho(); k++)
//         {
//             contador++;
//             arquivo<<vetconferencia[k][profundidade]<<" ";
//             if(contador==gettamanho()){
//                 arquivo<<endl;
//                 contador=0;
//             }
//         }
//         arquivo<<endl;
//     }
// }
