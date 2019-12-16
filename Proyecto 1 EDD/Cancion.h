//
// Created by Monther on 12/12/2019.
//

#ifndef UNTITLED_CANCION_H
#define UNTITLED_CANCION_H


#include <string>
#include <utility>

class Cancion {
private:
    std::string nombre;
    std::string file;
    double rating;
public:
    Cancion(std::string nombre, std::string file, double rating) : nombre(std::move(nombre)), file(std::move(file)),
                                                                                 rating(rating) {}

    const std::string &getNombre() const {
        return nombre;
    }

    void setNombre(const std::string &nombre_) {
        Cancion::nombre = nombre_;
    }

    const std::string &getFile() const {
        return file;
    }

    void setFile(const std::string &file_) {
        Cancion::file = file_;
    }

    double getRating() const {
        return rating;
    }

    void setRating(double rating_) {
        Cancion::rating = rating_;
    }
};


#endif //UNTITLED_CANCION_H
