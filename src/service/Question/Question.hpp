/**
 * @author Matthew MacMaster | email
 * @modified James Huston | jamzhuston@gmail.com | huston@uleth.ca
 *
 */

#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <string>
#include <vector>

/**
 * @class Question in Question.hpp "Question.hpp"
 */
class Question {
 public:
 /**
  * @brief Constructor for Question
  *
  */
  Question();

  /**
   * @brief Copy Constructor for Question
   * @param[in] ADT the Question that is being copied
   */
  Question(const Question& ADT);

 /**
  * @brief Constructor for Question
  *
  */
  Question(int id, std::string topicName, std::string questionType,
  std::vector<std::string> options, std::vector<std::string> answer,
  std::string questionText);


  /**
   * @brief Destructor for Question
   *
   */
  ~Question();


  /**
   * @brief Assignment operator for Question
   * @param[in] ADT the Question that is being copied
   */
  Question& operator=(const Question& ADT);

 /**
  * @brief Getter for topicName
  * @return string the topicName
  */
  std::string GetTopicName();

 /**
  * @brief Setter for topicName
  * @param[in] topic the topic of the question
  */
  void SetTopicName(std::string topic);

 /**
  * @brief Getter for Question
  * @return string the questionType
  */
  std::string GetQuestionType();

 /**
  * @brief Setter for Question
  * @param[in] type the type of question
  */
  void SetQuestionType(std::string type);

 /**
  * @brief Getter for QuestionText
  * @return string the questionText
  */
  std::string GetQuestionText();

 /**
  * @brief Setter for QuestionText
  * @param[in] text the actual question
  */
  void SetQuestionText(std::string text);

 /**
  * @brief Getter for options
  * @return vector<string> the list of options
  */
  std::vector<std::string> GetOptions();

 /**
  * @brief Setter for options
  * @param[in] optionList the list of options
  */
  void SetOptions(std::vector<std::string> optionsList);

 /**
  * @brief Getter for answer
  * @return vector<string> the answer(s) of the question
  */
  std::vector<std::string> GetAnswer();

 /**
  * @brief Setter for answer
  * @param[in] answers the answer[s] of the question
  */
  void SetAnswer(std::vector<std::string> answers);

 /**
  * @brief Getter for id
  * @return int the id of the question
  */
  int GetID();

 /**
  * @brief Setter for id
  * @param[in] the ID of the question
  */
  void SetID(int ID);

  int getAnswerSize();

 private:
  std::string topicName = "Rand";   // enums
  std::string questionType = "MC";  // enums
  int id = 1;
  std::string questionText = "";
  std::vector<std::string> options = {"A", "B", "C", "D"};
  std::vector<std::string> answer = {"A"};
};

#endif /* QUESTION_CLASS_HPP_INCLUDED */

