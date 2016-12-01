//
// Created by milena on 23/11/16.
//

#include <json/json.h>
#include <iostream>
#include "Materia.h"
#include "../Exceptions/CursoInexistenteException.h"

Materia::Materia(Json::Value jMateria) {

    const Json::Value jCursosList = jMateria["cursos"];
    for (int index = 0; index < jCursosList.size(); index++) {
        Curso* curso = new Curso(jCursosList[index]);
        this->cursos.push_back(curso);
    }
    this->id = jMateria["id"].asString();
    this->nombre = jMateria["nombre"].asString();
    this->jMateria = jMateria;

}

Materia::~Materia() {

    for(int index = 0; index < this->cursos.size(); index++) {
        delete (this->cursos[index]);
    }

}

Curso *Materia::getCurso(std::string cursoID) {
    for (int index = 0; index < this->cursos.size(); index++) {
        if (this->cursos[index]->id == cursoID) {
            return this->cursos[index];
        }
    }

    throw CursoInexistenteException();
}

void Materia::agregarInscripto(std::string cursoID, Alumno *alumno) {
    this->getCurso(cursoID)->agregarAlumno(alumno);
    this->resetJson();
}

void Materia::resetJson() {
    Json::Value newJson;
    newJson["id"] = this->id;
    newJson["nombre"] = this->nombre;
    for (int i = 0; i < this->cursos.size(); i++) {
        newJson["cursos"].append(this->cursos[i]->jCurso);
        //std::cout << this->cursos[i]->jCurso.toStyledString()<< std::endl;
    }

    //std::cout << newJson << std::endl;
    this->jMateria = newJson;
}
