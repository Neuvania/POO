#ifndef WHATSERVICE_H
#define WHATSERVICE_H
#include <iostream>
#include <vector>
#include "repository.h"
#include "poo_aux.h"
#include <list>
#include "classes.h"

using namespace std;
using namespace poo;

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
    Repository <Chat*> r_Chat;
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
                    "newGroup $nome $nomeChat                     \n"
                    "newTalk $nome $nome2                         \n"
                    "zap $nome $nomeGp $msg                       \n"
                    "showChats $nome                              \n"
                    "invite $nomeAdm $nomeUser $nomeChat          \n"
                    "leave  $nomeUser $nomeChat                   \n"
                    "Users                                        \n"
                    "ler  $nomeUser $nomeChat                     \n"
                    "fim                                          \n";
        }
        else if(cmd == "addUser")
            this->r_User.add(ui[1],User(ui[1]));
        else if(cmd == "Users")
            return  poo::join(r_Chat.at(ui[1])->Users(), "\n");
        else if(cmd == "newGroup")
            this->r_Chat.addAt(ui[2], new Group(ui[2]))->newGroup(r_User.get(ui[1]));
        else if(cmd == "newTalk")
            this->r_Chat.addAt(ui[1]+ui[2],new Talk(ui[1]+ui[2]))->newTalk(r_User.get(ui[1]),r_User.get(ui[2]));
        else if(cmd == "showChats")
            return "Chats de " + r_User.get(ui[1])->getId() + ": [ "+ this->r_User.get(ui[1])->getChats() + " ]";
        else if(cmd == "fim")
            return "fim";
        else if(cmd == "invite"){
            int size = ui.size();
            for(int i = 2; i < (size - 1); i++)
                r_Chat.at(ui[size - 1])->addUser(r_User.get(ui[i]));
        }else if(cmd == "leave"){
            try{
                r_Chat.at(ui[2])->leave(r_User.get(ui[1]));
            }catch(...){
                cerr<< "Erro" <<endl;
            }
        }else  if(cmd == "zap"){
            try{
                r_User.get(ui[1])->sendZap(join(slice(ui,3), " "), ui[2]);
            }catch (const string& e){
                cout << e << endl;
            }
        }
        else if(cmd == "ler"){
            return poo::join(r_Chat.at(ui[2])->msg(ui[1]), "\n");
        }
        else
            return "Comando inválido";
        return "Done";
    }
};



#endif // WHATSERVICE_H
