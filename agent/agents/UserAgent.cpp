//
// Created by Darian Sandru on 09.01.2026.
//

#include "UserAgent.h"

namespace {
    constexpr const char* NO_DATA = "NA";
    auto withDefault = [](const std::string& s) {
        return s.empty() ? std::string(NO_DATA) : s;
    };

    std::string normalize(std::string s) {
        Algorithm::toLower(s);
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());

        std::string out;
        bool prevSpace = false;
        for (char c : s) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                if (!prevSpace) out += ' ';
                prevSpace = true;
            }
            else {
                out += c;
                prevSpace = false;
            }
        }

        return out;
    }

    std::vector<std::string> normalizeList(const std::vector<std::string>& input) {
        std::vector<std::string> out;
        out.reserve(input.size());
        for (auto s : input)
            out.push_back(normalize(std::move(s)));
        return out;
    }

    bool isNegative(const std::string& s) {
        return s.empty() || s == "n" || s == "no";
    }

    bool isPositive(const std::string& s) {
        return s == "y" || s == "yes";
    }

    bool askYesNo(const std::string& question) {
        while (true) {
            OutputDevice::writeNewLine(question);
            std::string input = normalize(InputDevice::readLineFromKeyboard());

            if (isPositive(input)) return true;
            if (isNegative(input)) return false;

            OutputDevice::writeNewLine("Please answer with Y/Yes or N/No.");
        }
    }

    std::string askOptional(const std::string& question) {
        OutputDevice::writeNewLine(question);
        std::string input = normalize(InputDevice::readLineFromKeyboard());

        return isNegative(input) ? "" : input;
    }
}

void UserAgent::getInfo(const std::string& songString) {
    OutputDevice::writeNewLine(
            "If you do not care about a question, answer 'No' or leave it empty."
    );

    std::string albumString = askOptional("Any album you want to listen to?");
    std::string artistString = askOptional("Any artist you want to listen to?");
    std::string genreString = askOptional("Any genre you want to listen to?");
    bool careRating = askYesNo("Do you care about the rating of the song? (Y/N)");
    bool shorterLength = askYesNo("Do you want a shorter song? (Y/N)");
    bool newerSong = askYesNo("Do you want a newer song? (Y/N)");
    std::string languageString = askOptional("Do you prefer a certain language?");

    std::string messageString =
            withDefault(albumString) + ":" +
            withDefault(artistString) + ":" +
            withDefault(genreString) + ":" +
            (!careRating ? "1" : "0") + ":" +
            (!shorterLength ? "1" : "0") + ":" +
            (!newerSong ? "1" : "0") + ":" +
            withDefault(languageString);

    OutputDevice::writeNewLine("Thank you! I will send the data to the Analyst Agent.");
    sendInfo(songString, messageString);
}

void UserAgent::sendInfo(const std::string& songString, const std::string& messageString) {
    std::vector<std::string> normalizedList = Algorithm::split(songString, ',');
    normalizedList = normalizeList(normalizedList);
    std::string listString;
    for (const std::string& elem : normalizedList) {
        listString += elem + ",";
    }

    std::string message = listString.substr(0, listString.size() - 1) + ":" + ((messageString.empty()) ? "end" : messageString);
    Message msg = Message(AgentMetaData::USER_AGENT_ID, INFO, message);
    MessageBus::send(AgentMetaData::ANALYST_AGENT_ID, msg);
 }

void UserAgent::start() {
    OutputDevice::writeNewLine("User Agent, with ID: " + std::to_string(AgentMetaData::USER_AGENT_ID) + ", speaking:");
    OutputDevice::writeNewLine("Welcome! Please provide some information about what you would like to listen to.");
    OutputDevice::writeNewLine("Any song(s) you are in the mood for? (comma-separated, or 'No')");
    std::string songResponse = normalize(InputDevice::readLineFromKeyboard());

    if (isNegative(songResponse)) {
        OutputDevice::writeNewLine("Alright! Then provide some general preferences.");
        getInfo("");
        return;
    }
    bool chooseBest = askYesNo("Should we choose the best ones for you? (Y/N)");
    if (chooseBest) getInfo(songResponse);
    else sendInfo(songResponse, "");
}

void UserAgent::run() {
    while (running) {
        auto messages = MessageBus::collect(agentID);
        while (!messages.empty()) {
            auto message = messages.front();
            messages.pop();

            if (message.type == INFO && message.message == "start") start();
            else if (message.type == RESPONSE) {
                OutputDevice::writeNewLine("User Agent, with ID: " + std::to_string(AgentMetaData::USER_AGENT_ID) + ", speaking:");
                OutputDevice::writeNewLine("Analysis failed. Analysis Agent, with ID: "
                    + std::to_string(AgentMetaData::ANALYST_AGENT_ID) + ", says:\n" + message.message);
                start();
            }
        }
    }
}