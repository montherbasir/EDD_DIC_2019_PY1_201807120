//
// Created by Monther on 15/12/2019.
//

#ifndef UNTITLED_PLAYLISTQUEUE_H
#define UNTITLED_PLAYLISTQUEUE_H

#include <string>
#include <utility>
#include "Cancion.h"
#include "EDD/Cola.h"
#include "Playlist.h"

class PlaylistQueue: public Playlist{
private:
    std::string name;
    std::string type;
    Cola<Cancion*> *canciones;

public:
    PlaylistQueue(std::string name, std::string type) : Playlist(std::move(name),std::move(type))
    {
        canciones = new Cola<Cancion*>();
    }

    Cola<Cancion*> *getCanciones() const{
        return canciones;
    }

    void setCanciones(Cola<Cancion*>* canciones_) {
        PlaylistQueue::canciones = canciones_;
    }

    void addCancion(Cancion* cancion_) override{
        canciones->queue(cancion_);
    }

    void reproducir() override{
        auto* lista = new Lista<Cancion*>();

        int x = canciones->getSize();
        for(int i = 0; i<x;i++){
            Cancion* cancion = canciones->dequeue();
            lista->add_last(cancion);
        }

        while(lista->getSize()!=0){
            generarGraph(lista);
            lista->remove_at(0);
            Sleep(6000);
        }

    }

    void generarGraph(Lista<Cancion*>* lista){
        string graph = "digraph {\n"
                       "splines=\"line\";\n"
                       "rankdir = LR;\n"
                       "node [shape=rectangle, height=0.5, width=1.5];\n"
                       "graph[nodesep = 0.35, dpi=300];\n\n";


        if(lista->getSize()>0){
            graph += "node0 [label=\""+lista->get_element_at(0)->getNombre()+"\", fillcolor=greenyellow, style=filled];\n";
        }

        for(int j = 1; j<lista->getSize();j++){
            Cancion* cancion = lista->get_element_at(j);
            graph += "node"+to_string(j)+" [label=\""+cancion->getNombre()+"\"];\n";
        }

        for(int k = 0; k<lista->getSize()-1;k++){
            Cancion* cancion = lista->get_element_at(k);
            graph += "node"+to_string(k)+" -> node"+to_string(k+1)+";\n";
        }

        ofstream myfile;
        myfile.open("stack.dot");
        myfile << graph+"}";
        myfile.close();
        system("dot -Tpng stack.dot -o stack.png");
        ShellExecute(NULL, "open", "stack.png", NULL, NULL, SW_NORMAL);
    }

};
#endif //UNTITLED_PLAYLISTQUEUE_H
