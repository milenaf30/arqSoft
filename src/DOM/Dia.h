//
// Created by milena on 23/11/16.
//

#ifndef ARQSOFT_DIA_H
#define ARQSOFT_DIA_H

#include <string>
#include <json/json.h>

class Dia {
public:
    std::string aula;
    std::string sede;
    std::string modalidad;
    std::string dia;
    std::string desde;
    std::string hasta;

    Dia(Json::Value jDia);
    ~Dia();

};


#endif //ARQSOFT_DIA_H
