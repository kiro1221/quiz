/**
 * @author Matthew MacMaster | email
 * @modified James Huston | jamzhuston@gmail.com | huston@uleth.ca
 *
 */

#include <iostream>
#include <string>
#include <vector>

#include "Question.hpp"

Question::Question() {}

Question::Question(int id, std::string topicName, std::string questionType,
  std::vector<std::string> options, std::vector<std::string> answer,
  std::string questionText) {
    SetID(id);
    SetAnswer(answer);
    SetOptions(options);
    SetQuestionText(questionText);
    SetQuestionType(questionType);
    SetTopicName(topicName);
}

Question::~Question() {}

Question::Question(const Question& ADT) {
  topicName = ADT.topicName;
  questionType = ADT.questionType;
  id = ADT.id;
  questionText = ADT.questionText;
  options = ADT.options;
  answer = ADT.answer;
}

Question& Question::operator=(const Question& ADT) {
  topicName = ADT.topicName;
  questionType = ADT.questionType;
  id = ADT.id;
  questionText = ADT.questionText;
  options = ADT.options;
  answer = ADT.answer;
  return *this;
}

//Getters
std::string Question::GetTopicName() {
  return topicName;
}

std::string Question::GetQuestionType() {
  return questionType;
}

std::string Question::GetQuestionText() {
  return questionText;
}

std::vector<std::string> Question::GetAnswer() {
  return answer;
}

int Question::GetID() {
  return id;
}

void Question::SetID(int ID) {
  id = ID;
}

std::vector<std::string> Question::GetOptions() {
  return options;
}

//Setters
void Question::SetOptions(std::vector<std::string> optionsList) {
  options = optionsList;
}

void Question::SetTopicName(std::string topic) {
  topicName = topic;
}

void Question::SetQuestionType(std::string type) {
  questionType = type;
}

void Question::SetQuestionText(std::string text) {
  questionText = text;
}

void Question::SetAnswer(std::vector<std::string> answers) {
  answer = answers;
}

int Question::getAnswerSize() {
  return answer.size();
}
