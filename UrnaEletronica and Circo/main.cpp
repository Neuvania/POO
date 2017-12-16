#include <iostream>
#include <vector>

using namespace std;

class Pessoa {
public :

    string nome;
    int idade;
    int titulo;
    int voto;
    Pessoa(string nome ,int idade , int titulo, int voto = NULL){

        this->nome = nome;
        this->idade = idade;
        this->titulo = titulo;
        this->voto = voto;

    }
};

class Candidato{
public:
    string nome;
    string nvice;
    string partido;
    int num;
    int totvoto;



    Candidato(string nome, string nvice , string partido , int num){

        this->nome = nome;
        this->nvice = nvice;
        this->partido = partido;
        this->num = num;
        this->totvoto = 0;

    }

    void votar(vector<Pessoa> vetor){

        for (int i = 0; i < vetor.size(); i++){
            if (this->num == vetor[i].voto){
                totvoto += 1;
            }
        }


    }


};
int main(){

    int votobranco = 0;
    int p=0;

    string op = "inicio";
    vector <Candidato> polit = {Candidato("Lula     ", "Dilma", "pt", 40), Candidato("Bolsonario", "Aecio", "Psdb", 30)};
    vector <Pessoa> popul = {Pessoa("neu", 20, 1000020, 40),Pessoa ("jose", 45, 86654454, 40), Pessoa("Joshua", 20, 2000, 30),Pessoa("maria", 34,23444)};



    for(Pessoa &pessoa :popul )
        if(pessoa.voto == NULL)
            votobranco += 1;

    cout << "ELEICOES 2018 PRESIDENCIA" << " " << endl << endl;
    cout << "CANDIDATOS " << "\tVICE " << "\t\tPARTIDO " << "\tNUMERO " << endl;
    for(Candidato candi_2018 : polit)


        cout << candi_2018.nome << "\t"<< candi_2018.nvice << "\t "<< "\t   "<<candi_2018.partido<< "\t\t  "<< candi_2018.num <<endl;
    cout <<"\nDIGITE 'RESULTADO'" << endl;

    do{

        cin >> op;
        cout << endl;

        if (op == "resultado"){
            cout << "RESULTADO DAS ELEIÇÕES 2018" << endl;

            for( Candidato &candidato : polit)
                candidato.votar(popul);
            for(Candidato &candidato : polit)
                cout << candidato.nome<< " " <<candidato.totvoto<< " " << endl;
            cout << "TOTAL BRANCOS:" << votobranco << endl;



        }

    }while(op != "fim");

}


