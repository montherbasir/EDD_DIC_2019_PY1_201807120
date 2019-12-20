//
// Created by Monther on 17/12/2019.
//

#ifndef UNTITLED_PLAYLISTCIRCULAR_H
#define UNTITLED_PLAYLISTCIRCULAR_H

#include <string>
#include <utility>
#include "Cancion.h"
#include "EDD/ListaDobleCircular.h"
#include "Playlist.h"

class PlaylistCircular: public Playlist{
private:
    ListaDobleCircular<Cancion*> *canciones;

public:
    PlaylistCircular(std::string name, std::string type) : Playlist(std::move(name),std::move(type)){
        canciones = new ListaDobleCircular<Cancion*>();
    }

    ListaDobleCircular<Cancion *> *getCanciones() const {
        return canciones;
    }

    void setCanciones(ListaDobleCircular<Cancion *> *canciones_) {
        PlaylistCircular::canciones = canciones_;
    }

    void addCancion(Cancion* cancion_) {
        canciones->add_last(cancion_);
    }

    void reproducir() override{
//        while(canciones->getSize()!=0){
        generarGraph(canciones);

        Sleep(2000);
//        }

    }

    void generarGraph(ListaDobleCircular<Cancion*>* lista){
        cout << "Hola " <<endl;
        string graph = "digraph {\n"
                       "splines=\"line\";\n"
                       "rankdir = LR;\n"
                       "node [shape=rectangle, height=0.5, width=1.5];\n"
                       "graph[nodesep = 0.35, dpi=300];\n\n";


        if(lista->getSize()>0){
            graph += "node0 [label=\""+lista->get_element_at(0)->getNombre()+"\", fillcolor=greenyellow, style=filled];\n";
            cout << lista->get_element_at(0)->getNombre()<<endl;
        }

        for(int j = 1; j<lista->getSize();j++){
            Cancion* cancion = lista->get_element_at(j);
            graph += "node"+to_string(j)+" [label=\""+cancion->getNombre()+"\"];\n";
            cout << cancion->getNombre()<<endl;
        }

        for(int k = 0; k<lista->getSize()-1;k++){
            cout<<lista->getSize();
            Cancion* cancion = lista->get_element_at(k);
            graph += "node"+to_string(k)+" -> node"+to_string(k+1)+"\n";
            cout << cancion->getNombre()<<endl;
        }

        ofstream myfile;
        myfile.open("stack.dot");
        myfile << graph+"}";
        myfile.close();
        system("dot -Tpng stack.dot -o stack.png");
        ShellExecute(NULL, "open", "stack.png", NULL, NULL, SW_NORMAL);
    }

};
#endif //UNTITLED_PLAYLISTCIRCULAR_H
