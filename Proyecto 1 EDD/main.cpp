#include <iostream>
#include <json/json.h>
#include <memory>
#include <fstream>
#include "EDD/ListaDoble.h"
#include "EDD/Cola.h"
#include "EDD/Matriz.h"
#include "Album.h"
#include "Artista.h"

using namespace std;


Json::Value parseJson(string file)
{
    ifstream infile { file };
    string rawJson { istreambuf_iterator<char>(infile), istreambuf_iterator<char>() };

    const auto rawJsonLength = static_cast<int>(rawJson.length());
    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err))
    { cout << "error parsing revise la ruta" << endl;
        return 0;
    }

    return root;

}


int main() {
    auto* m = new Matriz<Album>("Monther");
//    m->insertarColumna(10);
//    m->insertarColumna(11);
//    m->insertarColumna(13);
//    m->insertarColumna(1);
//    m->insertarColumna(100);
//    m->insertarColumna(0);
//    m->insertarColumna(100);
//    m->insertarColumna(10);
//
//    m->insertarFila("Enero");
//    m->insertarFila("Marzo");
//    m->insertarFila("diciembre");
//    m->insertarFila("julio");
//    m->insertarFila("Marzo");

//    m->insertar(new Album("M1","mayo",2019, nullptr));
//    m->insertar(new Album("M2","agosto",2019, nullptr));
//    m->insertar(new Album("M3","mayo",2018, nullptr));
//    m->insertar(new Album("M4","marzo",2020, nullptr));
//    m->insertar(new Album("M5","marzo",2020, nullptr));
//
//    m->imprimirCol();
//    m->imprimirFilas();

    cout << "Bienvenido a Music++" << endl;
    cout << "Ingrese la ruta del archivo json: " << endl;
    string s;
    getline(cin, s);
    Json::Value root = parseJson(s);
    auto* artistas = new ListaDoble<Artista*>();
    for ( int i = 0; i < root["Library"].size(); i++ )
    {
        Json::Value artist = root["Library"][i]["Artist"];
        string name = artist["Name"].asString();
        cout << "Artista: " << name << endl;
        auto *art = new Artista(name, nullptr);
        auto* albumes = new Matriz<Album>(name);
        for(int j=0;j<artist["Albums"].size();j++)
        {
            Json::Value album = artist["Albums"][j];
            string name1 = album["Name"].asString();
            cout << "   " << name1 << endl;
            string month = album["Month"].asString();
            cout << "   " << month << endl;
            string year = album["Year"].asString();
            cout << "   " << year << endl;
            auto* al = new Album(name1,month,stoi(year), nullptr);
            auto* canciones = new Lista<Cancion*>();
            for(int k=0;k<album["Songs"].size();k++){
                Json::Value song = album["Songs"][k];
                string name2 = song["Name"].asString();
                cout << "       " << name2 << endl;
                string file = song["File"].asString();
                cout << "       " << file << endl;
                string rating = song["Rating"].asString();
                cout << "       " << rating << endl;
                auto* cancion = new Cancion(name2,file,stod(rating));
                canciones->add_last(cancion);
            }
            al->setCanciones(canciones);
            albumes->insertar(al);
        }
        art->setAlbumes(albumes);
        artistas->add_last(art);
    }

    return 0;
}
