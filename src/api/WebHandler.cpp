#include "WebHandler.h"
#include "MateriasHandler.h"

WebHandler::WebHandler() {}

WebHandler::~WebHandler() {}

Response* WebHandler::handleRequest(http_message* httpMessage) {
    Response* response = new Response();
    Handler* handler;

        if (&httpMessage->uri) {
            //fixme
            string url = this->getUrl(httpMessage->uri);
            if (regex_match(url, regex("/materias/.*/cursos")) || regex_match(url, regex("/users"))) {
                handler = new MateriasHandler();
                response = handler->handleRequest(httpMessage, url);
                delete handler;
                return response;
            }
            if (regex_match(url, regex("/materias/.*/cursos/.*/inscriptos"))) {
                handler = new InscriptosHandler();
                response = handler->handleRequest(httpMessage, url);
                delete handler;
                return response;
            }
        }

}

string WebHandler::getUrl(const struct mg_str uri) {
    return this->getStringFromMgStr(uri);
}

string WebHandler::getStringFromMgStr(const struct mg_str structMgStr) {
    string asString = "";
    const char* pointer = structMgStr.p;
    for(int i = 0; i < structMgStr.len; i++) {
        asString = asString + *pointer;
        pointer++;
    }
    return asString;
}

