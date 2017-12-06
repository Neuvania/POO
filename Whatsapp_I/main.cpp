#include <iostream>
#include <vector>
#include "repository.h"
#include "poo_aux.h"
#include <list>

using namespace std;
using namespace poo;

class Zap{
    string id;
    string Msg;
public:
    Zap(string userId = "", string Msg = ""){
        this->id = userId;
        this->Msg =  Msg;
    }
    string getUserId(){
        return this->id;
    }
    string toString(){
        return "[ " + id + ": " + Msg + " ]\n";
    }
    TO_OSTREAM(Zap)
};

class Chat;
class Registro;

class User{
    string id;
    vector<Chat*> chats;
public:
    User(string id = " "){
        this->id = id;
    }
    string getId(){
        return this->id;
    }
    string getChats();

    void invite(string chat, User * users);
    void leave(string nome);
    void sendZap(string msg, string IdChat);

    string toString(){
        return id;
    }
    TO_OSTREAM(User)
    friend class Chat;
};

class Registro{
    User * user;
    int conta{0};

public:
    Registro(User * user = nullptr) {
        this->user = user;
    }

    int getConta(){
        return this->conta;
    }

    void addConta(int qtd){
        this->conta += qtd;
    }

};

class Chat{
    int unreadCont = 0;
    string id;
    vector<Zap> list_zap;
    map<string, Registro> list_reg;

public:
    Chat(string chatId = "") {
        this->id = chatId;
    }
    bool addFirstUser(User * chatCreator){
        list_reg[chatCreator->id] = Registro(chatCreator);
        chatCreator->chats.push_back(this);
        return true;
    }

    string getChatId(){
        return id;
    }
    string getOverview(){
        return id;
    }
    void deliverZap(Zap  zap){
        list_zap.push_back(Zap(zap));
        for(auto &elem : list_reg){
            if(zap.getUserId() != elem.first)
                elem.second.addConta(1);
        }
    }

    vector<Zap> getUnread(){
        vector <Zap> naolidos;
        int cont = 0;
        for(auto elem :list_reg){
            // naolidos.push_back(elem);
            cont++;
            if(cont == unreadCont)
                break;
        }
        unreadCont = 0;
        return naolidos;
    }

    friend class User;
};

string User::getChats(){
    stringstream saida;
    for(auto par : chats){
        saida << par->getChatId() + ", ";
    }
    return saida.str();
}

void User::invite(string chat, User * users){
    for(auto &elem : chats){
        if(elem->id == chat){
            elem->list_reg[users->id] = Registro(users);
            users->chats.push_back(elem);

        }
    }
}
void User::leave(string nome){
    for(int i = 0; i < (int) chats.size(); i++){
        if(nome == chats[i]->id){
            this->chats.erase(chats.begin() + i);
            chats[i]->list_reg.erase(this->id);
        }
    }
}

void User::sendZap(string msg, string IdChat){
    for(auto *elem : chats){
        if(IdChat == elem->id){
            elem->deliverZap(msg);
        }
    }
}

class Controller{
public:
    virtual string process(string line){
        return line;
    }

    void commandLine() {
        cout << "Digite help, cmd ou fim:" << endl;
        string line = " ";
        while(line != "fim"){
            getline(cin, line);

            if((line == "" ) || (line.substr(0, 2) == " "))
                continue;
            cout << line << endl;
            if(line[0] == '*')
                continue;
            try {
                string resp = this->process(line);
                cout << tab(resp, " >> ") << endl;
            } catch(const string& e) {
                cout << tab(e," ") << endl;
            }
        }
    }
};

class Whatsapp : public Controller{
    Repository <User> r_User;
    Repository <Chat> r_Chat;

public:
    Whatsapp():
        r_User("User"),
        r_Chat("Chat")
    {

    }

    string process(string line){
        auto ui = split(line);
        auto cmd = ui[0];

        if(cmd == "help"){
            return  "help                                         \n"
                    "addUser $nome                                \n"
                    "newChat $nome $nomeChat                      \n"
                    "zap $nome $nomeGp $msg                       \n"
                    "showChats $nome                              \n"
                    "invite $nomeAdm $nomeUser $nomeChat          \n"
                    "deleave  $nomeUser $nomeChat                 \n"
                    "Users                                        \n"
                    "ler  $nomeUser $nomeChat                     \n"
                    "fim                                          \n";
        }
        else if(cmd == "addUser")
            this->r_User.add(ui[1],User(ui[1]));
        else if(cmd == "Users")
            return "Usuarios\n[ " +join(this->r_User.keys(),", ") + "]";
        else if(cmd == "newChat")
            this->r_Chat.add(ui[2], Chat(ui[2]))->addFirstUser(r_User.get(ui[1]));
        else if(cmd == "showChats")
            return "Chats de " + r_User.get(ui[1])->getId() + ": [ "+ this->r_User.get(ui[1])->getChats() + " ]";
        else if(cmd == "fim")
            return "fim";
        else if(cmd == "invite"){
            int size = ui.size();
            for(int i = 2; i < (size - 1); i++)
                r_User.get(ui[1])->invite(ui[size - 1], r_User.get(ui[i]));
        }else if(cmd == "deleave")
            r_User.get(ui[1])->leave(ui[2] );
        else if(cmd == "zap")
            r_User.get(ui[1])->sendZap(join(slice(ui, 3), " "), ui[2]);
        else if(cmd == "ler"){

        }
        else
            return "Comando inválido";
        return "Done";


    }


};

int main(){
    Whatsapp w;
    w.commandLine();
}
