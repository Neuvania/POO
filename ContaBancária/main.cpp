#include <iostream>
#include <vector>
using namespace std;

template <class T>
T read(){
    T t;
    cin >> t;
    return t;
}

struct Operacao{

    string descricao;
    float valor = 0;
    string n;
    float saldoResidual = 0;

    Operacao(string descricao = " ", float valor = 0){
        this->descricao = descricao;
        this->valor = valor;
    }

};

//------------------------------------------------------------
class Conta{
private:
    vector <Operacao> extrato ;

public:

    float saldo = 0;
    int numero;
    bool ativa;

    Conta(int num = 0){
        this->numero = num;
    }
    int getNumero(){
        return this->numero;
    }
    void setNumero(int num){
        this->numero = num;
    }
    float getSaldo(){
        return this->saldo;
    }
    bool deposito(float valor){
        if(valor < 1)
            return false;

        this->saldo += valor;
        this->extrato.push_back(Operacao("Desposito: + ",valor));
        return true;

    }
    bool saque(float valor){
        if(this->saldo < valor || valor < 0)
            return false;
        this->saldo -= valor;
        this->extrato.push_back(Operacao("Saque: - ",valor));

        return true;
    }
    bool transferir(Conta& other, float valor){
        if(valor > this->saldo){
            cerr << "Valor insuficiente para transferencia\n";
            return false;
        }
        this->saldo -= valor;
        extrato.push_back(Operacao("Transferencia de Conta: " + to_string(other.getNumero()), - valor));


        other.saldo += valor;
        extrato.push_back(Operacao("Transferencia para Conta: " + to_string(this->getNumero()), + valor));
        return true;
    }

    vector<Operacao> mostrarExtrato(){
        cout << "Conta: " << this->numero << endl << endl;
        return this->extrato;
    }

};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
void inicializar(Conta& conta, Conta& contaa){
    conta = Conta(8893);
    contaa = Conta(56);
    conta.deposito(10);
    conta.transferir(contaa, 4);
    conta.saque(50);
}

int main(){
    Conta conta, contaa;

    string op;


    inicializar(conta, contaa);
    cout << "Diga a operacao que deseja realizar" << endl << endl;
    cout << "iniciar $Conta: " << endl
         << "saldo" << endl
         << "saque $valor" << endl
         << "deposito $valor" << endl
         << "transf $contaDe: $ContaPara: "
         << "extrato" << endl
         << "sair" << endl;
    cout << "----------------------------------" << endl;

    while(op != "sair"){
        cin >> op;

        cout << "----------------------------------" << endl;
        if(op == "iniciar")
            conta = Conta(read<int>());
        if(op == "saldo")
            cout << conta.getSaldo() << endl;
        if(op == "saque")
            cout << (conta.saque(read<float>())? "ok" : "erro") << endl;
        if(op == "deposito")
            cout << (conta.deposito(read<float>())? "ok" : "erro") << endl;
        if(op == "transf")
            cout << (conta.transferir(contaa, read<float>())? "ok" : "erro") << endl;
        if(op == "extrato"){
            for(auto operacao : conta.mostrarExtrato()){
                cout << operacao.descricao << operacao.valor  <<endl ;
            }
            cout << "Saldo Atual: "<< conta.saldo << endl ;
        }
    }
}

