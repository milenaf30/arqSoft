//
// Created by milena on 24/11/16.
//

#include "DbBuilder.h"
#include "../Managers/MateriaManager.h"
#include "../Exceptions/MateriaYaExisteException.h"
#include <iostream>
#include <fstream>

DbBuilder::DbBuilder() {
    this->namedb = new std::string("/tmp/appDB");
    this->db = DBWrapper::openDb(namedb);
}

DbBuilder::~DbBuilder() {
    DBWrapper::ResetInstance();
    delete namedb;
}

std::vector<std::string> DbBuilder::cargar_materias() {
    //Read File
    std::ifstream file ("/home/milena/Escritorio/git/arqSoft/src/file1.csv");
    std::string value;
    std::vector<std::string> materias_disponibles;
    bool init = false;
    int contador = 1;
    Json::Value jMateria;
    MateriaManager* materiaManager = new MateriaManager(this->db);
    while (getline(file, value, '"')) {

        if (value.compare("\n") != 0 && value.compare("") != 0) {
            if(value.compare(";") != 0) {
                init = true;
                if (contador == 3) {
                    jMateria["nombre"] = value;

                } else if (contador == 4) {
                    jMateria["id"] = value;
                    materias_disponibles.push_back(value);
                }else if (contador == 5) {
                    jMateria["cursos"] = this->procesar_cursos((std::string) value, nullptr);
                }
                contador++;
               // std::cout << jMateria << std::endl;
            }

        } else if (init) {
            contador = 1;
            try {
                if (jMateria!= "") materiaManager->saveMateria(jMateria);}
            catch (MateriaYaExisteException& e){}
            init = false;

        }

    }
    try{if (init) materiaManager->saveMateria(jMateria);} catch(std::exception& e) {};
    delete(materiaManager);
    return materias_disponibles;
}



void DbBuilder::set_upDB() {
    std::vector<std::string> materias_disponibles = this->cargar_materias();
    this->cargar_alumnos(materias_disponibles);

}

void DbBuilder::split2(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}
std::vector<std::string> DbBuilder::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split2(s, delim, elems);
    return elems;
}

Json::Value DbBuilder::procesar_cursos(std::string value, Materia *materia) {
    std::vector<std::string> informacion_de_cursos = split(value, '\n');
    int contador = 1;
    bool init = false;
    Json::Value jcursos;
    Json::Value jcurso;
    for (long index = 0; index < informacion_de_cursos.size(); index++) {

        std::vector<std::string> campo_valor;
        campo_valor = split(informacion_de_cursos[index],':');

        if (informacion_de_cursos[index].compare("") != 0){

            if (contador == 2){
                jcurso["profesores"] = campo_valor[1];
                init = true;
            }
            if (contador == 4)
                jcurso["cursoID"] = campo_valor[1];
            if (contador >= 5 && campo_valor[0].compare("Materia") != 0) {
                //Se hace el compare explicito porque habian saltos en el medio de los cursos
                jcurso["dias"].append(informacion_de_cursos[index]);
            }
            contador++;
        }
        if (informacion_de_cursos[index].compare("") != 0 && campo_valor[0].compare("Materia") == 0 && init){
            contador = 2;
            jcurso["inscriptos"];
            jcursos.append(jcurso);
            jcurso["dias"] = Json::Value::null;

        }
    }

    //queda un curso afuera por el parseo
    jcurso["inscriptos"];
    jcursos.append(jcurso);

    return jcursos;
}

void DbBuilder::cargar_alumnos(std::vector<std::string> materias_disponibles) {

    MateriaManager* materiaManager = new MateriaManager(this->db);
    for (int i = 0; i < 1000; i++) {
        Json::Value alumno;
        alumno["nombre"] = "Nombre" + std::to_string(i+1);
        alumno["apellido"] = "Apellido" + std::to_string(i+1);
        alumno["padron"] = this->crear_padron();
        Alumno* alumno1 = new Alumno(alumno);
        int materia_index = std::rand() % (int)materias_disponibles.size();
        std::string id = materias_disponibles[materia_index];
        Materia* materia = materiaManager->getMateria(std::stol(id));
        std::vector<Curso*> cursos_disponibles = materia->cursos;
        int curso_index = std::rand() % (int)cursos_disponibles.size();
        materiaManager->agregarInscriptoAlCurso(materia, cursos_disponibles[curso_index]->id, alumno1);
        std::cout << "materiaID " + id <<std::endl;
        std::cout << "cursoID" + cursos_disponibles[curso_index]->id << std::endl;
    }

}

std::string DbBuilder::crear_padron() {
    char padron[5];
    static const char num[] = "0123456789";
    for (int i = 0; i < 5; i++) {
        padron[i] = num[rand() % (sizeof(num) - 1)];
    }
    padron[5] = '\0';
    return std::string(padron);
}




