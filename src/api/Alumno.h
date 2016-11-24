//
// Created by milena on 24/11/16.
//

#ifndef ARQSOFT_ALUMNO_H
#define ARQSOFT_ALUMNO_H

#include <string>
#include <json/json.h>

class Alumno {
public:
    Alumno(Json::Value jAlumno);

    std::string nombre;
    std::string apellido;
    long padrón;

};


#endif //ARQSOFT_ALUMNO_H
