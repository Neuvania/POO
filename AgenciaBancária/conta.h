#include <iostream>
#include <vector>
#include <sstream>

#ifndef CONTA_H
#define CONTA_H


using namespace std;

int cont = 0;

class Operacao{
public:

    string descricao;
    float valor;
    float saldoParc{0};

    Operacao(string descricao = " ", float valor = 0){
        this->descricao = descricao;
        this->valor = valor;
    }

    string Tostring(){
        stringstream saida;
        saida << "Descricao: "<<descricao << " Valor: " << valor << " saldoParc: " << saldoParc << endl;
        return saida.str();
    }
};

class Conta{
    float saldo{0};
    int id;
    bool ativa = true;
    vector<Operacao> extrato;

public:
    Conta(int id = 0){
        this->id = id;
    }

    float getSaldo(){
        return this->saldo;
    }

    int getId(){
        return this->id;
    }
    bool getAtiva(){
        return ativa;
    }
    bool setAtiva(bool sit){
        return ativa = sit;
    }
    void Despositar(float valor){
        if(valor <= 0 )
            throw string("impossivel depositar");
        if(ativa == false)
            throw string("conta desativada");


        this->saldo += valor;
        this->extrato.push_back(Operacao("Deposito: ", valor));

    }

    void Sacar(float valor){
        if(valor > saldo || valor < 0)
            throw string("Saldo insuficiente");
        if(ativa == false)
            throw string ("Essa conta se encontra desativada");
        this->saldo -= valor;
        this->extrato.push_back(Operacao("Saque: ", valor));

    }
    void Transferir(Conta * other, float valor){
        if(valor < 0 )
            throw string("Saldo insuficiente");
        if(ativa == false)
            throw string ("Essa conta se encontra desativada");

        this->saldo -= valor;
        this->extrato.push_back(Operacao("Transferencia: ",valor));
        other->saldo += valor;
        other->extrato.push_back(Operacao("Tranferencia: ",valor));
    }

    vector <Operacao> getExtrato(){
        return this->extrato;
    }
    string mostrar(){
        stringstream s;
        for(auto elem : extrato)
            s << elem.Tostring();
        return s.str();
    }
};

#endif // CONTA_H
