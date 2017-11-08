#include <iostream>
#include<vector>
#include<cstdlib>

using namespace std;

template <class T>
T read(){
    T t;
    cin >> t;
    return t;

}
struct Espiral{
    string nome;
    int qtd;
    float valor;

    Espiral(string nome = " ",int qtd =0 , float valor = 0.0f){
        this->nome = nome;
        this->qtd = qtd;
        this->valor = valor;
    }
};
class Maquina{
    float saldo = 0.0;
    float lucro = 0.0;
    vector<Espiral> espirais;
public:
    bool receberDinheiro(float valor){
        if(valor < 0)
            return false;
        this->saldo += valor;
        return true;
    }
    float getsaldo(){
        return this->saldo;
    }
    void devolverTroco(){
        cout  << "você retirou:" << this->saldo<< endl;
        this->saldo = 0.0;
    }
    bool alterarEspiral(int id, string nome,int qtd,float valor){
        if(id >= 0 && id < (int)espirais.size()){
            espirais[id].nome = nome;
            espirais[id].qtd = qtd;
            espirais[id].valor = valor;
            return true;
        }
        return false;
    }
    bool vender(int id){
        if(((int)espirais.size() < id) || (id < 0) || espirais[id].qtd <= 0){
            cout << "produto nao existe\n";
        }
            if(saldo <= espirais[id].valor){
                cout << "dinheiro insuficiente\n";

                return false;
        }else{
            espirais[id].qtd -= 1;
            this->saldo -= espirais[id].valor;
            this->lucro += espirais[id].valor;
            return true;
        }

    }
    void addespiral(Espiral espiral){
        espirais.push_back(espiral);
    }
    void mostrarstatus(){
        cout <<"---------------------------------";
        cout << " \n Saldo: "<< this->saldo<< endl;
        cout << " Lucro: "<<this->lucro << endl;
        cout <<"---------------------------------"<< endl;

        for(int i = 0; i < (int)espirais.size(); i++){

            cout << " Espiral " << i << " : "
                 << espirais[i].nome << " "
                 << espirais[i].qtd <<  " "
                 << espirais[i].valor << endl;
        }
        cout << "---------------------------------"<< endl;
    }
};

void inicializar(Maquina & machine){
    machine.addespiral(Espiral("doritos",4 ,4.9));
    machine.addespiral(Espiral("cheetos",4 ,4.9));
    machine.addespiral(Espiral("refrigerante",2,3.50));
}

int main(){
    Maquina machine;
    inicializar(machine);
    string op = " ";

    while(op != "sair"){
        cout <<"---------------------------------"<<endl;
        cout<< "- inserir $din"
            << "\n- comprar $ind"
            << "\n- troco"
            << "\n-alterar $ind $nome $qtd $valor"
            << "\n- status"<< endl;
        cout <<"---------------------------------"<<endl;

        cin >> op;
        if(op == "inserir")
            cout << (machine.receberDinheiro(read<float>())? "Ok\n" : "Erro\n");
        if(op == "comprar")
          cout << (machine.vender(read<int>())? "Ok" : "Erro/n");
        if(op =="status")
            machine.mostrarstatus();
        if (op == "saldo")
            cout <<machine.getsaldo() << endl;
        if(op == "troco")
            machine.devolverTroco();
        if(op == "alterar"){
            int id;
            string name;
            int qnt;
            float value;
            cin >> id >> name >> qnt >> value;
           cout << (machine.alterarEspiral(id,name,qnt,value)? "Produto Alterado\n" : "Erro. Produto não está na espiral\n");
        }
//          machine.alterarEspiral(read<int>(),read<string>(),
//                                   read<int>(),read<float>());
//        }
    }





}
