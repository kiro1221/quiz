#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "TopicController.hpp"
#include "src/service/Question/Question.hpp"
#include "../Model/TopicModel.hpp"
#include "src/dto/DTOs.hpp"

TopicController::TopicController(std::vector<TopicModel*> modelsI) {
    models = modelsI;
}

TopicController::~TopicController() {
    int modelsSize = models.size();
    for (int i = 0; i < modelsSize; i++) {
        delete models[i];
    }
}

void TopicController::push_back(TopicModel* modelI) {
    models.push_back(modelI);
}

void TopicController::pop_back() {
    models.pop_back();
}

Question TopicController::getQuestion(
    std::string topic, std::string type, int id) {
    int numTopic = 0;
    if (topic == "Random") {
        numTopic = randomTopic();
    } else {
        numTopic = topicToNum(topic);
    }
    int numType = 0;
    if (type == "Random") {
        numType = randomType(numTopic);
    } else {
        numType = typeToNum(type);
    }
    if (id == -1) {
        id = randomQuestionID(numTopic, numType);
    }
    return models[numTopic]->getQuestion(numType, id);
}
std::vector<std::string> TopicController::getTopics() {
    int modelsSize = models.size();
    std::vector<std::string> topicList = {};
    for (int i = 0; i < modelsSize; i++) {
        topicList.push_back(models[i]->getTopicName());
    }
    return topicList;
}


int TopicController::topicToNum(std::string topic) {
    if (topic == "DesignPatterns") {
        return 0;
    } else if (topic == "Solid") {
        return 1;
    } else if (topic == "Testing") {
        return 2;
    } else if (topic == "Doxygen") {
        return 3;
    } else if (topic == "VersionControl") {
        return 4;
    }
    throw std::runtime_error("TopicController: Reached end of topicToNum");
}

int TopicController::typeToNum(std::string type) {
    if (type == "MC") {
        return 0;
    } else if (type == "TF") {
        return 1;
    } else if (type == "MATCH") {
        return 2;
    } else if (type == "FILL") {
        return 3;
    }
    throw std::runtime_error("TopicController: Reached end of typeToNum");
}

int TopicController::randomTopic() {
  srand(time(NULL));
  int numTopics = models.size();
  return (rand() % numTopics);
}

int TopicController::randomType(int numTopic) {
  srand(time(NULL));
  int modelsSize = models.size();
  if (modelsSize <= 0) {
    throw std::runtime_error(
        "TopicController: Number of Models Cannot be <= 0 in randomType");
  }
  if (numTopic < 0 && numTopic >= modelsSize) {
    throw std::runtime_error(
        "TopicController: Topic number out of Bounds in randomType");
  }
  int numQuestionTypes = models[numTopic]->getNumQuestionTypes();
  return (rand() % numQuestionTypes);
}

int TopicController::randomQuestionID(int numTopic, int numType) {
  srand(time(NULL));
  int modelsSize = models.size();
  if (modelsSize <= 0) {
    throw std::runtime_error(
    "TopicController: Number of Models Cannot be <= 0 in randomQuestionID");
  }
  if (numTopic < 0 && numTopic >= modelsSize) {
    throw std::runtime_error(
    "TopicController: Topic number out of Bounds in randomQuestionID");
  }
  int questionSize = models[numTopic]->getQuestionsCount(numType);
  if (questionSize <= 0) {
    throw std::runtime_error(
    "TopicController: Question Size Cannot be <= 0 in randomQuestionID");
  }
  int id = rand() % questionSize;
  if (id < 0 && id >= questionSize) {
    throw std::runtime_error(
    "TopicController: Question ID out of bounds in randomQuestionID");
  }
  return id;
}

bool TopicController::checkAnswer(int id, std::string topic,
    std::string type, std::vector<std::string> answers) {
    int numTopic = topicToNum(topic);
    int numType = typeToNum(type);
    return models[numTopic]->checkAnswer(id, numType, answers);
}
