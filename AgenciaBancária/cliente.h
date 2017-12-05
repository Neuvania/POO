#include <iostream>
#include <vector>
#include <sstream>

#ifndef CLIENTE_H
#define CLIENTE_H

using namespace std;

class Cliente{
    string nome;
    vector<Conta>contas;
    int qtdContas{1};

public:
    Cliente(string cpf = " "){
        this->nome = cpf;
        contas.push_back(Conta(cont++));
        qtdContas ++;
    }

    Conta * getConta(int num){
        for(auto &elem : contas)
            if(elem.getId() == num)
                return &elem;
        return nullptr;
    }

    string getNome(){
        return nome;
    }
    vector<Conta> getContas(){
        return contas;
    }
    void addConta(){
        if(qtdContas > 2)
            throw string("Numeros de contas maxima atingido!");
        contas.push_back(Conta(cont));
        cont += 1;
        qtdContas +=1;

    }

    string encerrarConta(int numero){
        stringstream saida;
        for(int i = 0; i < (int)contas.size(); i++){
            if(contas[i].getId() != numero){
                saida << "conta invalida";
                return saida.str();
            }else if(contas[i].getId() == numero) {
                if(contas[i].getSaldo() > 0){
                    saida << "saldo positivo";
                    return saida.str();
                } else if (contas[i].getAtiva() == false){
                    saida<< "conta ja desativada";
                    return saida.str();
                }else{
                    saida << "ok";
                    contas[i].setAtiva(false);
                    return saida.str();

                }
            }
        }
        return saida.str();
    }
    string Tostring(){
        stringstream ss;
        for(auto elem : getContas())
            ss << elem.getId() << " ";
        return ss.str();
    }
};

#endif // CLIENTE_H
