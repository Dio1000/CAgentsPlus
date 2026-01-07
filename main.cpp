#include <iostream>
#include "controller/LogicController.h"
#include "ontology/field/Field.h"
#include "ontology/Ontology.h"
#include "ontology/OntologyInstance.h"
#include "ontology/factory/OntologyFactory.h"
#include "ontology/factory/RuleFactory.h"
#include "helper/Formatter.h"
#include "helper/Logger.h"
#include "ontology/Value.h"
#include "ontology/query/Query.h"
#include "helper/Algorithm.h"
#include "ontology/query/decision/WeightedDecision.h"
#include "ontology/query/decision/Rule.h"
#include "ontology/query/decision/RuleDecision.h"
#include "agent/agents/MusicAgent.h"
#include "agent/agents/MusicPickerAgent.h"
#include "agent/SystemAgent.h"


void test() {
    Ontology ontology = OntologyFactory::getOntology("album");
    auto instances = OntologyFactory::getOntologyInstances(&ontology);
    auto rules = RuleFactory::getRules(&ontology);

    RuleDecision decision(instances, rules);
    SystemAgent system;

    auto musicAgent = std::make_unique<MusicAgent>(1, &decision, nullptr);
    auto musicPickerAgent = std::make_unique<MusicPickerAgent>(2, &decision, nullptr);
    system.addAgent(std::move(musicAgent));
    system.addAgent(std::move(musicPickerAgent));

    MessageBus::send(2, Message{0, INFO, "PICK"});
    system.start();
    std::this_thread::sleep_for(std::chrono::seconds(1000));
}

int main(int argc, char** argv) {
    LogicController::run();
    test();
}
