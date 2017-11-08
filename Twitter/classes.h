#ifndef CLASSES
#define CLASSES
#include <iostream>
#include<list>
#include"poo_aux.h"
#include "controller.h"
#include "repository.h"


using namespace std;

class Tweet{

    int idTw;
    string name;
    string msg;
    list<string> likes;

public:
    Tweet(int idTw = 0, string name = "",  string msg = ""){
        this->idTw = idTw;
        this->name = name;
        this->msg = msg;
    }

    int getIdTw(){
        return this->idTw;
    }
    string getName(){
        return this->name;
    }
    string getMsg(){
        return this->msg;
    }
    list<string> getLikes(){
        return this->likes;
    }

    void addLike(string nome){
        for(auto ele : likes){
            if(ele ==  nome){
                return;
            }
            likes.push_back(nome);
        }
    }
    string toString(){
        string saida = to_string(idTw);
        saida += " " + name + ": " + msg;
        if(likes.size() > 0)
            saida += "{ " + poo::join(likes, " ") + "}";
        return saida;
    }

    friend ostream& operator <<(ostream&  os, Tweet tweet){
        os << tweet.toString();
        return os;
    }
};

class User{
    string name;
    int unreadCount;
    list<User*> seguidores;
    list<User*> seguidos;
    list<Tweet*> Timeline;
    list<Tweet*> myTweets;
public:
    User(string name = ""){
        this->name = name;
    }

    list<Tweet*> getTimeline(){
        unreadCount = 0;
        return Timeline;

    }
    list<Tweet*> getMyTweeet(){
        return myTweets;
    }
    list<Tweet*> getUnread(){
        list<Tweet*> naoLidos;
        int cont = 0;
        for(auto elem : Timeline){
            naoLidos.push_back(elem);
            cont++;
            if(cont == unreadCount)
                break;
        }
        unreadCount = 0;
        return naoLidos;
    }
    list<User*> getseguidores(){
        return seguidores;
    }
    list<User*> getseguidos(){
        return seguidos;
    }


    void seguir(User * user){
        for(auto elem : seguidos)
            if(elem->name == user->name)
                return;
        seguidos.push_back(user);
        user->seguidores.push_back(this);
    }

    void twittar(Tweet * tweet){
        myTweets.push_front(tweet);
        for(User * elem : seguidores)
            elem->Timeline.push_front(tweet);
    }
    friend ostream& operator<<(ostream &os, User user){
          os << user.name;
          return os;
  }
};
class TweetGenerator{
    Repository<Tweet> * r_tw;
    int nextId;
public:
    TweetGenerator(Repository<Tweet> * r_tw){
        this->r_tw = r_tw;
    }

    Tweet * creat(string name, string msg){
        int id = nextId++;
        return r_tw->add(to_string(id), Tweet(id, name, msg));
    }
};


#endif // CLASSES

