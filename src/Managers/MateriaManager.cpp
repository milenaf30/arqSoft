//
// Created by milena on 23/11/16.
//

#include <json/json.h>
#include "MateriaManager.h"
#include "../api/MateriaInexistenteException.h"
#include "Materia.h"

#define MATERIAID "materiaID_"

MateriaManager::MateriaManager(DBWrapper *db) {
    this->db = db;
}

MateriaManager::~MateriaManager() {

}

Materia * MateriaManager::getMateria(long materiaID) {

    Json::Value jMateria;
    std::string informacion_materia;
    try {
        this->db->getKey(MATERIAID + std::to_string(materiaID), &informacion_materia);

    } catch (std::exception& e){
        throw MateriaInexistenteException();
    }

    jMateria = this->getJsonFromString(informacion_materia);
    Materia* materia = new Materia(jMateria);

    return materia;
}

Json::Value MateriaManager::getJsonFromString(std::string basic_string) {
    Json::Reader reader;
    Json::Value jvalue;
    reader.parse(basic_string.c_str(), jvalue);
    return  jvalue;
}

Curso *MateriaManager::getCurso(long materiaID, long cursoID) {
    Materia* materia = this->getMateria(materiaID);
    return materia->getCurso(cursoID);


}


