#include "TestingTest.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <vector>


#include "../../controller/SeleepController.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void TestingTest::onRun() {
  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  /* Get object mapper component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                  objectMapper);

  /* Add SeleepController endpoints to the router of the test server */
  runner.addController(std::make_shared<SeleepController>());

  /* Run test */
  runner.run(
      [this, &runner] {
        /* Get client connection provider for Api Client */
        OATPP_COMPONENT(
            std::shared_ptr<oatpp::network::ClientConnectionProvider>,
            clientConnectionProvider);

        /* Get object mapper component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                        objectMapper);

        /* Create http request executor for Api Client */
        auto requestExecutor =
            oatpp::web::client::HttpRequestExecutor::createShared(
                clientConnectionProvider);

        /* Create Test API client */
        auto client =
            MyApiTestClient::createShared(requestExecutor, objectMapper);

        /* Call server API and assert that server responds with 200 */

        // API POST endpoint testing
        // API POST good and bad data
        // Ensure data is correct expecations - non empty etc

        auto response = client->getTestingMC();
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

        response = client->getTestingTF();
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

        response = client->getTestingMATCH();
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

        response = client->getTestingFILL();
        qResponse = response->readBodyToDto<oatpp::Object<QuestionDTO>>(
            objectMapper.get());
        OATPP_ASSERT(response->getStatusCode() == 200);
        OATPP_ASSERT(qResponse->question != "");
        OATPP_ASSERT(qResponse->topicName != "");
        OATPP_ASSERT(qResponse->questionType != "");
        OATPP_ASSERT(qResponse->errorMessage == "");

        // Good answer - MC
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MC\", \"topic\": \"Testing\", \"answer\": "
            "[\"When you test a system without knowing its implementation\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        /* Read response body as MessageDto */
        auto message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == true);

        // Good answer - TF
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"TF\", \"topic\": \"Testing\", \"answer\": "
            "[\"True\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        /* Read response body as MessageDto */
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == true);

        // Good answer - MATCH
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MATCH\", \"topic\": \"Testing\", "
            "\"answer\": [\"Acceptance\", \"Integration\", \"System\", "
            "\"Unit\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        /* Read response body as MessageDto */
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == true);

        // Good answer - FILL
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"FILL\", \"topic\": \"Testing\", "
            "\"answer\": [\"Partition\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        /* Read response body as MessageDto */
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == true);

        // BAD answer - MC
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MC\", \"topic\": \"Testing\", \"answer\": "
            "[\"When you test a system knowing how it is implemented\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        /* Read response body as MessageDto */
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == false);

        // BAD answer - TF
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"TF\", \"topic\": \"Testing\", \"answer\": "
            "[\"False\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        /* Read response body as MessageDto */
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == false);

        // BAD answer - MATCH
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MATCH\", \"topic\": \"Testing\", "
            "\"answer\": [\"Unit\", \"Acceptance\", \"Integration\", "
            "\"System\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        /* Read response body as MessageDto */
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == false);

        // BAD answer - FILL
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"FILL\", \"topic\": \"Testing\", "
            "\"answer\": [\"Not take into account\"]}");
        OATPP_ASSERT(response->getStatusCode() == 200);
        /* Read response body as MessageDto */
        message = response->readBodyToDto<oatpp::Object<AnswerDTO>>(
            objectMapper.get());
        OATPP_ASSERT(message);
        OATPP_ASSERT(message->answer == false);

        // BAD ID input - Any
        response = client->postAnswer(
            "{\"id\": 100, \"type\": \"MC\", \"topic\": \"Testing\", "
            "\"answer\": [\"When you test a system knowing how it is "
            "implemented\"]}");
        OATPP_ASSERT(response->getStatusCode() == 400);

        // Bad Array answer - MC
        response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MC\", \"topic\": \"Testing\", \"answer\": "
            "[\"Acceptance\", \"Integration\", \"System\", \"Unit\"]}");
        OATPP_ASSERT(response->getStatusCode() == 400);
      },
      std::chrono::minutes(10) /* test timeout */);
  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
