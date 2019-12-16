//
// Created by Monther on 11/12/2019.
//

#ifndef PROYECTO_1_EDD_MATRIZ_H
#define PROYECTO_1_EDD_MATRIZ_H

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../Album.h"
using namespace std;

template <class T>
class Nodo{
public:

    Nodo(T *dato) : dato(*dato) {left = 0;
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

    Matriz(const string& artista)
    {
        Album *al = new Album(artista,"",-1, nullptr);
        root = new Nodo<Album>(al);
    }

    Nodo<T> *buscarFila(const string& nombre);
    Nodo<T> *buscarColumna(int anio);
    Nodo<T> *insertarColumna(int anio);
    Nodo<T> *insertarFila(const string &nombre);
    void imprimirCol();
    void imprimirFilas();
    void insertar(Album *album);
private:
    Nodo<T> *root;
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

    auto *temp = new Nodo<Album>(new Album(to_string(anio),"mes",anio, nullptr));

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

    auto *temp = new Nodo<Album>(new Album(nombre,nombre,getNoMes(nombre), nullptr));

    aux = this->root;
    while(aux->getDown()!=0){
        aux = aux->getDown();
        if(temp->getDato().getAnio()<aux->getDato().getAnio()){
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
    auto *nodo = new Nodo<Album>(album);
    insertarEnFila(insertarFila(album->getMes()),nodo);
    imprimirNodo(insertarEnColumna(insertarColumna(album->getAnio()),nodo));
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
            if (nodo->getDato().getAnio() < aux->getDato().getAnio()) {
                aux->getUp()->setDown(nodo);
                nodo->setUp(aux->getUp());
                nodo->setDown(aux);
                aux->setUp(nodo);
                return nodo;
            }else if(nodo->getDato().getAnio()==aux->getDato().getAnio()) {
                return nodo;
            }
            aux->setDown(nodo);
            nodo->setUp(aux);
            return nodo;
        }
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
    if(iequals(a,"enero")){
        return 1;
    }
    if(iequals(a,"febrero")){
        return 2;
    }
    if(iequals(a,"marzo")){
        return 3;
    }
    if(iequals(a,"abril")){
        return 4;
    }
    if(iequals(a,"mayo")){
        return 5;
    }
    if(iequals(a,"junio")){
        return 6;
    }
    if(iequals(a,"julio")){
        return 7;
    }
    if(iequals(a,"agosto")){
        return 8;
    }
    if(iequals(a,"septiembre")){
        return 9;
    }
    if(iequals(a,"octubre")){
        return 10;
    }
    if(iequals(a,"noviembre")){
        return 11;
    }
    if(iequals(a,"diciembre")){
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


#endif //PROYECTO_1_EDD_MATRIZ_H
