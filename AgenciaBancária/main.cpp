#include <iostream>
#include <vector>
#include <sstream>
#include "conta.h"
#include "cliente.h"
#include "agencia.h"

using namespace std;

template <class T>
T read(){
    T t;
    cin >> t;
    return t;
}

class Controle{
    Agencia agencia;
    Conta * conta;
    Cliente * cliente;
public:
    Controle(){
        cliente = nullptr;

    }
    void comandline(){
        string op = "";
        string login = "";
        string ui = "";

        cout << "admin"<< endl
             <<  "login $cliente" << endl;
        while(login != "sair"){
            cin >> login;



            if(login == "admin"){
                cout << "----------------------\n";
                cout<<"admin"<< endl
                   <<"addCli $nome"<< endl
                  <<"openConta"<< endl
                 <<"encerrar"<< endl
                <<"showCli"<< endl
                <<"showAll"<< endl
                <<"logout"<< endl;


                while (op != "logout"){
                    cout <<"-----------------------"<< endl;
                    cin >> op;
                    try{
                        if(op == "addCli")
                            (agencia.addCliente(read<string>()));
                        else if(op == "showCli")
                            cout << agencia.Tostring();
                        else if(op == "showAll")
                            cout << agencia.showCli();
                        else if(op == "openConta"){
                            string a;
                            cin >> a;
                            agencia.getcliente(a)->addConta();
                        }
                        else if(op == "encerrar"){
                            string cpf = "";
                            int num = 0;
                            cin >> cpf;
                            cin >> num;
                            cout << agencia.getcliente(cpf)->encerrarConta(num);
                        }   else if(op != "logout"){
                            cout << "comando invalido"<< endl;
                        }
                        cout << "done" << endl;
                    }catch(string e){
                        cout << e;
                    }

                }
            }

            if(login == "login"){
                auto cli = agencia.getcliente(read<string>());
                cout << "-----------------------------------" << endl;
                if(cli!= nullptr){

                    cout << "login" << endl
                         <<"logout"<< endl
                        <<"saldo" <<endl
                       <<"saque"<< endl
                      <<"extrato"<< endl
                     <<"deposito"<< endl
                    <<"myAccounts"<< endl ;

                    while(ui != "logout"){
                        cout <<"-----------------------"<< endl;
                        cin >> ui;
                        try{
                            if(ui == "myAccounts"){
                                cout << agencia.showcontas(read<string>());
                            }
                            else if(ui == "saldo"){
                                string cpf = "";
                                int num = 0;

                                cin >> cpf;
                                cin >> num;

                                cout << (agencia.getSaldo(cpf,num)) << " ";
                            }

                            else if(ui == "deposito"){
                                int num = 0, valor = 0;
                                string a = "";
                                cin >> a >> num >> valor;
                                agencia.getcliente(a)->getConta(num)->Despositar(valor);
                            }
                            else if(ui == "saque"){
                                int num = 0, valor = 0;
                                string nome = "";
                                cin >> nome >> num >> valor;
                                agencia.getcliente(nome)->getConta(num)->Sacar(valor);
                                //cout << end;
                            }
                            else if(ui == "transferir"){
                                int num = 0,other = 0;
                                float valor = 0;
                                string nome = "";
                                cin >> nome >>  num >> other >>valor;
                                agencia.getcliente(nome)->getConta(num)->Transferir(new Conta(other), valor);

                            }
                            else if(ui == "extrato"){
                                string nome = " ";
                                int num = 0;
                                cin >> nome >> num;
                                cout << agencia.extrato(nome ,num) << endl;
                            }
                            else if (ui !="logout"){
                                cout << "comando invalido"<< endl;
                            } else {
                                cout << "done" << endl;
                            }
                        }catch(string e){
                            cout << e;
                        }
                    }

                }else{
                    cout << "Usuario não existe\n";
                }
            }
        }
    }

};

int main(){
    Controle controle;
    controle.comandline();

}

