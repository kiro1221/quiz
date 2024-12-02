#ifndef DOXYGENMODEL_HPP
#define DOXYGENMODEL_HPP


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "TopicModel.hpp"

class DoxygenModel : public TopicModel {
 public:
    /**
     * @brief Constructor for TopicModelSubclass
     */
    DoxygenModel();

    /**
     * @brief Destructor for TopicModelSubclass
     */
    ~DoxygenModel();

    /**
     * @brief Implementation of the pure virtual function to read questions.
     */
    void readInQuestions() override;
};

#endif /* DOXYGENMODEL_HPP */
