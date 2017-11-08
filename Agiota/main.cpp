#include <iostream>
#include <vector>
#include<cmath>

using namespace std;

template<class T >
T read(){
    T t;
    cin >> t;
    return t;
}

struct Transacao{
    string nome;
    float valor;
    int id;

    Transacao(int id = 0, string nome = "",float valor = 0.0f){
        this->nome =nome;
        this->valor = valor;
        this->id = id;
    }
};
class Sistema{
    float balanco{0};
    int nextId = 0;
    vector<Transacao> transacoes;
public:
    Sistema(float balanco = 0.0){
        this->balanco = balanco;
    }
    float getBalanco(){
        return this->balanco;
    }
    void addTran(string nome, float valor ){

        if(valor < 0){
            if(abs(valor) > this->Balanco() ){
                cout << "Gente fina não pode emprestar dinheiro no momento"<< endl;
                return;
            }else{
                this->transacoes.push_back(Transacao(nextId, nome, valor));
                this->nextId++;
                return;
            }
        }
        this->transacoes.push_back(Transacao(nextId, nome, valor));
        this->nextId++;

    }
    bool rmTrans(int i){
        if(i >= 0 && i <= (int)transacoes.size()){
            transacoes.erase(transacoes.begin() + i);
            return true;
        }
        return false;
    }
    void mostTransacao(){
        cout << "Lista de transacoes: " << endl;
        for (int i = 0; i < (int)transacoes.size(); i++){
            cout << "Transação " << transacoes[i].id << ": "
                 << transacoes[i].nome << " "
                 << transacoes[i].valor << endl;
        }
    }
    void mostCliente(string nome){
        for(int i = 0; i < (int)transacoes.size(); i++ ){
            if(nome == transacoes[i].nome){

                cout << "Lista de transações de "<< transacoes[i].nome<< ":"<< endl;
                cout << "ID: "<< transacoes[i].id << endl << "Nome: " << transacoes[i].nome << endl
                     << "Valor: " << transacoes[i].valor << endl;
            }
        }
    }
    float Balanco(){
        float total = this->getBalanco();
        for(int i = 0; i < (int)transacoes.size(); i++ ){

            if(transacoes[i].valor < 0){
                total = (total + (transacoes[i].valor));
            }else{
                total += transacoes[i].valor;
            }
        }
        return total;
    }
    vector<Transacao>GetTransacao(){
        return this->transacoes;
    }

    int ContarCliente(){
        for(int i = 0; i < (int)transacoes.size(); i++){
            for(int j = i+1; j < (int)transacoes.size(); j++){
                if(transacoes[i].nome == transacoes[j].nome)
                    this->nextId --;
            }
        }
          return nextId;
    }
};
void initialize(Sistema& system){
    system = Sistema(20);
    system.addTran("jose", 40);
    system.addTran("maria", 20);
}

int main(){
    Sistema system;
    string op = "";

    initialize(system);

    while(op != "sair"){
        cout <<"---------------------------------"<<endl;
        cout<< "- iniciar $din"
            << "\n- addTransacao $nome $valor"
            << "\n- verTransacao"
            << "\n- verCliente $nome"
            << "\n- verBalanco "
            << "\n- rmTransacao"
            << "\n -contarCliente"<< endl;
        cout <<"---------------------------------"<<endl;
        cin >> op;

        if (op == "iniciar")
            system = Sistema((read<float>()));
        if(op == "addTransacao"){
            string  name;
            float value;
            cin >> name >> value;
            system.addTran(name, value);
        }
        if(op == "verCliente")
            system.mostCliente(read<string>());
        if(op == "verTransacao")
            system.mostTransacao();
        if(op == "rmTransacao")
            cout << (system.rmTrans(read<int>())? "Ok" : "Erro");
        if(op == "verBalanco")
            cout << system.Balanco()<<endl;
        if(op == "contarCli"){
            int re = 0;
            re = system.ContarCliente();
            cout << "Total de cliente: "<< re << endl;
        }

    }

}
