/**
 * @author James Huston | jamzhuston@gmail | huston@gmail.com
 * @date 11/05/2024
 *
 */

#ifndef TOPICMODEL_hpp
#define TOPICMODEL_hpp

#include <iostream>
#include <string>
#include <vector>

#include "src/service/Question/Question.hpp"

/**
 * @class TopicModel in TopicModel.hpp "TopicModel.hpp"
 * @brief Model class for topics.
 *
 */
class TopicModel {
 public:
  /**
   * @brief Constructor for TopicModel
   *
   */
  TopicModel();
  /**
   * @brief Destructor for TopicModel
   *
   */
  ~TopicModel();

  /**
   * @brief Pure virtual function for reading in the data from a file.
   *
   */
  virtual void readInQuestions() = 0;

  /**
   * @brief Getter function for questions in each list.
   *
   * @return Question from the correct list.
   */
  Question getQuestion(int numType, int id);

  /**
   * @brief Getter function for number of questions.
   *
   * @return int the number of questions.
   */
  int getQuestionsCount(int numType);

  /**
   * @brief Get the number of question types.
   *
   * @return int number of question types.
   */
  int getNumQuestionTypes();

  // Design Note
  // Some level of redundency here, topic name is in data and declared here
  // Due to time restrictions the redundency remains
  std::string getTopicName();

  bool checkAnswer(int id, int type, std::vector<std::string> answers);

 protected:
  // Design notes
  // choice between four vectors and a map.
  const int numQuestionTypes = 4;
  std::string TopicName = "baseType";
  std::vector<Question> MultipleChoice;
  std::vector<Question> TrueFalse;
  std::vector<Question> Matching;
  std::vector<Question> FillInBlank;
};

#endif /* TOPICMODEL_hpp */
