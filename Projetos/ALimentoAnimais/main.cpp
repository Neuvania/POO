#include <iostream>
#include <cstdlib>

using namespace std;

struct Comida{
    string nome;
    int vnut;
    float valorC;

    Comida(string nome, int vnut, float valorC){

        this->nome = nome;
        this->vnut = vnut;
        this->valorC = valorC;

    }
};


struct Acoes{
    string nome;
    int  cansaco;

    Acoes(string nome , int cansaco){
        this->nome = nome;
        this->cansaco = cansaco;
    }
};


enum Tipo{gato, dog};


struct Bicho{
    Tipo tipo;
    string nome;
    int energia;
    int idade;
    bool vivo;
    float money;
    Bicho (string nome, Tipo tipo ){
        this->nome=nome;
        this->tipo =tipo;
        energia =10;
        idade =0;
        vivo = true;
        money = 5.0;
    }

    void comer(Comida comida){
        if (energia <= 0){
            vivo = false;
            cout << "SEU TAMAGOCHI MORREU" << endl;

        }

        money -= comida.valorC;
        energia +=comida.vnut;

    }

    void envelhecer(){

        if(idade >= 10){

            vivo = false;
            cout << "SEU TAMAGOCHI MORREU  DE VELHICE\n";
        }

        idade +=1;
        energia -= (0.5 * idade);

    }
    void status(){
        cout << "Nome: " << this->nome
             << "\nEnergia: " << this->energia
             << "\nIdade: " << this->idade
             << "\nMoney: " << this->money << endl;
        if(vivo == false){
            system("clear");
            cout << "SEU TAMAGOCHI MORREU \n";
        }

        if(money < 0){
            system("clear");
            cout << "você esta sem dinheiro suficiente para alimenta-lo\n";

        }
        cout << "*************************************************************\n";
    }

    void caminhar(Acoes acoes){
        if (energia <= 0){
            vivo = false;
            cout << "SEU TAMAGOCHI MORREU" << endl;

        }else{
            energia -= acoes.cansaco;
            money +=1;
        }
    }
    void Brincar(Acoes acoes){
        if (energia <= 0){
            vivo = false;
            cout << "SEU TAMAGOCHI MORREU" << endl;

        }else{
            energia -= acoes.cansaco;
            money +=2;
        }
    }

    void dormir(Acoes acoes){
        energia +=acoes.cansaco;
    }

};


int main()
{
    char op;
    int I = 0;
    Bicho bicho ("taliban", dog);
    Comida banana("banana", 3, 1);
    Comida maca("maca", 5, 2);
    Acoes acaminhar("caminhar",3);
    Acoes abrincar("brincar", 4);
    Acoes adormir("Dormir",3);

    do {

        bicho.status();

        cout << "A - Para alimentar\n";
        cout << "B - Para brincar\n";
        cout << "C - Para caminhar\n";
        cout << "D - Para dormir\n";
        cout << "S - Para sair\n";

        cin >> op;

        if(op == 'a'){
            cout << endl;
            cout << "1 para: Banana: R$ 1,00\n";
            cout << "2 para: Maçã: R$ 2,00\n";


            cout << "Digite sua opção\n";
            cin >> op;
            cout <<"***********************************************************"<< endl;
            if(op == '1'){
                bicho.comer(banana);
            }
            if(op == '2'){
                bicho.comer(maca);
            }


        }
        if(op == 'b'){
            bicho.Brincar(abrincar);


            I ++;
        }
        if (op =='c'){

            bicho.caminhar(acaminhar);

            I++;
        }
        if(op == 'd'){
            bicho.dormir(adormir);

            I++;
        }
        if(I == 3){
            bicho.envelhecer();
            I= 0;

        }



    }while(op!= 's' && bicho.vivo == true);



}



