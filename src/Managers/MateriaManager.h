//
// Created by milena on 23/11/16.
//

#ifndef ARQSOFT_MATERIAMANAGER_H
#define ARQSOFT_MATERIAMANAGER_H


#include <vector>
#include "../DOM/Curso.h"
#include "../DB/DBWrapper.h"
#include "Manager.h"
#include "../DOM/Materia.h"

class MateriaManager : public Manager{

public:
    MateriaManager(DBWrapper *db);
    ~MateriaManager();

    Materia * getMateria(long materiaID);

    Json::Value getJsonFromString(std::string basic_string);

    Curso *getCurso(long materiaID, std::string cursoID);

    void saveMateria(Json::Value jMateria);

    void agregarInscriptoAlCurso(Materia *materia, std::string cursoID, Alumno *alumno);

    void updateMateria(Json::Value jMateria);

    std::vector<Alumno *> getInscriptosCurso(std::string materiaID, std::string cursoID);

    void updateInscriptosCurso(std::string materiaID, Curso *curso);

    Materia *getMateriaResume(long materiaID);
};

#endif //ARQSOFT_MATERIAMANAGER_H
