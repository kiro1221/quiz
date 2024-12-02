#include "DesignPatternModel.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

DesignPattern::DesignPattern() {
    // Constructor implementation placeholder.
    // Add any initialization code or resource allocation you need here.
    TopicName = "DesignPatterns";
    readInQuestions();
}

DesignPattern::~DesignPattern() {
    // Destructor implementation placeholder.
    // Add any cleanup or resource deallocation you need here.
}

void DesignPattern::readInQuestions() {
    std::string filename = "src/service/Data/DesignPatternData.txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(TopicName + ": Error opening file");
        return;
    }

    std::string line = "";
    while (std::getline(file, line)) {
        // Check if the line is empty to avoid stoi errors
        if (line.empty() || line == "\r") {
            continue;
        }
        line.erase(std::remove(line.begin(), line.end(),
             '\r'), line.end());

        std::stringstream ssID(line);
        int id = -1;
        ssID >> id;

        // Read topic name
        if (!std::getline(file, line) || line.empty()) {
            throw std::runtime_error(TopicName +
            ": Missing topic name for ID");
        }
        line.erase(std::remove(line.begin(), line.end(),
             '\r'), line.end());
        std::stringstream ssQuestionTopic(line);
        std::string topicName  = "";
        ssQuestionTopic >> topicName;

        // Read question type
        if (!std::getline(file, line) || line.empty()) {
            throw std::runtime_error(TopicName +
            ": Missing question type for ID");
        }
        line.erase(std::remove(line.begin(), line.end(),
             '\r'), line.end());
        std::stringstream ssQuestionType(line);
        std::string questionType = "";
        ssQuestionType >> questionType;
        // Read options (comma-separated)
        if (!std::getline(file, line) || line.empty()) {
            throw std::runtime_error(TopicName +
            ": Missing options for ID");
        }
        line.erase(std::remove(line.begin(), line.end(),
             '\r'), line.end());
        std::vector<std::string> options;
        std::stringstream ss(line);
        std::string option;
        while (std::getline(ss, option, ',')) {
            options.push_back(option);
        }

        // Read answer(s) (comma-separated for some types)
        std::vector<std::string> answer;
        if (questionType == "MC"
            || questionType == "TF"
            || questionType == "FILL"
            || questionType == "MATCH") {
            if (!std::getline(file, line) || line.empty()) {
                throw std::runtime_error(TopicName +
                ": Missing answer for ID");
            }
            line.erase(std::remove(line.begin(), line.end(),
                 '\r'), line.end());
            std::stringstream ssAnswer(line);
            std::string ans;
            while (std::getline(ssAnswer, ans, ',')) {
                answer.push_back(ans);
            }
        }

        // Read the question text, but only if it's not a MATCH type
        std::string questionText;
        if (!std::getline(file, line) || line.empty()) {
            throw std::runtime_error(TopicName +
            ": Missing question text for ID");
        }
        line.erase(std::remove(line.begin(), line.end(),
             '\r'), line.end());
        questionText = line;

        // Create a new Question object and push it to the appropriate vector
        Question q(id, topicName, questionType, options, answer, questionText);
        if (questionType == "MC") {
            MultipleChoice.push_back(q);
        } else if (questionType == "TF") {
            TrueFalse.push_back(q);
        } else if (questionType == "MATCH") {
            Matching.push_back(q);
        } else if (questionType == "FILL") {
            FillInBlank.push_back(q);
        } else {
            throw std::runtime_error(TopicName + ": Question Type Error");
        }
    }
}
