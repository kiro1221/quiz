#ifndef TOPIC_CONTROLLER_hpp
#define TOPIC_CONTROLLER_hpp

#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "src/service/Question/Question.hpp"
#include "../Model/TopicModel.hpp"
#include "src/dto/DTOs.hpp"

/**
 * @class TopicController TopicController.hpp "TopicController.hpp"
 * @brief Controller class for topics.
 * 
 */
class TopicController {
 public:
 /**
  * @brief Construct a new TopicController object.
  * 
  */
  TopicController(std::vector<TopicModel*> modelsI);
  /**
   * @brief Destroy the TopicController object.
   * 
   */
  ~TopicController();

  /**
   * @brief Adds a Topic Model to the controller on the end.
   * 
   * @param modelI The added Topic Model.
   */
  void push_back(TopicModel* modelI);

  /**
   * @brief Removes a Topic Model from the end of the vector of models.
   * 
   * @param modelI The added Topic Model.
   */
  void pop_back();

  /**
   * @brief Get a Question based on the string topic, string type, and id given.
   * 
   * @param topic String form of the question topic.
   * @param type String form of the question type.
   * @param id ID for a specific question.
   * @return Question The returned question.
   */
  Question getQuestion(std::string topic, std::string type, int id);

  std::vector<std::string> getTopics();

  bool checkAnswer(int id, std::string topic,
    std::string type, std::vector<std::string> answers);

 private:
  std::vector<TopicModel*> models;

  /**
   * @brief Transforms a string for the topic to an integer of the topic.
   * 
   * @param type String form of the question topic.
   * @return Integer form of the question topic.
   */
  int topicToNum(std::string topic);
  /**
   * @brief Transforms a string for the type to an integer of the type.
   * 
   * @param type String form of the question type.
   * @return Integer form of the question type.
   */
  int typeToNum(std::string type);

  /**
   * @brief Gets a random question topic.
   * 
   * @return Integer form of the question topic.
   */
  int randomTopic();
  /**
   * @brief Gets a random question type for a given question topic.
   * 
   * @param numTopic Integer form of the question topic.
   * @return Integer form of the question type.
   */
  int randomType(int numTopic);
  /**
   * @brief Gets a random id for a given question topic and type.
   * 
   * @param numTopic Integer form of the question topic.
   * @param numType Integer form of the question type.
   * @return Integer for the question type id.
   */
  int randomQuestionID(int numTopic, int numType);
};
#endif /* TOPIC_CONTROLLER_hpp */
