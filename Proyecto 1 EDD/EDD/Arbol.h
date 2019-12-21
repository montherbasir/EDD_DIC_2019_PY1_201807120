//
// Created by Monther on 19/12/2019.
//

#ifndef UNTITLED_ARBOL_H
#define UNTITLED_ARBOL_H

#include <iostream>
#include "../Playlist.h"
#include <string>
#include <utility>
#include <fstream>
#include <windows.h>
using namespace std;

class Arbol
{

    class Nodo
    {
    public:
        explicit Nodo (Playlist* playlist_) : playlist(playlist_), izq(0), der(0) {}

        Playlist *getPlaylist() const {
            return playlist;
        }

        void setPlaylist(Playlist *playlist_) {
            Nodo::playlist = playlist_;
        }

        Nodo *getIzq() const {
            return izq;
        }

        void setIzq(Nodo *izq_) {
            Nodo::izq = izq_;
        }

        Nodo *getDer() const {
            return der;
        }

        void setDer(Nodo *der_) {
            Nodo::der = der_;
        }

        string getGraph(){
            string g;
            if(izq==0&&der==0){
                g = "\""+playlist->getName()+"\" [label=\""+playlist->getName()+"\"];\n";
            }else{
                g = "\""+playlist->getName()+"\" [label=\"<C0>|"+playlist->getName()+"|<C1>\"];\n";
            }

            if(izq!=0){
                g += izq->getGraph() + "\""+playlist->getName()+"\":C0 -> \""+izq->playlist->getName()+"\";\n";
            }
            if(der!=0){
                g += der->getGraph() + "\""+playlist->getName()+"\":C1 -> \""+der->getPlaylist()->getName()+"\";\n";
            }
            return g;
        }

    private:
        Playlist *playlist;
        Nodo* izq;
        Nodo* der;
    };
private:
    Nodo* raiz;
    void add(Playlist *dato, Nodo* tmp)
    {
        if (dato->getName()<tmp->getPlaylist()->getName())
        {
            if (tmp->getIzq()!=0) add(dato, tmp->getIzq());
            else tmp->setIzq(new Nodo(dato));
        }
        else
        {
            if (tmp->getDer()!=0) add(dato, tmp->getDer());
            else tmp->setDer(new Nodo(dato));
        }
    }

    Playlist* search(string dato, Nodo* tmp){

        if(tmp==0)
            return 0;
        if (tmp->getPlaylist()->getName() == dato)
            return tmp->getPlaylist();

        if (tmp->getPlaylist()->getName() < dato)
            return search(dato, tmp->getDer());

        return search(dato, tmp->getIzq());
    }

    string inorder(Nodo* tmp)
    {
        if (tmp!=0)
        {
            inorder(tmp->getIzq());
            tmp->getPlaylist()->getName();
            inorder(tmp->getDer());
        }
    }

public:

    Arbol () : raiz(0) {}

    bool isEmpty(){
        return this->raiz==0;
    }
    void add(Playlist *playlist)
    {
        if (raiz!=0) add(playlist, raiz);
        else raiz = new Nodo(playlist);
    }

    void imprimir(){
        cout <<"Playlists:"<<endl;
        inorder(this->raiz);
    }

    void graficar(){
        string graph = "digraph {\n"
                       "splines=\"line\";\n"
                       "rankdir = TB;\n"
                       "node [shape=record, height=0.5, width=1.5];\n"
                       "graph[dpi=300];\n\n";

        graph += raiz->getGraph();

        graph += "}";

        ofstream myfile;
        myfile.open("arbol.dot");
        myfile << graph;
        myfile.close();
        system("dot -Tpng arbol.dot -o arbol.png");
        ShellExecute(NULL, "open", "arbol.png", NULL, NULL, SW_NORMAL);
    }

    Playlist* buscar(string nombre)
    {
        return search(std::move(nombre), this->raiz);
    }

};


#endif //UNTITLED_ARBOL_H
