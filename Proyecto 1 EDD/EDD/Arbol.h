//
// Created by Monther on 19/12/2019.
//

#ifndef UNTITLED_ARBOL_H
#define UNTITLED_ARBOL_H


template<class T>
class Arbol
{
    class Nodo{
    public:
        Nodo(T x)
        {
            izq = 0;
            der = 0;
            dato = x;
        }

        Nodo *getIzq(){ return izq;}
        Nodo *getDer() {return der;}
        void setIzq(Nodo *n) { izq = n;}
        void setDer(Nodo *n){ der = n;}
        T getDato(){ return dato;}
    private:
        Nodo *izq;
        Nodo *der;
        T dato;
    };
public:
    Arbol()
    {
        raiz = 0;
        size = 0;
    }
    Nodo insertar(T x);
private:
    bool isEmpty(){return size == 0;}
    int size;
    Nodo *raiz;
};

template<class T>
void ListaDoble<T>::add_first(T dato)
{
    Nodo *n = new Nodo(dato);
    if(this->isEmpty())
    {
        this->first = n;
        this->last = n;
        this->size++;
    }
    else
    {
        n->setNext(this->first);
        this->first->setBefore(n);
        this->first = n;
        this->size++;
    }
}

template<class T>
void ListaDoble<T>::add_last(T dato)
{
    if(this->isEmpty())
    {
        this->add_first(dato);
    }
    else
    {
        Nodo *n = new Nodo(dato);
        this->last->setNext(n);
        n->setBefore(this->last);
        this->last = n;
        this->size++;
    }
}

template<class T>
void ListaDoble<T>::add_at(T dato, int index)
{
    if(index >= 0 && index <= this->size)
    {
        if(index == 0){ this->add_first(dato); return;}
        if(index == this->size) {this->add_last(dato); return;}
        Nodo *aux = this->first;
        int x = 0;
        while(aux!=0)
        {
            if(x == index){break;}
            aux = aux->getNext();
            x++;
        }
        Nodo *n = new Nodo(dato);
        aux->getBefore()->setNext(n);
        n->setBefore(aux->getBefore());
        n->setNext(aux);
        aux->setBefore(n);
        this->size++;
    }
}

template<class T>
T ListaDoble<T>::get_element_at(int index)
{
    if(index >= 0 && index < size)
    {
        Nodo *iterador = this->first;
        int x = 0;
        while(iterador!=0)
        {
            if(index == x){return iterador->getDato();}
            iterador = iterador->getNext();
            x++;
        }
    }
    return 0;
}

#endif //UNTITLED_ARBOL_H
