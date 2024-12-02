/**
 * @author James Huston | jamzhuston@gmail.com | huston@uleth.ca
 *
 *
 */

#include "TopicModel.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "src/service/Question/Question.hpp"

TopicModel::TopicModel() {}

TopicModel::~TopicModel() {}

Question TopicModel::getQuestion(int numType, int id) {
  switch (numType) {
    case 0:
      if (id < 0 || id >= MultipleChoice.size()) {
        throw std::runtime_error("TopicModel: Error in Multiple Choice ID");
      }
      return MultipleChoice[id];
      break;

    case 1:
      if (id < 0 || id >= TrueFalse.size()) {
        throw std::runtime_error("TopicModel: Error in True False ID");
      }
      return TrueFalse[id];
      break;

    case 2:
      if (id < 0 || id >= Matching.size()) {
        throw std::runtime_error("TopicModel: Error in Matching ID");
      }
      return Matching[id];
      break;

    case 3:
      if (id < 0 || id >= FillInBlank.size()) {
        throw std::runtime_error("TopicModel: Error in Fill in Blank ID");
      }
      return FillInBlank[id];
      break;
    default:
      break;
  }
  throw std::runtime_error("TopicModel: Reached end of getQuestion");
}

int TopicModel::getQuestionsCount(int numType) {
  switch (numType) {
    case 0:
      return MultipleChoice.size();
      break;
    case 1:
      return TrueFalse.size();
      break;
    case 2:
      return Matching.size();
      break;
    case 3:
      return FillInBlank.size();
      break;
    default:
      break;
  }
  throw std::runtime_error("TopicModel: Reached end of getQuestionsCount");
}

int TopicModel::getNumQuestionTypes() { return numQuestionTypes; }

std::string TopicModel::getTopicName() { return TopicName; }

bool TopicModel::checkAnswer(int id, int type,
                             std::vector<std::string> answers) {
  // Check corresponding array via type
  // Check corresponding index by id
  // Compare Arrays  of answer and answers
  switch (type) {
    case 0:
      if (id < 0 || id >= MultipleChoice.size()) {
        throw std::runtime_error("TopicModel: Error in Multiple Choice ID");
      }
      if (answers.size() != MultipleChoice[id].getAnswerSize()) {
        throw std::runtime_error("Different Sized Answer Arrays");
      }
      if (MultipleChoice[id].GetID() != id) {
        throw std::runtime_error("Different Ids");
      }
      return (MultipleChoice[id].GetAnswer() == answers);
      break;

    case 1:
      if (id < 0 || id >= TrueFalse.size()) {
        throw std::runtime_error("TopicModel: Error in Multiple Choice ID");
      }
      if (answers.size() != TrueFalse[id].getAnswerSize()) {
        throw std::runtime_error("Different Sized Answer Arrays");
      }
      return (TrueFalse[id].GetAnswer() == answers);
      break;

    case 2:
      if (id < 0 || id >= Matching.size()) {
        throw std::runtime_error("TopicModel: Error in Multiple Choice ID");
      }
      if (answers.size() != Matching[id].getAnswerSize()) {
        throw std::runtime_error("Different Sized Answer Arrays");
      }
      return (Matching[id].GetAnswer() == answers);
      break;

    case 3:
      if (id < 0 || id >= FillInBlank.size()) {
        throw std::runtime_error("TopicModel: Error in Multiple Choice ID");
      }
      if (answers.size() != FillInBlank[id].getAnswerSize()) {
        throw std::runtime_error("Different Sized Answer Arrays");
      }
      return (FillInBlank[id].GetAnswer() == answers);
      break;

    default:
      throw std::runtime_error("TopicModel: Defaulted in getQuestion");
      return false;
      break;
  }
  throw std::runtime_error("TopicModel: Reached end of getQuestion");
  return false;
}
