#ifndef DESIGNPATTHERN_HPP
#define DESIGNPATTHERN_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TopicModel.hpp"

class DesignPattern : public TopicModel {
 public:
    /**
     * @brief Constructor for TopicModelSubclass
     */
    DesignPattern();

    /**
     * @brief Destructor for TopicModelSubclass
     */
    ~DesignPattern();

    /**
     * @brief Implementation of the pure virtual function to read questions.
     */
    void readInQuestions() override;
};

#endif /* DESIGNPATTHERN_HPP */

