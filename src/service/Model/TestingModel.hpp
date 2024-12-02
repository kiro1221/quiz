#ifndef TESTINGMODEL_HPP
#define TESTINGMODEL_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "TopicModel.hpp"

class TestingModel : public TopicModel {
 public:
    /**
     * @brief Constructor for TopicModelSubclass
     */
    TestingModel();

    /**
     * @brief Destructor for TopicModelSubclass
     */
    ~TestingModel();

    /**
     * @brief Implementation of the pure virtual function to read questions.
     */
    void readInQuestions() override;
};

#endif /* TESTINGMODEL_HPP */

