/**
 * @author James Huston | jamzhuston@gmail.com | huston@uleth.ca
 *
 */

#ifndef VERSION_CONTROL_MODEL
#define VERSION_CONTROL_MODEL
#include <vector>
#include <string>

#include "../Question/Question.hpp"
#include "TopicModel.hpp"

/**
 *
 *
 */
class VersionControlModel : public TopicModel {
 public:
  /**
   *
   *
   */
  VersionControlModel();

  /**
   *
   *
   */
  ~VersionControlModel();

  /**
   *
   *
   */
  void readInQuestions() override;

 private:
  /**
   * @brief class to manage reading files, hiding within model
   * @brief will use functor design patternf
   */
  class FileReader {
   public:
    /**
     * @brief default 
     *
     */
    FileReader(std::string path);

    /**
     *
     *
     */
    std::vector<Question> operator()(std::string file);

   private:
    std::string path;
    /**
     *
     *
     */
    Question parseStringToQuestion(std::string unformatted);

    /**
     *
     *
     *
     */
    std::vector<std::string> convertToVectorOfStrings(
      std::string question, char delimeter);
  };
};


#endif /* VERSION_CONTROL_MODEL */
