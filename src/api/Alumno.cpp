//
// Created by milena on 24/11/16.
//

#include "Alumno.h"

Alumno::Alumno(Json::Value jAlumno) {

    this->nombre = jAlumno["nombre"].asString();
    this->apellido = jAlumno["apellido"].asString();
    this->padrón = jAlumno["padrón"].asLargestInt();
}
