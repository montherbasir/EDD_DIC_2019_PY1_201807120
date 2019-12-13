#include <iostream>
#include <json/json.h>
#include <memory>
#include <fstream>
#include "Cola.h"
#include "Matriz.h"
#include "Album.h"

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
    auto* m = new Matriz<Album>("artista");
    m->insertarColumna(10);
    m->insertarColumna(11);
    m->insertarColumna(13);
    m->insertarColumna(1);
    m->insertarColumna(100);
    m->insertarColumna(0);
    m->insertarColumna(100);
    m->insertarColumna(10);
    m->imprimirCol();

    m->insertarFila("Enero");
    m->insertarFila("Marzo");
    m->insertarFila("Diciembre");
    m->insertarFila("Julio");
    m->insertarFila("Marzo");
    m->imprimirFilas();

//    cout << "Ingrese la ruta" << endl;
//    string s;
//    getline(cin, s);
//    Json::Value root = parseJson(s);
//
//    for ( int i = 0; i < root["Library"].size(); i++ )
//    {
//        const string name = root["Library"][i]["Artist"]["Name"].asString(); cout << name << endl;
//    }

    return 0;
}
