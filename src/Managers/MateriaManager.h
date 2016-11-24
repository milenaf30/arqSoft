//
// Created by milena on 23/11/16.
//

#ifndef ARQSOFT_MATERIAMANAGER_H
#define ARQSOFT_MATERIAMANAGER_H


#include <vector>
#include "../api/Curso.h"
#include "../DB/DBWrapper.h"
#include "Manager.h"
#include "Materia.h"

class MateriaManager : public Manager{

public:
    MateriaManager(DBWrapper *db);
    ~MateriaManager();

    Materia * getMateria(long materiaID);

    Json::Value getJsonFromString(std::string basic_string);

    Curso *getCurso(long materiaID, long cursoID);
};

#endif //ARQSOFT_MATERIAMANAGER_H
