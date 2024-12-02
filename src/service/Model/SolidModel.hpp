#ifndef SOLIDMODEL_HPP
#define SOLIDMODEL_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "TopicModel.hpp"

class SolidModel : public TopicModel {
 public:
  /**
   * @brief Constructor for TopicModelSubclass
   */
  SolidModel();

  /**
   * @brief Destructor for TopicModelSubclass
   */
  ~SolidModel();

  /**
   * @brief Implementation of the pure virtual function to read questions.
   */
  void readInQuestions() override;
};

#endif /* SOLIDMODEL_HPP */
