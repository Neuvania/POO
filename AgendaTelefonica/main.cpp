#include <iostream>
#include <vector>
#include <cstring>
#include<sstream>
#include <algorithm>


using namespace std;
template <class T>
T read(){
    T t;
    cin >> t;
    return t;
}
class Fone{
public:
    string id;
    string numero;

    Fone(string id = "casa", string numero = " "):
        id(id),numero(numero)
    {

    }

    static bool validate(string numero){
        string tipos ="0123456789-() ";
        for(auto elem : numero){
            if(tipos.find(elem) ==  string::npos){
                return false;
            }
        }

        return true;
    }
};

class Contato{
    string nome;
    vector<Fone>fones;
public :
    Contato(string nome = " "):
        nome(nome)
    {}

    vector<Fone> getFone(){
        return fones;
    }

    string getnome(){
        return this->nome;
    }/*
    vector<fones> getfones(){
        return fones;
    }*/
    bool AddFone(Fone fone){
        for (auto elem : fones){
            if(elem.id == fone.id){
                cerr<< "Idduplicado\n";
                return false;
            }
            if(elem.numero == fone.numero){
                cerr <<"Numero duplicado\n";
                return false;
            }
        }
        fones.push_back(Fone(fone));
        return true;
    }
    bool rmFone(string fone){
        for (int i = 0; i < (int)fones.size(); i++){
            if (fones[i].numero == fone){
                fones.erase(fones.begin() + i);
                return true;
            }
        }
        return false;

    }
    bool match(/*string pattern*/){
        return true;
    }
    string tostring() {

        stringstream ss;
        ss << "NOME:" << getnome()<<" " <<"Fones:";
        for(auto &elem : fones){
            ss <<" " << elem.id<< " "<<elem.numero <<endl;
        }
        return ss.str();
    }

    string toFavoritos(){
        stringstream ci;
        ci << "NOME: " << getnome() << " " << endl;
        return ci.str();
    }

    bool havematch(string pattern){
        string serial = this->tostring();
        if(serial.find(pattern) != string::npos)
            return true;

        return false;
    }


};

class Agenda{
    vector<Contato> contatos;
    vector <Contato> favoritos;
public:

    //    string ordenados (){
    //        stringstream os;
    //        os << cont.getnome() << endl;
    //        return os.str();
    //    }

    static bool compararContato(Contato a, Contato b){
        return a.getnome() < b.getnome();
    }
    vector<Contato> getcontatos(){
        std::sort(contatos.begin(),contatos.end(), compararContato);
        return contatos;
    }
    Contato * getcontato(string nome){
        for(auto &elem : contatos)
            if(elem.getnome() == nome){
                return &elem;
            }
        return nullptr;

    }
    vector<Contato> getfavorits(){
        return favoritos;
    }
    bool addContato(Contato contato){
        for(auto elem : contatos)
            if(elem.getnome() == contato.getnome())
                return false;
        contatos.push_back(contato);
        return true;
    }
    bool rmContato(string nome){

        for(int i = 0; i < (int)contatos.size(); i++){
            if(contatos[i].getnome() == nome){
                for(int j = 0; j < (int)favoritos.size(); j++){
                    if(favoritos[i].getnome() == nome){
                        contatos.erase(contatos.begin() + j);
                        favoritos.erase(favoritos.begin() + j);
                        return true;
                    }
                }
                contatos.erase(contatos.begin() + i);
                return true;
            }


        }
        return false;
    }


    vector<Contato> search(string pattern){
        vector<Contato> encontrados;
        for(auto elem : contatos)
            if(elem.havematch(pattern))
                encontrados.push_back(elem);
        return encontrados;

        //            string texto = cont->toString();
        //            if(texto.find(pattern) != string::npos){
    }

    bool favoritar(string nome){
        for(auto elem : contatos){
            if(elem.getnome() == nome){
                favoritos.push_back(nome);
                return true;
            }
        }
        return false;
    }
    bool desfavoritar(string nome){
        for(int i = 0; i < (int)contatos.size(); i++){
            if(contatos[i].getnome() == nome){
                favoritos.erase(favoritos.begin() + i);
                return true;
            }
        }
        return false;

    }
    string toString(){
        stringstream in;
        cout << "------------------Agenda-----------------------"<< endl;
        cout << "Foram encontrado(s) " << getcontatos().size() << " contato(s) em sua agenda" <<endl;
        for(auto &elem: contatos)
            cout << elem.tostring();
        return in.str();
    }
    string listafavoritos(){
        stringstream in;
        cout << "Foram encontrados " << getfavorits().size()<< " favoritos em sua agenda" << endl;
        for(auto &elem : favoritos)
            cout << elem.toFavoritos();
        return in.str();
    }

};
void comandline(){
    string op;
    Agenda agenda;

    cout << "                             MENU"
         <<   "\n-----------------------------------------------------------------"<< endl;
    cout <<"addContato $contato" << endl <<"rmContato $Nome" << endl <<"addFone $NomeContato $Id $Numero" << endl
        <<"rmFone $Nome" << endl<<"showContatos" << endl <<"buscar $Pattern" << endl
       <<"favoritar $Nome" << endl <<"showfavoritos" << endl <<"showOrdenados" << endl;
    cout << "-----------------------------------------------------------------"<< endl;
    while(op != "sair"){
        cin >> op;
        if(op == "addContato"){
            cout << (agenda.addContato(Contato(read<string>()))? "Contato adicionado\n" : "Contato já existe\n");
        }
        if(op == "rmContato"){
            cout <<(agenda.rmContato(read<string>()) ? "Contato removido\n" : "Contato não existe\n");
        }
        if(op == "showContatos"){
            cout << agenda.toString();
        }
        if(op == "addFone"){
            Fone f;
            string nome,num, id;
            cin >> nome >> id >> num;
            auto contato = agenda.getcontato(nome);
            if(f.validate(num) == false){
                cerr<< "numero com formato incorreto\n";
                continue;
            }
            if(!contato){
                cerr<<"contato nao existe\n"<< endl;
                continue;
            }
            cout <<(contato->AddFone(Fone(id,num))   ? "Telefone adicionado\n": "ERRO\n") ;
        }
        if(op == "rmFone"){
            string nome, num ,id;
            cin >> nome >> num >> id;

            auto contato =  agenda.getcontato(nome);
            if(!contato){
                cerr<< "Contato não existe\n" << endl;
            }
            cout<<(contato->rmFone(num)?"ok\n" : "erro\n");
        }
        if(op =="favoritar"){
            cout << (agenda.favoritar(read<string>())? "Adicionado\n" : "erro");
        }
        if(op =="desfavoritar"){
            cout <<(agenda.desfavoritar(read<string>()) ? "ok\n" : "erro\n");
        }
        if(op == "showFavoritos"){

            cout << agenda.listafavoritos();
        }
        if(op == "busca"){
            string pattern;
            cin >> pattern;
            for(auto elem : agenda.search(pattern))
                cout << elem.tostring() << endl;
        }
        if(op == "showOrdenados"){

            cout << agenda.toString();

        }

    }

}
int main(){
    comandline();
}
