//
// Created by Monther on 20/12/2019.
//

#ifndef UNTITLED_LISTAARTISTAS_H
#define UNTITLED_LISTAARTISTAS_H


#include "../Artista.h"

class ListaArtistas
{
    class Nodo{
    public:
        Nodo(Artista* x)
        {
            next = 0;
            before = 0;
            dato = x;
        }

        Nodo *getNext(){ return next;}
        Nodo *getBefore() {return before;}
        void setNext(Nodo *n) { next = n;}
        void setBefore(Nodo *n){ before = n;}
        Artista* getDato(){ return dato;}
        void setDato(Artista *n){dato=n;}
    private:
        Nodo *next;
        Nodo *before;
        Artista* dato;
    };
public:
    ListaArtistas()
    {
        first = 0;
        last = 0;
        size = 0;
    }

    int getSize(){return size;}
    void add_first(Artista* dato);
    void add_last(Artista* dato);
    void add_at(Artista* dato, int index);
    Artista* get_element_at(int index);
    void ordenarNombre();
    void ordenarRating();
    void generarReporte();
private:
    bool isEmpty(){return size == 0;}
    int size;
    Nodo *first;
    Nodo *last;
    void my_swap(Nodo *node_1, Nodo *node_2);
};

void ListaArtistas::add_first(Artista* dato)
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


void ListaArtistas::add_last(Artista* dato)
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

void ListaArtistas::add_at(Artista* dato, int index)
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

Artista* ListaArtistas::get_element_at(int index)
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

void ListaArtistas::my_swap (Nodo *node_1, Nodo *node_2)
{
    Artista* temp = node_1->getDato();
    node_1->setDato(node_2 -> getDato());
    node_2 -> setDato(temp) ;
}

void ListaArtistas::ordenarNombre() {
    int swapped;

    Nodo *lPtr; // left pointer will always point to the start of the list
    Nodo *rPrt = 0; // right pointer will always point to the end of the list
    do
    {
        swapped = 0;
        lPtr = this->first;
        while(lPtr->getNext() != rPrt)
        {
            if (lPtr->getDato()->getNombre() > lPtr->getNext()->getDato()->getNombre())
            {
                my_swap(lPtr, lPtr->getNext());
                swapped = 1;
            }
            lPtr = lPtr->getNext();
        }

        rPrt = lPtr;

    }while(swapped);
}

void ListaArtistas::ordenarRating() {
    int swapped;

    Nodo *lPtr; // left pointer will always point to the start of the list
    Nodo *rPrt = 0; // right pointer will always point to the end of the list
    do
    {
        swapped = 0;
        lPtr = this->first;
        while(lPtr->getNext() != rPrt)
        {
            if (lPtr->getDato()->getRating() < lPtr->getNext()->getDato()->getRating())
            {
                my_swap(lPtr, lPtr->getNext());
                swapped = 1;
            }
            lPtr = lPtr->getNext();
        }

        rPrt = lPtr;

    }while(swapped);
}

void ListaArtistas::generarReporte() {
    string graph = "digraph {\n"
                   "splines=\"line\";\n"
                   "rankdir = LR;\n"
                   "node [shape=rectangle, height=0.5, width=1.5];\n"
                   "graph[nodesep = 0.35, dpi=300];\n\n";


    if(this->getSize()>0){
        graph += "node0 [label=\""+this->get_element_at(0)->getNombre()+"\"]";
        graph+=";\n";
    }

    for(int j = 1; j<this->getSize();j++){
        Artista* art = this->get_element_at(j);
        graph += "node"+to_string(j)+" [label=\""+art->getNombre()+"\"]";
        graph+=";\n";
    }

    for(int k = 0; k<this->getSize()-1;k++){
        Artista* art = this->get_element_at(k);
        graph += "node"+to_string(k)+" -> node"+to_string(k+1)+";\n";
        graph += "node"+to_string(k+1)+" -> node"+to_string(k)+";\n";
    }

    ofstream myfile;
    myfile.open("artistas.dot");
    myfile << graph+"}";
    myfile.close();
    system("dot -Tpng artistas.dot -o artistas.png");
    ShellExecute(NULL, "open", "artistas.png", NULL, NULL, SW_NORMAL);

}

#endif //UNTITLED_LISTAARTISTAS_H
