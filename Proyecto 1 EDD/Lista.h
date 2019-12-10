//
// Created by Monther on 9/12/2019.
//

#ifndef UNTITLED_LISTA_H
#define UNTITLED_LISTA_H

template<class T>
class Lista {
    class Nodo{
        public:
            Nodo(T x)
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


#endif //UNTITLED_LISTA_H
