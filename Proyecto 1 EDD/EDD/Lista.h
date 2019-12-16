//
// Created by Monther on 9/12/2019.
//

#ifndef UNTITLED_LISTA_H
#define UNTITLED_LISTA_H

template<class T>
class Lista {
    class Nodo{
        public:
            explicit Nodo(T x)
            {
                next = 0;
                dato = x;
            }

            Nodo *getNext(){ return next;}
            void setNext(Nodo *n) { next = n;}
            T getDato(){ return dato;}
        private:
            Nodo *next;
            T dato;
    };
    public:
        Lista()
        {
            first = 0;
            last = 0;
            size = 0;
        }

        int getSize(){return size;}
        void add_first(T dato);
        void add_last(T dato);
        //void add_at(T dato, int index);
        T get_element_at(int index);
        void remove_at(int index);
    private:
        bool isEmpty(){return size == 0;}
        int size;
        Nodo *first;
        Nodo *last;
};


template<class T>
void Lista<T>::add_first(T dato)
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
        this->first = n;
        this->size++;
    }
}

template<class T>
void Lista<T>::add_last(T dato)
{
    if(this->isEmpty())
    {
        this->add_first(dato);
    }
    else
    {
        Nodo *n = new Nodo(dato);
        this->last->setNext(n);
        this->last = n;
        this->size++;
    }
}

template<class T>
T Lista<T>::get_element_at(int index)
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

template<class T>
void Lista<T>::remove_at(int index)
{
    if(index >= 0 && index < this->size)
    {

        if(index == 0)
        {
            if(this->size==1){
                delete this->first;
            }else{
                Nodo *aux = this->first->getNext();
                delete this->first;
                this->first=aux;
            }
        }
        else
        {
            Nodo *aux = this->first;
            int i = 0;
            while(aux!=0)
            {
                if(i == index-1){break;}
                aux = aux->getNext();
                i++;
            }
            if(aux->getNext()==last){
                delete aux->getNext();
                aux->setNext(0);
                last=aux;
            }else{
                aux->setNext(aux->getNext()->getNext());
                delete aux->getNext();
            }
        }
        this->size--;
    }
}
#endif //UNTITLED_LISTA_H
