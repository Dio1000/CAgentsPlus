# CAgentsPlus

## About the Project

CAgentsPlus is a C++ library for building lightweight Multi-Agent Systems. It provides an environment for creating ontologies, defining decision-based rules, and implementing autonomous agents that can communicate and collaborate with eachother. The framework is designed to be intuitive and easy to use while offering powerful abstractions for modeling complex intelligent systems.

A practical example included in the project demonstrates how four specialised agents can work together to recommend a music playlist based on user preferences, making use of some basic user-defined rules.

## Features

### Library
- **Ontology Creation**: Define structured schemas with typed fields (TEXT, INT, BIGINT, REAL, DATE, BOOL) and constraints (NULLABLE, NOT_NULL). Store and retrieve schemas and their data instances.
- **Rule Creation**: Implement both **Weighted Rules** (for numerical scoring) and **Decision-Based Rules** (with conditional operators like EQUAL_TO, GREATER_THAN) to guide agent reasoning.
- **Agent Creation**: Build agents that run in managed threads. The framework handles inter-agent communication via a message bus, simplifying concurrent system design.

### Music Agents (Example Implementation)
The included demo system features four coordinated agents:
- **User Agent**: Interfaces with the user to gather preferences and context.
- **Analyst Agent**: Processes data in order to ensure that there are no contradictions and the data required exists.
- **Music Picker Agent**: Applies rules and weights to ontology data (songs, genres, albums) to generate recommendations.
- **Music Agent**: Simulates the final playback of the selected song queue.

## How to Use

Using this library revolves around three core concepts: Ontologies, Rules, and Agents.

### Ontologies

Ontologies act as structured data schemas, similar to tables in a relational database.

**Creating an Ontology Schema:**
Run the program with the `ontology` argument. You will be prompted for:
- **Ontology name**
- **Field Name**
- **Field Type** (TEXT, INT, BIGINT, REAL, DATE, BOOL)
- **Field Constraint** (NULLABLE, NOT_NULL)

Schemas are persisted and can be retrieved using `OntologyFactory::getOntology(ontologyName)`.

**Creating an Ontology Instance:**
Run the program with the `instance` argument. You will need to provide:
- **Ontology name**
- **Instance name**
- **Values** for each field in the schema

### Rules

Rules enable agents to evaluate ontology instances and make decisions.

- **Weighted Rules**: Assign numerical weights to specific fields (INT, BIGINT, REAL). A total score is calculated as `(field_value * weight)`. Create these statically using the `Weight` object, which takes an `std::unordered_map<std::string, double>` mapping field names to weights.
    ```cpp
    std::unordered_map<std::string, double> weightMap = {{"rating", 0.8}, {"length", 0.5}};
    WeightedDecision weightedRule(weightMap);
    ```

- **Decision-Based Rules**: Support complex conditional logic (`EQUAL_TO`, `GREATER_THAN`, etc.) on any field type. These rules are stored persistently. To create one, run the program with the `rule` argument and provide:
    - **Ontology name**
    - **Rule name**
    - **Query type** (e.g., GREATER_THAN)
    - **Field name** (must exist in the ontology)
    - **Comparison value**
    - **Operation** (ADD, SUB, MUL, DIV, MOD) applied if the condition is true
    - **Operation value** to use with the operation

### Agents

1. **Create an Agent Class:** Publicly inherit from the `Agent` interface and override the `run()` method.
2. **Agent Communication:**
    - Send messages using `MessageBus::send(receiverAgentId, Message)`.
    - The `Message` object requires the sender's ID, a type (`INFO`, `RESPONSE`, `STOP`), and a content string.
    - Retrieve messages with `MessageBus::collect(yourAgentId)`.
3. **Agent Construction:** Your agent's constructor should accept an ID and pointers to `RuleDecision` and `WeightedDecision` objects (can be `nullptr` if the agent doesn't make decisions).
4. **Orchestration with SystemAgent:** The `SystemAgent` manages the lifecycle of all agents, handling initialization, thread spawning, and graceful shutdown.

#### Full Agent Setup Example

```cpp
// Retrieve an ontology and its instances based on the name of the ontology.
Ontology* ontology = OntologyFactory::getOntology("song");
auto instances = OntologyFactory::getOntologyInstances(ontology);

// Retrieve the rules of the ontology and create a RuleDecision object which can calculate scores.
auto rules = RuleFactory::getRules(ontology);
RuleDecision ruleDecision(instances, rules);

// Create an unordered map of weights and create the Weight object,
// as well as the WeightedDecision object to calculate scores based on weights.
std::unordered_map<std::string, double> weights = {{"rating", 0.5}, {"release_date", 0.25}, {"length", -0.25}};
Weight weight{weights};
WeightedDecision weightedDecision{instances, weight};

// Initialise the SystemAgent
SystemAgent system;

// Initialise pointers to Agents
auto userAgent = std::make_unique<UserAgent>(AgentMetaData::USER_AGENT_ID, nullptr, nullptr);
auto analystAgent = std::make_unique<AnalystAgent>(AgentMetaData::ANALYST_AGENT_ID, nullptr, nullptr);
auto musicPickerAgent = std::make_unique<MusicPickerAgent>(AgentMetaData::MUSIC_PICKER_AGENT_ID, &ruleDecision, &weightedDecision);
auto musicAgent = std::make_unique<MusicAgent>(AgentMetaData::MUSIC_AGENT_ID, nullptr, nullptr);

// Add Agents to the SystemAgent for threading and communication management
system.addAgent(std::move(userAgent));
system.addAgent(std::move(analystAgent));
system.addAgent(std::move(musicAgent));
system.addAgent(std::move(musicPickerAgent));

// Start the SystemAgent
system.start();

// Example message send to the UserAgent by the SystemAgent
MessageBus::send(AgentMetaData::USER_AGENT_ID, Message(AgentMetaData::SYSTEM_AGENT_ID, INFO, "start"));

// After 1000 seconds, gracefully stop the system using the stop() method.
std::this_thread::sleep_for(std::chrono::seconds(1000));
system.stop();
```

# Prerequisites

- **C++17** or later
- **CMake** (version 3.10+ recommended)
- A C++ compiler with standard library support (GCC, Clang, or MSVC)

## Building and Usage

1. **Clone the repository:**
    ```bash
    git clone https://github.com/Dio1000/CAgentsPlus.git
    cd CAgentsPlus

2. **Build with CMake:**
  ```bash
    mkdir build && cd build
    cmake ..
    cmake --build .
```

3. **Run the example music agent system:**
   ```bash
   ./CAgentsPlus run
   ```

## Contact

Email: [sandru.darian@gmail.com](mailto:sandru.darian@gmail.com)  

CAgentsPlus: [https://github.com/Dio1000/CAgentsPlus](https://github.com/Dio1000/CAgentsPlus)  
