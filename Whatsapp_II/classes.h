#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <vector>
#include "repository.h"
#include "poo_aux.h"
#include <list>
#include <stdexcept>


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
    string getMsg(){
        return "[" +  id + ": " + Msg + "]" ;
    }

    friend class Chat;
};

class Chat;
class Registro;

class User{
public:
    string id;
    vector<Chat*> chats;


    User(string id = " "){
        this->id = id;
    }

    string getId(){
        return this->id;
    }
    string getChats();

    virtual void sendZap(string msg, string IdChat);

    friend class Chat;
};

class Registro{
public:
    User * user;

    Registro(User * user = nullptr) {
        this->user = user;
    }
    string getUser(){
        return user->getId();
    }
};
class Chat{
protected:
    string id;
    vector<Zap> list_zap;
    map<string, Registro> list_reg;
public:
    Chat(string chatId = "") {
        this->id = chatId;
    }
    vector<Zap> getlist_zap(){
        return list_zap;
    }
    vector<Registro>getLista_reg(){
        return poo::map_values(list_reg);
    }
    string getChatId(){
        return id;
    }
    map<string,Registro>getLista_r(){
        return list_reg;
    }

    void addUser(User *user);
    vector<string> msg(string nomeUser){
        vector <string> msg;
        for(auto elem : list_reg)
            if(elem.first == nomeUser){
                for(auto coisa : list_zap){
                    msg.push_back(coisa.getMsg());
                }
            }
        if(list_reg.count(nomeUser) == 0)
            msg.push_back("você nao possui esse grupo");

        return msg;
    }

    void deliverZap(Zap  zap){
        list_zap.push_back(Zap(zap));
    }
    virtual void newTalk(User * user1, User * user2);
    virtual void newGroup(User * user1);
    virtual void leave(User* User);

    vector<string>Users(){
        vector<string>users;
        for(auto elem : getLista_reg()){
            users.push_back(elem.getUser());
        }
        return users;
    }

    friend class User;
};

class Talk : public Chat{
public:
    Talk(string id = ""):
        Chat(id)
    {}
    void leave(User* user){
        throw "erro";
    }
    void addUser(User* user){
        throw "erro";
    }
};

class Group : public Chat{
public:
    Group(string id = ""):
        Chat(id)
    {}

};
void Chat::leave(User* user){
    for(auto elem : list_reg)
        if(user->id == elem.first){
            for(int i = 0; i < (int) elem.second.user->chats.size(); i++){
                if(id == user->chats[i]->id){
                    user->chats.erase(user->chats.begin() + i);
                    list_reg.erase(elem.first);
                }
            }
        }


 }
void Chat::newGroup(User * user){
    list_reg[user->id] = user;
    user->chats.push_back(this);
}
void Chat::newTalk(User *user1, User *user2){
    list_reg[user1->id] = user1;
    list_reg[user2->id] = user1;
    user1->chats.push_back(this);
    user2->chats.push_back(this);
}
void Chat::addUser(User *user){
    list_reg[user->id] = user;
    user->chats.push_back(this);
}
string User::getChats(){
    stringstream saida;
    for(auto &elem : chats){
        saida << elem->getChatId() + ", ";
    }
    return saida.str();
}
void User::sendZap(string msg, string IdChat){
    for(auto &elem : chats)
        if(IdChat == elem->id){
            elem->deliverZap(Zap(id,msg));
        }
}

#endif // CLASSES_H
