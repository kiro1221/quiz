#ifndef Controller_hpp
#define Controller_hpp

#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../dto/DTOs.hpp"
#include "../service/Model/DesignPatternModel.hpp"
#include "../service/Model/DoxygenModel.hpp"
#include "../service/Model/SolidModel.hpp"
#include "../service/Model/TestingModel.hpp"
#include "../service/Model/VersionControlModel.hpp"
#include "../service/TopicController/TopicController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  ///< Begin Codegen

class SeleepController : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  SeleepController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {
    try {
      models = {new DesignPattern(), new SolidModel(), new TestingModel(),
                new DoxygenModel(), new VersionControlModel()};
      CoreController = new TopicController(models);
    } catch (const std::exception &e) {
      models = {};
      CoreController = new TopicController(models);
      contructorException = e.what();
      constructionFailed = true;
      return;
    }
    contructorException = "";
    constructionFailed = false;
    return;
  }

  ~SeleepController() { delete CoreController; }

  ADD_CORS(getQuestion)  // Needed to allow for cross domain access

  // Example:
  // http://localhost:9100/seleep/questions?topic={topicInput}&type={typeInput}
  //?topic={topicInput}&type={typeInput}
  // change to Post later. GET is for test
  // deconstructor
  ENDPOINT("GET", "/seleep/questions", getQuestion,
           QUERY(String, topicInput, "topic"),
           QUERY(String, typeInput, "type")) {
    Question curQues;
    auto dto = QuestionDTO::createShared();

    if (constructionFailed) {
      dto->statusCode = 500;
      dto->errorMessage = contructorException;
      return createDtoResponse(Status::CODE_500, dto);
    }

    try {
      curQues = CoreController->getQuestion(topicInput, typeInput, -1);
    } catch (const std::exception &e) {
      dto->statusCode = 400;
      dto->errorMessage = e.what();
      return createDtoResponse(Status::CODE_400, dto);
    }

    dto->statusCode = 200;
    dto->topicName = curQues.GetTopicName();
    dto->questionType = curQues.GetQuestionType();
    dto->id = curQues.GetID();
    dto->question = curQues.GetQuestionText();
    dto->options = {};
    std::vector<std::string> curOptions = curQues.GetOptions();
    int optionsSize = curOptions.size();
    for (int i = 0; i < optionsSize; i++) {
      dto->options->push_back(curOptions[i]);
    }
  

    dto->errorMessage = "";

    return createDtoResponse(Status::CODE_200, dto);
  }

  // Body text is, Topic, Type, ID
  /*Example Body text
  {
  "id": 1
    "type": "test"
    "answer": ["Test","Test1","Test2"]
}
  */
  ENDPOINT("POST", "/seleep/answer", answer,
           BODY_DTO(Object<AnswerBodyDTO>, answerdataDTO)) {
    auto dto = AnswerDTO::createShared();

    if (constructionFailed) {
      dto->statusCode = 500;
      dto->errorMessage = contructorException;
      return createDtoResponse(Status::CODE_500, dto);
    }

    // Use DTO to read in values
    // Call checkAnswer(id,type,answer)
    if (constructionFailed) {
      dto->statusCode = 500;
      dto->errorMessage = contructorException;
      return createDtoResponse(Status::CODE_500, dto);
    }

    int id = answerdataDTO->id;
    std::string topic = answerdataDTO->topic;
    std::string type = answerdataDTO->type;
    // Convert the oatpp::List<oatpp::String> to std::vector<std::string>
    auto arr = answerdataDTO->answer;  // Access the list
    std::vector<std::string> ansArr;
    for (const auto &item : *arr) {
      ansArr.push_back(item->c_str());  // Convert to std::string
    }

    bool result = false;
    try {
      result = CoreController->checkAnswer(id, topic, type, ansArr);
    } catch (const std::exception &e) {
      dto->statusCode = 400;
      dto->errorMessage = e.what();
      return createDtoResponse(Status::CODE_400, dto);
    }

    dto->statusCode = 200;
    dto->answer = result;
    return createDtoResponse(Status::CODE_200, dto);
  }

  ENDPOINT("GET", "/seleep", root) {
    auto dto = ListDTO::createShared();
    std::vector<std::string> topList = CoreController->getTopics();
    int topSize = topList.size();
    dto->topics = {};
    for (int i = 0; i < topSize; i++) {
      dto->topics->push_back(topList[i]);
    }
    dto->statusCode = 200;
    return createDtoResponse(Status::CODE_200, dto);
  }
  ENDPOINT("GET", "/", getHeader) {
    std::ifstream file(
        "static/index.html");  
    if (!file.is_open()) {
      return createResponse(Status::CODE_404, "Header HTML file not found");
    }

    // Read the file content
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string headerHtml = buffer.str();
    file.close();

    auto response = createResponse(Status::CODE_200, headerHtml);
    response->putHeader("Content-Type", "text/html");
    return response;
  }

 private:
  TopicController *CoreController;
  std::vector<TopicModel *> models;
  bool constructionFailed;
  std::string contructorException;
};
#include OATPP_CODEGEN_END(ApiController)  ///< End Codegen

#endif /* Controller_hpp */
