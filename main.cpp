#include <iostream>
#include "controller/LogicController.h"
#include "ontology/field/Field.h"
#include "ontology/Ontology.h"
#include "ontology/OntologyInstance.h"
#include "ontology/factory/OntologyFactory.h"
#include "helper/Formatter.h"
#include "helper/Logger.h"
#include "ontology/Value.h"
#include "ontology/query/Query.h"
#include "helper/Algorithm.h"

int main(int argc, char** argv) {
    LogicController::run();
}
