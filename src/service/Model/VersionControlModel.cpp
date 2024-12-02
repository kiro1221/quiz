#include "VersionControlModel.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

VersionControlModel::VersionControlModel() {
  TopicName = "VersionControl";
  readInQuestions();
}

VersionControlModel::~VersionControlModel() {}

void VersionControlModel::readInQuestions() {
  FileReader file_reader("src/service/Data");
  MultipleChoice = file_reader("VC_Multiple_Choice.txt");
  Matching = file_reader("VC_Matching.txt");
  FillInBlank = file_reader("VC_Fill_In_The_Blank.txt");
  TrueFalse = file_reader("VC_True_Or_False.txt");
}

VersionControlModel::FileReader::FileReader(std::string path):
  path(path) {}

std::vector<Question> VersionControlModel::FileReader::operator()
  (std::string file) {
  std::vector<Question> question_list;
  std::fstream reader;
  reader.open(path + "/" + file);
  if (reader.is_open()) {
    std::string question_string;
    while (getline(reader, question_string)) {
      question_string.erase(std::remove(question_string.begin(),
        question_string.end(), '\r'), question_string.end());
      question_list.push_back(parseStringToQuestion(question_string));
      question_string = "";
    }
    reader.close();
  } else {
    throw std::runtime_error(
      "FileReader: File either doesn't exist or is named incorrectly");
  }
  return question_list;
}

Question VersionControlModel::FileReader::parseStringToQuestion(
  std::string unformated) {
  Question question;
  std::vector<std::string> tempVector;
  std::vector<std::string> converted = convertToVectorOfStrings(
    unformated, '-');
  question.SetID(std::stoi(converted[0]));
  question.SetTopicName(converted[1]);
  question.SetQuestionType(converted[2]);
  question.SetQuestionText(converted[3]);
  if (converted[4].find(',') > converted[4].length()) {
    tempVector.push_back(converted[4]);
    question.SetOptions(tempVector);
    tempVector.clear();
  } else {
    question.SetOptions(convertToVectorOfStrings(converted[4], ','));
  }
  if (converted[5].find(',') > converted[5].length()) {
    tempVector.push_back(converted[5]);
    question.SetAnswer(tempVector);
    tempVector.clear();
  } else {
    question.SetAnswer(convertToVectorOfStrings(converted[5], ','));
  }
  return question;
}

std::vector<std::string> VersionControlModel::FileReader::
convertToVectorOfStrings(std::string question, char delimeter) {
  std::stringstream string_reader(question);
  std::string temp;

  std::vector<std::string> questionAttributes;
  while (getline(string_reader, temp, delimeter)) {
    temp.erase(std::remove(temp.begin(), temp.end(), '\r'),
      temp.end());
    questionAttributes.push_back(temp);
  }
  return questionAttributes;
}
