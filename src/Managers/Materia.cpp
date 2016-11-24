//
// Created by milena on 23/11/16.
//

#include <json/json.h>
#include "Materia.h"
#include "CursoInexistenteException.h"

Materia::Materia(Json::Value jMateria) {

    const Json::Value jCursosList = jMateria["cursos"];
    for (int index = 0; index < jCursosList.size(); index++) {
        Curso* curso = new Curso(jCursosList[index]);
        this->cursos.push_back(curso);
    }
    this->id = jMateria["materiaID"].asLargestInt();
    this->nombre = jMateria["nombre"].asString();
    this->jMateria = jMateria;

}

Materia::~Materia() {

}

Curso *Materia::getCurso(long cursoID) {
    for (int index = 0; index < this->cursos.size(); index++) {
        if (this->cursos[index]->id == cursoID) {
            return this->cursos[index];
        }
    }

    throw CursoInexistenteException();
}
