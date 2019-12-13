//
// Created by Monther on 11/12/2019.
//

#ifndef PROYECTO_1_EDD_MATRIZ_H
#define PROYECTO_1_EDD_MATRIZ_H

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Album.h"
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
    Nodo<T> *insertarFila(const string& nombre);
    void imprimirCol();
    void imprimirFilas();
    //void add_first(T dato);
    //void add_last(T dato);
    //void add_at(T dato, int index);
    //T get_element_at(int index);
    //void remove_at(int index);
private:
    Nodo<T> *root;
};

template <class T>
Nodo<T>* Matriz<T>::buscarFila(const string& nombre){
    Nodo<Album> *aux = this->root;
    while(aux!=0){
        if(aux->getDato().getMes()==nombre){
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
Nodo<T>* Matriz<T>::insertarFila(const string& nombre){

    Nodo<Album>* aux = buscarFila(nombre);
    if(aux!=0){
        return aux;
    }

    auto* temp = new Nodo<Album>(new Album(nombre,nombre,0,new Lista<Cancion>()));

    aux = this->root->getDown();
    if(aux!=0) {
        this->root->setDown(temp);
        temp->setUp(this->root);
        temp->setDown(aux);
        aux->setUp(temp);
        return temp;
    }

    temp->setUp(this->root);
    this->root->setDown(temp);
    return temp;
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


#endif //PROYECTO_1_EDD_MATRIZ_H
