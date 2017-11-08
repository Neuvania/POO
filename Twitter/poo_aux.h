#ifndef POO_AUX_H
#define POO_AUX_H
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <list>

using namespace std;

namespace poo {

template <class T>
T cast(string palavra){
    T value;
    stringstream(palavra) >> value;
    return value;
}

inline int Int(string word){
    return cast<int>(word);
}

inline int Float(string word){
    return cast<float>(word);
}

vector<string> split(const string& text, char sep = ' '){
    vector<string> saida;
    istringstream ss(text);
    string token;
    while(getline(ss, token, sep))
        saida.push_back(token);
    return saida;
}

string tab(string data, string prefix = "  "){
    auto linhas = split(data, '\n');
    string saida = "";
    for(auto& line : linhas)
        saida += prefix + line + "\n";
    if(saida.size() > 0)
        saida.pop_back();//remove a ultima \n
    return saida;
}

template<class T>
vector<T> slice(vector<T>& vet, int vbegin = 0, int vend = -1){
   vector<T> new_vet;
    int size = vet.size();
    if(vend == -1)
        vend = size;
    for(int i = vbegin; i < vend; i++)
        new_vet.push_back(vet[i]);
    return new_vet;
}

template<class K, class T>
vector<T> map_values(map<K, T> &mapa){
    vector<T> vet;
    for(auto& par: mapa)
        vet.push_back(par.second);
    return vet;
}

template<class K, class T>
vector<K> map_keys(map<K, T> &mapa){
    vector<K> vet;
    for(auto& par: mapa)
        vet.push_back(par.first);
    return vet;
}

template <typename T>
string to_string(const T& value) {
   ostringstream os;
    os << value;
    return os.str();
}

template<class T>
vector<T> to_values(vector<T*> v_ref){
   vector<T> vet;
    for(int i = 0; i < (int) v_ref.size(); i++)
        vet.push_back(*v_ref[i]);
    return vet;
}

template<class T>
string join(vector<T> vet, string separ){
stringstream ss;
    for(int i = 0; i < (int) vet.size() - 1; i++)
        ss << vet[i] << separ;
    if(vet.size() > 0)
        ss << vet.back();
    return ss.str();
}

template<class T>
string pjoin(vector<T*> vet, string separ){
    return join(to_values<T>(vet), separ);
}

template<class T>
string join(list<T> lista, string separ){
    return join(vector<T>(lista.begin(), lista.end()), separ);
}

template<class T>
string pjoin(list<T*> lista, string separ){
    return pjoin(vector<T*>(lista.begin(), lista.end()), separ);
}

}

#endif // POO_AUX_H
