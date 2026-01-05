cmake_minimum_required(VERSION 3.27)
project(IntelligentSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(IntelligentSystem main.cpp
        io/InputDevice.cpp
        io/InputDevice.h
        io/OutputDevice.cpp
        io/OutputDevice.h
        io/FileManager.cpp
        io/FileManager.h
        controller/LogicController.cpp
        controller/LogicController.h
        helper/Logger.cpp
        helper/Logger.h
        ontology/field/Field.cpp
        ontology/field/Field.h
        ontology/field/Type.cpp
        ontology/field/Type.h
        ontology/field/Constraint.cpp
        ontology/field/Constraint.h
        ontology/Ontology.cpp
        ontology/Ontology.h
        helper/Formatter.cpp
        helper/Formatter.h
        meta/MetaData.cpp
        meta/MetaData.h
        ontology/OntologyInstance.cpp
        ontology/OntologyInstance.h
        ontology/Value.cpp
        ontology/Value.h
        ontology/structures/Date.cpp
        ontology/structures/Date.h
)
