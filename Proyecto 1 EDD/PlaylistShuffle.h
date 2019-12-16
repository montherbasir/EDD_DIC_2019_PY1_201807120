//
// Created by Monther on 15/12/2019.
//

#ifndef UNTITLED_PLAYLISTSHUFFLE_H
#define UNTITLED_PLAYLISTSHUFFLE_H

#include <string>
#include <utility>
#include <iostream>
#include "Cancion.h"
#include "EDD/ListaDoble.h"

class PlaylistShuffle{
private:
    std::string name;
    std::string type;
    ListaDoble<Cancion*>* canciones;
public:
    PlaylistShuffle(std::string name, std::string type) : name(std::move(name)), type(std::move(type))
    {
        canciones = new ListaDoble<Cancion*>();
    }

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name_) {
        PlaylistShuffle::name = name_;
    }

    const std::string &getType() const {
        return type;
    }

    void setType(const std::string &type_) {
        PlaylistShuffle::type = type_;
    }

    ListaDoble<Cancion *> *getCanciones() const {
        return canciones;
    }

    void setCanciones(ListaDoble<Cancion *> *canciones_) {
        PlaylistShuffle::canciones = canciones_;
    }

    void addCancion(Cancion* cancion_){
        if(canciones->getSize()==0){
            canciones->add_first(cancion_);
        }else{
            int x = (rand() % canciones->getSize()+1) ;
            std::cout<<x;
            canciones->add_at(cancion_, x);
        }
    }
};
#endif //UNTITLED_PLAYLISTSHUFFLE_H
