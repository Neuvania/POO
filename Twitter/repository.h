#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <iostream>
#include <map>
#include<vector>

using namespace std;

template <class T>
class Repository {
    map<string, T> _mapa;
    string nomeTipo;
public:
    Repository(string nomeTipo = ""){
        this->nomeTipo = nomeTipo;
    }

    T * add(string key, T t){
        if(_mapa.count(key) == 1)
            throw nomeTipo + " " + key + " ja existe";
        _mapa[key] = t;
        return &_mapa[key];
    }

    bool has(string key){
        return _mapa.count(key);
    }

    void rm(string key){
        if(!_mapa.erase(key))
            throw nomeTipo + " " + key + " nao existe";
    }

    T * get(string key){
        if(_mapa.count(key) == 0)
            throw nomeTipo + " " + key + " nao existe";
        return &_mapa[key];
    }

    T& at(string key){
        if(_mapa.count(key) == 0)
            throw nomeTipo + " " + key + " nao existe";
        return _mapa[key];
    }

    vector<T> values(){
        vector<T> vet;
        for(auto& par : _mapa)
            vet.push_back(par.second);
        return vet;
    }

    vector<string> keys(){
        vector<string> vet;
        for(auto& par : _mapa)
            vet.push_back(par.first);
        return vet;
    }
};

#endif // REPOSITORY_H
