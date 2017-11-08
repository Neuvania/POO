#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "poo_aux.h"
#include"repository.h"
#include"classes.h"
#include "iostream"

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

            if((line == "" ) || (line.substr(0, 2) == "  "))
                continue;
            cout << line << endl;
            if(line[0] == '#')
                continue;
            try {
                string resp = this->process(line);
                cout << tab(resp) << endl;
            } catch(const string& e) {
                cout << tab(e) << endl;
            }
        }
    }
};


class TService: public Controller{

    Repository<Tweet> r_tw;
    Repository<User> r_user;
    TweetGenerator twgen;
    int nextid;
public:

    TService():
        r_user("Usuario"), r_tw("Tweet"), twgen(&r_tw)
    {}

    string process(string line){
        auto ui = split(line);
        auto cmd = ui[0];
        if(cmd == "help"){
            return  "help                                               \n"
                    "users                                              \n"
                    "addUser    _nome                                   \n"
                    "seguir     _nome _outro                            \n"
                    "twittar    _nome _(mensagem com varias palavras)   \n"
                    "like       _nome                                   \n"
                    "seguidores _nome                                   \n"
                    "seguidos   _nome                                   \n"
                    "timeline   _nome                                   \n"
                    "myTweets   _nome                                   \n"
                    "unread     _nome                                   \n" ;

        }
        else if(cmd == "addUser")
            this->r_user.add(ui[1], User(ui[1]));
        else if(cmd == "users")
            return "usuarios\n[ " + join(this->r_user.keys(), " ") + "]";
        else if(cmd == "seguir")
            this->r_user.get(ui[1])->seguir(this->r_user.get(ui[2]));
        else if(cmd == "twittar"){
            auto msg = join(slice(ui, 2), " ");
            this->r_user.get(ui[1])->twittar(twgen.creat(ui[1], msg));
        }else if (cmd == "seguidores"){
            auto seguidores = this->r_user.get(ui[1])->getseguidores();
            return "[" + join(seguidores, " ") + "]";
        }else if(cmd == "seguidos"){
            auto seguidos = this->r_user.get(ui[1])->getseguidos();
            return "[" + join(seguidos, " ") + "]";
        }else if(cmd == "timeline"){
            auto timeline = this->r_user.get(ui[1])->getTimeline();
            return "Timeline\n" + pjoin(timeline, "\n");
        }else if(cmd == "unread"){
            auto unread = this->r_user.get(ui[1])->getUnread();
            return "Unread\n" + pjoin(unread, "\n");
        }else if(cmd == "myTweets"){
            auto tweets = this->r_user.get(ui[1])->getMyTweeet();
            return "MyTweets\n" + pjoin(tweets, "\n");
        }else if(cmd == "like"){
            auto timeline = this->r_user.get(ui[1])->getTimeline();
            for(auto tweet : timeline)
                if(tweet->getIdTw() == Int(ui[2]))
                    tweet->addLike(ui[1]);

        }else if(cmd == "fim")
            return "fim";
        else
            return "Comando inválido";
        return "Done";
    }

};


#endif // CONTROLLER_H
