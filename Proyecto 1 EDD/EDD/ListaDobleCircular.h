//
// Created by Monther on 17/12/2019.
//

#ifndef UNTITLED_LISTADOBLECIRCULAR_H
#define UNTITLED_LISTADOBLECIRCULAR_H

template<class T>
class ListaDobleCircular
{
    class Nodo{
    public:
        Nodo(T x)
        {
            next = 0;
            before = 0;
            dato = x;
        }

        Nodo *getNext(){ return next;}
        Nodo *getBefore() {return before;}
        void setNext(Nodo *n) { next = n;}
        void setBefore(Nodo *n){ before = n;}
        T getDato(){ return dato;}
    private:
        Nodo *next;
        Nodo *before;
        T dato;
    };
public:
    ListaDobleCircular()
    {
        first = 0;
        last = 0;
        size = 0;
    }

    int getSize(){return size;}
    void add_last(T dato);
    T get_element_at(int index);
private:
    bool isEmpty(){return size == 0;}
    int size;
    Nodo *first;
    Nodo *last;
};

template<class T>
void ListaDobleCircular<T>::add_last(T dato)
{
    Nodo *n = new Nodo(dato);
    if(this->isEmpty())
    {
        this->first = n;
        this->last = n;
        this->first->setNext(this->first);
        this->first->setBefore(this->first);
        this->size++;
    }
    else
    {
        this->last->setNext(n);
        n->setBefore(this->last);
        this->last = n;
        n->setNext(this->first);
        this->first->setBefore(n);
        this->size++;
    }
}

template<class T>
T ListaDobleCircular<T>::get_element_at(int index)
{
    if(index >= 0 && index < size)
    {
        if(index==0){
            return this->first->getDato();
        }
        if(index==size-1){
            return this->last->getDato();
        }
        Nodo *iterador = this->first->getNext();
        int x = 1;
        while(iterador!=this->first)
        {
            if(index == x){return iterador->getDato();}
            iterador = iterador->getNext();
            x++;
        }
    }
    return 0;
}

#endif //UNTITLED_LISTADOBLECIRCULAR_H
