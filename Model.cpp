/* 
 * File:   Model.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:33
 */

#include "Model.h"

Model::Model() {
    matrix = new Matrix();
    border = new Border();

    bases = new QVector<Base*>();
    vecObjects = new QVector<BitmapObj*>();

    roundObjects = new QHash<quint32,RoundObj*>();

    //TODO fill the containers ???
}

Model::~Model() {
    delete matrix;
    delete border;

    //Delete bases
    for (int i = 0; i < bases->size(); i++) {
        delete (*bases)[i];
    }
    delete bases;

    //Delete vecObjects
    for (int i = 0; i < vecObjects->size(); i++) {
        delete (*vecObjects)[i];
    }
    delete vecObjects;

    //Delete roundObjects
    for (int i = 0; i < roundObjects->size(); i++) {
        delete (*roundObjects)[i];
    }
    delete roundObjects;
}

void Model::reset() {
    //TODO call destructor and constructor
}

