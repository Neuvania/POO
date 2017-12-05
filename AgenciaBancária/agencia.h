#include <iostream>
#include <vector>
#include <sstream>
#ifndef AGENCIA_H
#define AGENCIA_H

using namespace std;

class Agencia{
public:

    Agencia(){}
    Cliente cli;
    vector<Cliente>clientes;
    Cliente * getcliente(string cpf){
        for(auto &elem : clientes)
            if(elem.getNome() == cpf)
                return &elem;
        return nullptr;
    }
    vector <Cliente> getclientes(){
        return clientes;
    }

    void addCliente(string cpf){

        for(auto elem : clientes){
            if(elem.getNome() == cpf)
                throw string("Já existe esse cliente cadastrado");
        }
        clientes.push_back(Cliente(cpf));

    }

    string Tostring(){
        stringstream ss;
        for(auto elem : getclientes())
            ss << elem.getNome() << " ";
        ss << endl;
        return ss.str();
    }

    string showCli(){
        stringstream saida;
        for(auto elem : clientes){
            saida <<"Cliente: "<< elem.getNome() << " Contas: ";
            for(auto cont : elem.getContas()) {
                saida << cont.getId() << " ";
            }
            saida << endl;
        }
        return saida.str();
    }

    string showcontas(string nome){
        stringstream saida;
        for(auto elem : clientes){
            if(elem.getNome() == nome){
                saida <<nome << " Conta:";
                for(auto contass : elem.getContas()){
                    saida << " [" <<contass.getId() << "]";
                }
            }
        }
        return saida.str();
    }

    string getSaldo(string nome ,int num){
        stringstream saida;
        for(auto elem : clientes)
            if(elem.getNome() == nome)
                for(auto saldoconta:  elem.getContas()){
                    if(saldoconta.getId() == num){
                        saida << "saldo: " << saldoconta.getSaldo() << endl;
                        return saida.str();
                    }else
                        saida << "Conta nao existe" << endl;
                }
        return saida.str();
    }

    string extrato(string nome ,int num){
        stringstream saida;
        for(auto elem : clientes){
            if(elem.getNome() == nome){
                for(auto conta : elem.getContas()){
                    if(num == conta.getId()){
                        saida << conta.mostrar();
                    }
                }
            }
        }
        return saida.str();
    }
};

#endif // AGENCIA_H
