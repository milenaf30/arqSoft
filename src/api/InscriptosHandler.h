//
// Created by milena on 24/11/16.
//

#ifndef ARQSOFT_INSCRIPTOSHANDLER_H
#define ARQSOFT_INSCRIPTOSHANDLER_H


#include "handler/Handler.h"

class InscriptosHandler: public Handler {
    InscriptosHandler();
    ~InscriptosHandler();

    Response* handleGetRequest(http_message* httpMessage, string url);


    long getCursoID(string url);

    long getMateriaID(string url);
};


#endif //ARQSOFT_INSCRIPTOSHANDLER_H
