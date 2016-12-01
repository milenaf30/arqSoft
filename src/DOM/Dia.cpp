//
// Created by milena on 23/11/16.
//

#include "Dia.h"

Dia::Dia(Json::Value jDia) {
    this->aula = jDia["aula"].asString();
    this->modalidad = jDia["modalidad"].asString();
    this->sede = jDia["sede"].asString();
    this->desde = jDia["desde"].asString();
    this->hasta = jDia["hasta"].asString();
    this->dia = jDia["dia"].asString();
}

Dia::~Dia() {

}
