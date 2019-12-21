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
        string i;
        int ind=0;
        while(ind<canciones->getSize()&&ind>-1){
            generarGraph(canciones,ind);
            cout << "0: Salir" <<endl;
            cout << "1: Atras" <<endl;
            cout << "2: Adelante" <<endl;
            getline(cin,i);
            if(i=="1"){
                ind--;
                if(ind==-1){
                    ind=canciones->getSize()-1;
                }
            }else if(i=="2") {
                ind++;
                if(ind==canciones->getSize()){
                    ind=0;
                }
            }else if(i=="0"){
                break;
            }else{

            }
            Sleep(500);
        }

    }

    void generarGraph(ListaDobleCircular<Cancion*>* lista, int in){

        string graph = "digraph {\n"
                       //"splines=\"line\";\n"
                       "rankdir = LR;\n"
                       "node [shape=rectangle, height=0.5, width=1.5];\n"
                       "graph[nodesep = 0.35, dpi=300];\n\n";


        if(lista->getSize()>0){
            graph += "node0 [label=\""+lista->get_element_at(0)->getNombre()+"\"]";
            if(in==0){
                graph+="[fillcolor=greenyellow, style=filled];\n";
            }else{
                graph+=";\n";
            }
        }

        for(int j = 1; j<lista->getSize();j++){
            Cancion* cancion = lista->get_element_at(j);
            graph += "node"+to_string(j)+" [label=\""+cancion->getNombre()+"\"]";
            if(in==j){
                graph+="[fillcolor=greenyellow, style=filled];\n";
            }else{
                graph+=";\n";
            }
        }

        for(int k = 0; k<lista->getSize()-1;k++){
            Cancion* cancion = lista->get_element_at(k);
            graph += "node"+to_string(k)+" -> node"+to_string(k+1)+";\n";
            graph += "node"+to_string(k+1)+" -> node"+to_string(k)+";\n";
        }

        graph += "node0 -> node"+to_string(lista->getSize()-1)+";\n";
        graph += "node"+to_string(lista->getSize()-1)+" -> node0;\n";

        ofstream myfile;
        myfile.open("stack.dot");
        myfile << graph+"}";
        myfile.close();
        system("dot -Tpng stack.dot -o stack.png");
        ShellExecute(NULL, "open", "stack.png", NULL, NULL, SW_NORMAL);
    }

};
#endif //UNTITLED_PLAYLISTCIRCULAR_H
