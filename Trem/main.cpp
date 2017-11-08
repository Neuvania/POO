#include <iostream>
#include <vector>
#include<algorithm>
#include<sstream>
using namespace std;
template <class T>
T read(){
    T t;
    cin >>t;
    return t;
}
class Passageiro{
    string cpf;
    int id;

public:
    Passageiro(string cpf = " "):
        cpf(cpf)
    {}
    string getcpf(){
        return cpf;
    }
    int getid(){
        return id;
    }
    void setid(int id){
        this->id = id;
    }
    string tostringpass(){
        stringstream ss;

        ss  << cpf;

        return ss.str();
    }
};

class Registro{
    vector<Passageiro> passageiros;
public:
    Registro(){

    }

    static  bool compararPassageiros(Passageiro a, Passageiro b){
        return a.getcpf() < b.getcpf();
    }
    vector<Passageiro> getPassageiros(){
        std::sort(passageiros.begin(),passageiros.end(),compararPassageiros);
        return passageiros;
    }



    void cadastrar(Passageiro pass){
        passageiros.push_back(pass);
    }
    string tostringRegistro(){
        int num = 1;
        stringstream ss;
        ss <<"Passageiros registrados"<< endl;
        for(auto elem: getPassageiros()){
            ss <<num <<  " " <<elem.tostringpass() << endl;
            num ++;
        }
        return ss.str();
    }

};

class Vagao{
    int capacidade;
    int id;
    vector<Passageiro*>cadeiras;

public:


    Vagao(int id = 0, int capacidade = 0):
        cadeiras(capacidade, nullptr)
    {
        this->capacidade = capacidade;
        this->id = id;
    }
    int getId(){
        return id;
    }
    int getLotacao(){
        return cadeiras.size() - std::count(cadeiras.begin(),cadeiras.end(),nullptr);
    }
    int getCapacidade(){
        return capacidade;
    }


    bool embarcar(Passageiro * passageiro){
        for(int i = 0; i < (int)cadeiras.size(); i++){
            if(!cadeiras[i]){
                cadeiras[i] = passageiro;

                return true;
            }

        }

        return false;
    }
    Passageiro *desembarcar(string cpf){
        for(int i = 0; i < capacidade; i++){
            if(cpf == cadeiras[i]->getcpf()){
                auto * pass = cadeiras[i];
                cadeiras[i] = nullptr;
                return pass;
            }


        }
        return nullptr;
    }



    string tostringvagao(){
        stringstream m;

        m << "[";
        for(auto elem: cadeiras){
            if(elem != nullptr){
                m<< " " << elem->tostringpass();

            }else{
                m << " - ";
            }
        }
        m << "]";
        return m.str();
    }

};
class Trem{
    int maxvagoes ;
    int cont{0};
    vector<Vagao> vagoes;

public:
    Registro registro;
    Trem(int maxvagoes = 0):
        maxvagoes(maxvagoes)
    {}
    bool addVagao(Vagao vagao){
        if(cont >= maxvagoes){
            return false;
        }
        vagoes.push_back(vagao);
        cont ++;
        return true;
    }
    bool embarcar(Passageiro * passageiro){

        for(auto& elem: vagoes){
            if(elem.getLotacao() < elem.getCapacidade() ){
                elem.embarcar(passageiro);
                return true;
            }

        }
        return false;
    }
    Passageiro * desembacar(string cpf){
        for(auto& elem : vagoes){
            auto * pass = elem.desembarcar(cpf);
            if(pass != nullptr)
                return pass;

        }
        return nullptr;
    }
    string tostringTrem(){
        stringstream s;
        s << "   Vagoes  " << cont <<endl;
        for(auto elem : vagoes){
            s << elem.tostringvagao();
        }
        return s.str();
    }
};

void comandline(){
    string op;
    Trem trem;
    Registro registro;
    int id = 0;
    cout <<"iniciar $maxvagoes" << endl
        << "addVagao $qtd" << endl
        << "entrar $idpass" << endl
        << "sair $idpass" <<endl
        << "showTrem" << endl
        << "registros" << endl;

    while(op !="fim"){
        cin >> op;
        if(op == "iniciar"){
            trem = Trem(read<int>());
            cout << "Done\n";

        }
        if(op == "addVagao"){
            Vagao vagao = Vagao(id,read<int>());
            cout<<(trem.addVagao(vagao)? "Done\n" : "Fail: Numero de vagoes excedido\n");
            id ++;
        }
        if(op == "showTrem"){
            cout<<(trem.tostringTrem());
        }
        if(op == "entrar"){
            bool entrar = true;
            string cpf;
            cin >> cpf;
            for(auto elem : registro.getPassageiros()){
            if(cpf == elem.getcpf()){
                entrar = false;
                cerr << "Fail: Ja existe um passageiro com esse id! \n";
            }
              }
            Passageiro * pass = new Passageiro(cpf);

            if(entrar == true){
            cout << (trem.embarcar(pass)? "Done\n": "Erro\n");
            }
            registro.cadastrar(* pass);

        }
        if(op == "sair"){
            Passageiro * pass = trem.desembacar(read<string>());
            delete pass;

        }
        if(op == "registros"){
            cout<<registro.tostringRegistro();
        }
    }
}

int main()
{
    comandline();
}

