//
// Created by milena on 24/11/16.
//

#include "InscriptosHandler.h"
#include "../Managers/MateriaManager.h"
#include "InvalidRequestException.h"

InscriptosHandler::InscriptosHandler() {

}

InscriptosHandler::~InscriptosHandler() {

}

Response *InscriptosHandler::handleGetRequest(http_message *httpMessage, string url) {
    Response* response = new Response();
    MateriaManager* materiaManager = new MateriaManager(this->db);

    try {
        long materiaID = this->getMateriaID(url);
        string cursoID = this->getCursoID(url);
        Curso* curso = materiaManager->getCurso(materiaID, cursoID);
        //Json::Value body;
        //Json::Value jcurso = curso->jCurso;
       // body["inscriptos"] = jcurso["inscriptos"];
        response->setSuccessfulHeader();
        response->setBody(curso->jCurso.toStyledString());
    } catch (InvalidRequestException& e) {
        response->setBadRequestHeader();
        response->setErrorBody(e.getMessage());
    }


    delete materiaManager;
    return response;
}

long InscriptosHandler::getMateriaID(string url) {
    vector<string> parsedUrl = split(url, '/');
    if (parsedUrl.size() < 2) {
        throw InvalidRequestException("Cannot get user id from url.");
    }
    string materiaIDAsString = parsedUrl[2];
    try {
        long materiaID = stol(materiaIDAsString);
        return materiaID;
    } catch (invalid_argument e) {
        throw InvalidRequestException("Not a numeric id");
    }
}

string InscriptosHandler::getCursoID(string url) {
    vector<string> parsedUrl = split(url, '/');
    if (parsedUrl.size() < 4) {
        throw InvalidRequestException("Cannot get user id from url.");
    }
    string cursoIDAsString = parsedUrl[4];
    return cursoIDAsString;
}

Response *InscriptosHandler::handlePostRequest(http_message *httpMessage) {
    return nullptr;
}

Response *InscriptosHandler::handleDeleteRequest(http_message *httpMessage, string url) {
    return nullptr;
}

Response *InscriptosHandler::handlePutRequest(http_message *httpMessage, string url) {
    return nullptr;
}
