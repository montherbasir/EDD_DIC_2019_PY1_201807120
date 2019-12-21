//
// Created by Monther on 11/12/2019.
//

#ifndef PROYECTO_1_EDD_MATRIZ_H
#define PROYECTO_1_EDD_MATRIZ_H

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "../Album.h"
#include <windows.h>
using namespace std;

template <class T>
class Nodo{
public:

    explicit Nodo(T *dato) : dato(*dato) {left = 0;
        right = 0;
        up = 0;
        down = 0;
        front = 0;
        back = 0;}

    Nodo *getLeft(){ return left;}
    Nodo *getRight(){ return right;}
    Nodo *getUp(){ return up;}
    Nodo *getDown(){ return down;}
    Nodo *getFront(){ return front;}
    Nodo *getBack(){ return back;}

    void setLeft(Nodo *n) { left = n;}
    void setRight(Nodo *n) { right = n;}
    void setUp(Nodo *n) { up = n;}
    void setDown(Nodo *n) { down = n;}
    void setFront(Nodo *n) { front = n;}
    void setBack(Nodo *n) { back = n;}
    T getDato(){ return dato;}

private:
    Nodo *left;
    Nodo *right;
    Nodo *up;
    Nodo *down;
    Nodo *front;
    Nodo *back;

    T dato;
};

template <class T>
class Matriz {

public:

    explicit Matriz(const string& artista)
    {
        auto *al = new Album(artista,"",-1,0, nullptr,0);
        root = new Nodo<Album>(al);
    }

    Nodo<T> *buscarFila(const string& nombre);
    Nodo<T> *buscarColumna(int anio);
    Nodo<T> *insertarColumna(int anio);
    Nodo<T> *insertarFila(const string &nombre);
    void imprimirCol();
    void imprimirFilas();
    void insertar(Album *album);
    string generarStringGraph();
    void imprimirAlbumes();
    Album buscarAlbum(const string& nombre);
    ListaDoble<Cancion*> *getAllCanciones();
private:
    Nodo<Album> *root;
    bool iequals(const string& a, const string& b);
    int getNoMes(const string& a);
    Nodo<Album> *insertarEnFila(Nodo<Album>* h_fila, Nodo<Album>* nodo);
    Nodo<Album> * insertarEnColumna(Nodo<Album>* h_col, Nodo<Album>* nodo);
    void imprimirNodo(Nodo<Album>* nodo);

};

template <class T>
Nodo<T>* Matriz<T>::buscarFila(const string& nombre){
    Nodo<Album> *aux = this->root;
    while(aux!=0){
        if(iequals(aux->getDato().getMes(), nombre)){
            return aux;
        }
        aux = aux->getDown();
    }
    return 0;
}

template <class T>
Nodo<T>* Matriz<T>::buscarColumna(int anio){
    Nodo<Album> *aux = this->root->getRight();
    while(aux!=0){
        if(aux->getDato().getAnio()==anio){
            return aux;
        }
        aux = aux->getRight();
    }
    return 0;
}

template <class T>
Nodo<T>* Matriz<T>::insertarColumna(int anio){

    Nodo<Album>* aux = buscarColumna(anio);
    if(aux!=0){
        return aux;
    }

    auto *temp = new Nodo<Album>(new Album(to_string(anio),"mes",anio,0, nullptr,0));

    aux = this->root;
    while(aux->getRight()!=0){
        aux = aux->getRight();
        if(anio<aux->getDato().getAnio()){
            aux->getLeft()->setRight(temp);
            temp->setLeft(aux->getLeft());
            temp->setRight(aux);
            aux->setLeft(temp);
            return temp;
        }
    }

    aux->setRight(temp);
    temp->setLeft(aux);
    return temp;
}

template <class T>
Nodo<T>* Matriz<T>::insertarFila(const string &nombre){

    Nodo<Album>* aux = buscarFila(nombre);
    if(aux!=0){
        return aux;
    }

    auto *temp = new Nodo<Album>(new Album(nombre,nombre,0,0,nullptr,getNoMes(nombre)));
    //temp->getDato().setNom(getNoMes(nombre));
    //cout << "NOM" << to_string(temp->getDato().getNom()) << endl;
    aux = this->root;
    while(aux->getDown()!=0){
        aux = aux->getDown();
        if(temp->getDato().getNom()<aux->getDato().getNom()){
            aux->getUp()->setDown(temp);
            temp->setUp(aux->getUp());
            temp->setDown(aux);
            aux->setUp(temp);
            return temp;
        }
    }

    aux->setDown(temp);
    temp->setUp(aux);
    return temp;
}

template<class T>
void Matriz<T>::insertar(Album* album) {
    album->setNom(getNoMes(album->getMes()));
    auto *nodo = new Nodo<Album>(album);
    insertarEnFila(insertarFila(album->getMes()),nodo);
    insertarEnColumna(insertarColumna(album->getAnio()),nodo);
}

template<class T>
Nodo<Album>* Matriz<T>::insertarEnFila(Nodo<Album>* h_fila, Nodo<Album>* nodo) {
    if(h_fila->getRight()==0){
        h_fila->setRight(nodo);
        nodo->setLeft(h_fila);
        return nodo;
    }else{
        Nodo<Album> *aux = h_fila;
        while(aux->getRight()!=0){
            aux = aux->getRight();
            if(nodo->getDato().getAnio()<aux->getDato().getAnio()){
                aux->getLeft()->setRight(nodo);
                nodo->setLeft(aux->getLeft());
                nodo->setRight(aux);
                aux->setLeft(nodo);
                return nodo;
            }else if(nodo->getDato().getAnio()==aux->getDato().getAnio()){
                if(aux->getFront()==0){
                    aux->setFront(nodo);
                    nodo->setBack(aux);
                    return nodo;
                }
                aux->getFront()->setBack(nodo);
                nodo->setFront(aux->getFront());
                nodo->setBack(aux);
                aux->setFront(aux);
                return nodo;
            }
        }
        aux->setRight(nodo);
        nodo->setLeft(aux);
        return nodo;
    }
}

template<class T>
Nodo<Album>* Matriz<T>::insertarEnColumna(Nodo<Album>* h_col, Nodo<Album>* nodo) {
    if (h_col->getDown() == 0) {
        h_col->setDown(nodo);
        nodo->setUp(h_col);
        return nodo;
    } else {
        Nodo<Album> *aux = h_col;
        while (aux->getDown() != 0) {
            aux = aux->getDown();
            if (nodo->getDato().getNom() < aux->getDato().getNom()) {
                aux->getUp()->setDown(nodo);
                nodo->setUp(aux->getUp());
                nodo->setDown(aux);
                aux->setUp(nodo);
                return nodo;
            }else if(nodo->getDato().getNom()==aux->getDato().getNom()) {
                return nodo;
            }
        }
        aux->setDown(nodo);
        nodo->setUp(aux);
        return nodo;
    }
}

template <class T>
void Matriz<T>::imprimirCol(){
    Nodo<Album> *aux = this->root;
    while(aux!=0){
        cout << aux->getDato().getNombre() << " ";
        aux = aux->getRight();
    }
    cout<< endl;
}

template <class T>
void Matriz<T>::imprimirFilas(){
    Nodo<Album> *aux = this->root->getDown();
    while(aux!=0){
        cout << aux->getDato().getNombre() << endl;
        aux = aux->getDown();
    }
}

template <class T>
void Matriz<T>::imprimirAlbumes(){
    Nodo<Album> *aux = this->root->getRight();
    Nodo<Album> *aux2;
    Nodo<Album> *aux3;
    cout << "0: Salir" << endl;
    while(aux!=0){
        aux2=aux->getDown();
        while(aux2!=0){
            cout << aux2->getDato().getNombre() << endl;
            aux3 = aux2->getFront();
            while(aux3!=0){
                cout << aux3->getDato().getNombre() << endl;
                aux3 = aux3->getFront();
            }
            aux2 = aux2->getDown();
        }
        aux = aux->getRight();
    }
}

template <class T>
Album Matriz<T>::buscarAlbum(const std::string & nombre) {
    Nodo<Album> *aux = this->root->getRight();
    Nodo<Album> *aux2;
    Nodo<Album> *aux3;
    while(aux!=0){
        aux2=aux->getDown();
        while(aux2!=0){
            if(iequals(aux2->getDato().getNombre(),nombre)){
                return aux2->getDato();
            }
            aux3 = aux2->getFront();
            while(aux3!=0){
                if(iequals(aux3->getDato().getNombre(),nombre)){
                    return aux3->getDato();
                }
                aux3 = aux3->getFront();
            }
            aux2 = aux2->getDown();
        }
        aux = aux->getRight();
    }
    throw 0;
}

template <class T>
ListaDoble<Cancion*> *Matriz<T>::getAllCanciones(){
    auto* songs = new ListaDoble<Cancion*>();
    Lista<Cancion*> *canciones;
    Nodo<Album> *aux = this->root->getRight();
    Nodo<Album> *aux2;
    Nodo<Album> *aux3;
    while(aux!=0){
        aux2=aux->getDown();
        while(aux2!=0){
            canciones = aux2->getDato().getCanciones();
            for(int i = 0; i < canciones->getSize(); i++){
                songs->add_last(canciones->get_element_at(i));
            }
            aux3 = aux2->getFront();
            while(aux3!=0){
                canciones = aux3->getDato().getCanciones();
                for(int j = 0; j < canciones->getSize(); j++){
                    songs->add_last(canciones->get_element_at(j));
                }
                aux3 = aux3->getFront();
            }
            aux2 = aux2->getDown();
        }
        aux = aux->getRight();
    }
    return songs;
}

template <class T>
bool Matriz<T>::iequals(const string& a, const string& b)
{
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

template <class T>
int Matriz<T>::getNoMes(const string &a){
    if(iequals(a,"Enero")){
        return 1;
    }
    if(iequals(a,"Febrero")){
        return 2;
    }
    if(iequals(a,"Marzo")){
        return 3;
    }
    if(iequals(a,"Abril")){
        return 4;
    }
    if(iequals(a,"Mayo")){
        return 5;
    }
    if(iequals(a,"Junio")){
        return 6;
    }
    if(iequals(a,"Julio")){
        return 7;
    }
    if(iequals(a,"Agosto")){
        return 8;
    }
    if(iequals(a,"Septiembre")){
        return 9;
    }
    if(iequals(a,"Octubre")){
        return 10;
    }
    if(iequals(a,"Noviembre")){
        return 11;
    }
    if(iequals(a,"Diciembre")){
        return 12;
    }
    return 0;
}



template <class T>
void Matriz<T>::imprimirNodo(Nodo<Album>* nodo){
    cout<<"Nombre: "<<nodo->getDato().getNombre()<<endl;
    if(nodo->getLeft()!=0){
        cout<<nodo->getLeft()->getDato().getNombre();
    }else{cout<<0;}
    cout<<" : Left"<<endl;
    if(nodo->getRight()!=0){
        cout<<nodo->getRight()->getDato().getNombre();
    }else{cout<<0;}
    cout<<" : right"<<endl;
    if(nodo->getUp()!=0){
        cout<<nodo->getUp()->getDato().getNombre();
    }else{cout<<0;}
    cout<<" : up"<<endl;
    if(nodo->getDown()!=0){
        cout<<nodo->getDown()->getDato().getNombre();
    }else{cout<<0;}
    cout<<" : down"<<endl;
    if(nodo->getFront()!=0){
        cout<<nodo->getFront()->getDato().getNombre();
    }else{cout<<0;}
    cout<<" : front"<<endl;
    if(nodo->getBack()!=0){
        cout<<nodo->getBack()->getDato().getNombre();
    }else{cout<<0;}
    cout<<" : back"<<endl;
    cout<<endl;
}
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}
template <class T>
string Matriz<T>::generarStringGraph() {
    string graph = "digraph {\n"
                   "splines=\"line\";\n"
                   "rankdir = TB;\n"
                   "node [shape=record, height=0.5, width=1.5];\n"
                   "graph[dpi=300];\n\n";



    Nodo<Album> *aux = this->root;
    while(aux!=0){
        graph += "nodeY_"+removeSpaces(aux->getDato().getNombre())+" [label=\"<f0>"+aux->getDato().getNombre()+"\"];\n";
        aux = aux->getRight();
    }
    graph+="\n";

    aux = this->root->getDown();
    while(aux!=0){
        graph += "nodeM_"+removeSpaces(aux->getDato().getNombre())+" [label=\"<f0>"+aux->getDato().getNombre()+"\"];\n";
        aux = aux->getDown();
    }
    graph+="\n";

    aux = this->root->getDown();
    Nodo<Album> *aux2;
    Nodo<Album> *aux3;
    while(aux!=0){
        aux2=aux->getRight();
        while(aux2!=0){
            graph += "nodeV_"+removeSpaces(aux2->getDato().getMes()+to_string(aux2->getDato().getAnio()))+" [label=\"<f0>"+aux2->getDato().getNombre();
            aux3=aux2->getFront();
            while(aux3!=0){
                graph += " | <f1>"+aux3->getDato().getNombre();
                aux3 = aux3->getFront();
            }
            graph+="\"];\n";
            aux2 = aux2->getRight();
        }
        aux = aux->getDown();
    }
    graph+="\n";

    aux = this->root;
    while(aux->getRight()!=0){
        graph += "nodeY_"+removeSpaces(aux->getDato().getNombre())+":f0 -> nodeY_"+removeSpaces(aux->getRight()->getDato().getNombre())+":f0;\n";
        graph += "nodeY_"+removeSpaces(aux->getRight()->getDato().getNombre())+":f0 -> nodeY_"+removeSpaces(aux->getDato().getNombre())+":f0;\n";
        aux = aux->getRight();
    }
    graph+="\n";

    aux = this->root->getRight();
    while(aux!=0){
        aux2=aux->getDown();
        if(aux2!=0){
            graph += "nodeY_"+removeSpaces(aux->getDato().getNombre())+":f0 -> nodeV_"+removeSpaces(aux2->getDato().getMes()+to_string(aux2->getDato().getAnio()))+":f0;\n";
            graph += "nodeV_"+removeSpaces(aux2->getDato().getMes()+to_string(aux2->getDato().getAnio()))+":f0 -> nodeY_"+removeSpaces(aux->getDato().getNombre())+":f0;\n";
        }

        while(aux2->getDown()!=0){
            graph += "nodeV_"+removeSpaces(aux2->getDato().getMes()+to_string(aux2->getDato().getAnio()))+":f0 -> nodeV_"+removeSpaces(aux2->getDown()->getDato().getMes()+to_string(aux2->getDown()->getDato().getAnio()))+":f0;\n";
            graph += "nodeV_"+removeSpaces(aux2->getDown()->getDato().getMes()+to_string(aux2->getDown()->getDato().getAnio()))+":f0 -> nodeV_"+removeSpaces(aux2->getDato().getMes()+to_string(aux2->getDato().getAnio()))+":f0;\n";
            aux2 = aux2->getDown();
        }
        aux = aux->getRight();
    }
    graph+="\n";

    aux = this->root;
    if(aux->getDown()!=0){
        graph += "nodeY_"+removeSpaces(aux->getDato().getNombre())+":f0 -> nodeM_"+removeSpaces(aux->getDown()->getDato().getNombre())+":f0;\n";
        graph += "nodeM_"+removeSpaces(aux->getDown()->getDato().getNombre())+":f0 -> nodeY_"+removeSpaces(aux->getDato().getNombre())+":f0;\n";
        aux = aux->getDown();
    }
    while(aux->getDown()!=0){
        graph += "nodeM_"+removeSpaces(aux->getDato().getNombre())+":f0 -> nodeM_"+removeSpaces(aux->getDown()->getDato().getNombre())+":f0;\n";
        graph += "nodeM_"+removeSpaces(aux->getDown()->getDato().getNombre())+":f0 -> nodeM_"+removeSpaces(aux->getDato().getNombre())+":f0;\n";
        aux = aux->getDown();
    }
    graph+="\n";

    aux = this->root->getDown();
    while(aux!=0){
        aux2=aux->getRight();
        if(aux2!=0){
            graph += "nodeM_"+removeSpaces(aux->getDato().getNombre())+":f0 -> nodeV_"+removeSpaces(aux2->getDato().getMes()+to_string(aux2->getDato().getAnio()))+":f0[constraint=false];\n";
            graph += "nodeV_"+removeSpaces(aux2->getDato().getMes()+to_string(aux2->getDato().getAnio()))+":f0 -> nodeM_"+removeSpaces(aux->getDato().getNombre())+":f0[constraint=false];\n";
        }

        while(aux2->getRight()!=0){
            graph += "nodeV_"+removeSpaces(aux2->getDato().getMes()+to_string(aux2->getDato().getAnio()))+":f0 -> nodeV_"+removeSpaces(aux2->getRight()->getDato().getMes()+to_string(aux2->getRight()->getDato().getAnio()))+":f0[constraint=false];\n";
            graph += "nodeV_"+removeSpaces(aux2->getRight()->getDato().getMes()+to_string(aux2->getRight()->getDato().getAnio()))+":f0 -> nodeV_"+removeSpaces(aux2->getDato().getMes()+to_string(aux2->getDato().getAnio()))+":f0[constraint=false];\n";
            aux2 = aux2->getRight();
        }
        aux = aux->getDown();
    }
    graph+="\n";

    aux = this->root;
    graph += "{rank=same; ";
    while(aux!=0){
        graph += "nodeY_"+removeSpaces(aux->getDato().getNombre())+"; ";
        aux=aux->getRight();
    }
    graph+="}\n";

    aux = this->root->getDown();
    while(aux!=0){
        aux2=aux->getRight();
        graph += "{rank=same; ";
        graph += "nodeM_"+removeSpaces(aux->getDato().getNombre())+"; ";

        while(aux2!=0){
            graph += "nodeV_"+removeSpaces(aux2->getDato().getMes()+to_string(aux2->getDato().getAnio()))+"; ";
            aux2 = aux2->getRight();
        }
        aux = aux->getDown();
        graph+="}\n";
    }
    graph+="\n";

    graph+="}\n";

    ofstream myfile;
    myfile.open("matriz.dot");
    myfile << graph;
    myfile.close();
    system("dot -Tpng matriz.dot -o matriz.png");
    ShellExecute(NULL, "open", "matriz.png", NULL, NULL, SW_NORMAL);

    //C:\Users\Monther\Downloads\Library.json
    //C:\Users\Monther\Downloads\Playlist_Rock.json
    //C:\Users\Monther\Documents\plccc.json
}



#endif //PROYECTO_1_EDD_MATRIZ_H
