//#include "../Question/QuestionModel.hpp"
#include "TestingModel.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

TestingModel::TestingModel() {
    TopicName = "Testing";
    readInQuestions();
}

TestingModel::~TestingModel() {}

void TestingModel::readInQuestions() {
    std::string filename = "src/service/Data/TestingData.txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(TopicName + ": Error opening file");
        return;
    }

    std::string typeAndText = "", optionsText = "", ansText = "";
    while (std::getline(file, typeAndText)) {
        if (typeAndText == "" || typeAndText == "\r") {
            continue;
        }
        std::string topicName = "Testing", questionType = "", questionText = "";
        std::vector<std::string> options = {}, answer = {};

        std::stringstream readableLine(typeAndText);
        readableLine >> questionType >> questionText;
        if (questionType == "") {
            throw std::runtime_error(TopicName +
            ": Error getting question type");
        }
        if (questionText == "") {
            throw std::runtime_error(TopicName +
            ": Error getting question text");
        }
        std::replace(questionText.begin(), questionText.end(), '-', ' ');

        std::getline(file, optionsText);
        if (optionsText == "") {
            throw std::runtime_error(TopicName + ": Error getting options");
        }
        readableLine = std::stringstream(optionsText);
        std::string curOption = "";
        while (readableLine >> curOption) {
            if (curOption == "None") {
                break;
            }
            std::replace(curOption.begin(), curOption.end(), '-', ' ');
            options.push_back(curOption);
        }

        std::getline(file, ansText);
        if (ansText == "") {
            throw std::runtime_error(TopicName + ": Error getting answers");
        }
        readableLine = std::stringstream(ansText);
        std::string curAnswer = "";
        while (readableLine >> curAnswer) {
            std::replace(curAnswer.begin(), curAnswer.end(), '-', ' ');
            answer.push_back(curAnswer);
        }

        int id = 0;
        if (questionType == "MC") {
            id = MultipleChoice.size();
            MultipleChoice.push_back(
                Question(id, topicName, questionType, options,
            answer, questionText));
        } else if (questionType == "TF") {
            id = TrueFalse.size();
            TrueFalse.push_back(Question(id, topicName, questionType, options,
            answer, questionText));
        } else if (questionType == "MATCH") {
            id = Matching.size();
            Matching.push_back(Question(id, topicName, questionType, options,
            answer, questionText));
        } else if (questionType == "FILL") {
            id = FillInBlank.size();
            FillInBlank.push_back(Question(id, topicName, questionType, options,
            answer, questionText));
        } else {
            throw std::runtime_error(TopicName + ": Question Type not Found");
        }
    }
}

