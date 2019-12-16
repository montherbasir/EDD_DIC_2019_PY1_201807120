//
// Created by Monther on 9/12/2019.
//

#ifndef UNTITLED_COLA_H
#define UNTITLED_COLA_H
#include "Lista.h"

template<class T>
class Cola{
public:
    void queue(T dato);
    T dequeue();
    int getSize(){return this->lista->getSize();}
    Cola(){
        this->lista = new Lista<T>();
    }
private:
    Lista<T> *lista;
};

template<class T>
void Cola<T>::queue(T dato)
{
    this->lista->add_first(dato);
}

template<class T>
T Cola<T>::dequeue()
{
    int x = this->lista->getSize()-1;
    T dato = this->lista->get_element_at(x);
    this->lista->remove_at(x);
    return dato;
}

#endif //UNTITLED_COLA_H
