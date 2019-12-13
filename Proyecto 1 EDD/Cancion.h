//
// Created by Monther on 12/12/2019.
//

#ifndef UNTITLED_CANCION_H
#define UNTITLED_CANCION_H


#include <string>

class Cancion {
private:
    std::string nombre;
    std::string file;
    double rating;
public:
    Cancion(const std::string &nombre, const std::string &file, double rating) : nombre(nombre), file(file),
                                                                                 rating(rating) {}

    const std::string &getNombre() const {
        return nombre;
    }

    void setNombre(const std::string &nombre) {
        Cancion::nombre = nombre;
    }

    const std::string &getFile() const {
        return file;
    }

    void setFile(const std::string &file) {
        Cancion::file = file;
    }

    double getRating() const {
        return rating;
    }

    void setRating(double rating) {
        Cancion::rating = rating;
    }
};


#endif //UNTITLED_CANCION_H
