//
// Created by Monther on 9/12/2019.
//

#ifndef UNTITLED_PILA_H
#define UNTITLED_PILA_H
#include "Lista.h"

template<class T>
class Pila{
public:
    void push(T dato);
    T pop();
    int getSize(){return this->lista->getSize();}
    Pila(){
        this->lista = new Lista<T>();
    }
private:
    Lista<T> *lista;
};

template<class T>
void Pila<T>::push(T dato)
{
    this->lista->add_first(dato);
}

template<class T>
T Pila<T>::pop()
{
    T dato = this->lista->get_element_at(0);
    this->lista->remove_at(0);
    return dato;
}

#endif //UNTITLED_PILA_H
