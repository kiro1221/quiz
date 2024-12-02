#include "SolidModelTest.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <vector>



#include "../../controller/SeleepController.hpp"
#include "../../service/Model/SolidModel.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void SolidModelTest::onRun() {
  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  /* Add SeleepController endpoints to the router of the test server */
  runner.addController(std::make_shared<SeleepController>());

  /* Run test */
  runner.run(
      [this, &runner] {
        /* Get client connection provider for API Client */
        OATPP_COMPONENT(
            std::shared_ptr<oatpp::network::ClientConnectionProvider>,
            clientConnectionProvider);

        /* Get object mapper component inside the lambda */
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                        objectMapper);

        /* Create HTTP request executor for API Client */
        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::createShared(
                clientConnectionProvider);

        /* Create Test API client */
        auto client =
            MyApiTestClient::createShared(requestExecutor, objectMapper);

        auto response = client->getSolidMC();
        OATPP_ASSERT(response->getStatusCode() == 200);
        auto qResponse = response->readBodyToDto<oatpp::Object<QuestionDTO>>(
            objectMapper.get());
        OATPP_ASSERT(qResponse->question != "");
        OATPP_ASSERT(qResponse->topicName != "");
        OATPP_ASSERT(qResponse->questionType != "");
        OATPP_ASSERT(qResponse->errorMessage == "");
        std::vector<std::string> MCArr;
        for (const auto &item : *qResponse->options) {
          MCArr.push_back(item->c_str());  // Convert to std::string
        }
        OATPP_ASSERT(MCArr.size() != 0);

        response = client->getSolidTF();
        qResponse = response->readBodyToDto<oatpp::Object<QuestionDTO>>(
            objectMapper.get());
        OATPP_ASSERT(response->getStatusCode() == 200);
        OATPP_ASSERT(qResponse->question != "");
        OATPP_ASSERT(qResponse->topicName != "");
        OATPP_ASSERT(qResponse->questionType != "");
        OATPP_ASSERT(qResponse->errorMessage == "");
        std::vector<std::string> TFArr;
        for (const auto &item : *qResponse->options) {
          TFArr.push_back(item->c_str());  // Convert to std::string
        }
        OATPP_ASSERT(TFArr.size() != 0);

        response = client->getSolidMATCH();
        qResponse = response->readBodyToDto<oatpp::Object<QuestionDTO>>(
            objectMapper.get());
        OATPP_ASSERT(response->getStatusCode() == 200);
        OATPP_ASSERT(qResponse->question != "");
        OATPP_ASSERT(qResponse->topicName != "");
        OATPP_ASSERT(qResponse->questionType != "");
        OATPP_ASSERT(qResponse->errorMessage == "");
        std::vector<std::string> MATCHArr;
        for (const auto &item : *qResponse->options) {
          MATCHArr.push_back(item->c_str());  // Convert to std::string
        }
        OATPP_ASSERT(MATCHArr.size() != 0);

        response = client->getSolidFILL();
        qResponse = response->readBodyToDto<oatpp::Object<QuestionDTO>>(
            objectMapper.get());
        OATPP_ASSERT(response->getStatusCode() == 200);
        OATPP_ASSERT(qResponse->question != "");
        OATPP_ASSERT(qResponse->topicName != "");
        OATPP_ASSERT(qResponse->questionType != "");
        OATPP_ASSERT(qResponse->errorMessage == "");

        // Test SOLID
        // MC question with the wrong answer
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MC\", \"topic\": \"Solid\", \"answer\": "
            "[\"Open/Closed Principle\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        auto message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == false);
        // TF question with  wrong answer
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"TF\", \"topic\": \"Solid\", \"answer\": "
            "[\"True\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == false);
        // FILL question with wrong answer
        response = client->postAnswer(
            "{\"id\": 1, \"type\": \"FILL\", \"topic\": \"Solid\", \"answer\": "
            "[\"Wrong answer\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == false);
        // TF correct answer
        response = client->postAnswer(
            "{\"id\": 2 \"type\": \"TF\", \"topic\": \"Solid\", \"answer\": "
            "[\"True\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == true);
        // MC correct answer
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MC\", \"topic\": \"Solid\", \"answer\": "
            "[\"Single Responsibility Principle\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == true);
        // // Fill correct answer
        response = client->postAnswer(
            "{\"id\": 1, \"type\": \"FILL\", \"topic\": \"Solid\", \"answer\": "
            "[\"Single Responsibility Principle\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == true);
        // Correct match
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MATCH\", \"topic\": \"Solid\", "
            "\"answer\": [\"A class that manages user data should not also "
            "handle report generation.\", \"A large interface is split into "
            "smaller, more specific interfaces for clients.\", \"A subclass "
            "should be able to replace its superclass without altering the "
            "program’s functionality.\", \"A logging system allows new types "
            "of log outputs without modifying existing code.\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == true);
        // Incorrect match
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MATCH\", \"topic\": \"Solid\", "
            "\"answer\": [\"wrong\", \"matchinh\", \"answers\", \"!!\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == false);
        // Incorrect Id
        response = client->postAnswer(
            "{\"id\": 999 \"type\": \"TF\", \"topic\": \"Solid\", \"answer\": "
            "[\"True\"]}");
        OATPP_ASSERT(response->getStatusCode() == 400);
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->errorMessage ==
                     "TopicModel: Error in Multiple Choice ID");
      },
      std::chrono::minutes(10) /* test timeout */);

  /* Wait for all server threads to finish */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
