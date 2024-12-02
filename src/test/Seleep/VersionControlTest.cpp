/**
 * @author James Huston | huston@uleth.ca
 * @date 25/11/2024
 */

#include "VersionControlTest.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <vector>


#include "../../controller/SeleepController.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

const int OK_STATUS_CODE = 200;
const int TEST_TIMEOUT = 10;
const int SLEEP_TIME = 1;

void VersionControlTest::onRun() {
  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  /* Add SeleepController endpoints to the router of the test server */
  runner.addController(std::make_shared<SeleepController>());

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

        /* Get Tests */
        auto response_mc = client->getVersionControlMC();
        OATPP_ASSERT(response_mc->getStatusCode() == OK_STATUS_CODE);
        auto McResponse =
            response_mc->readBodyToDto<oatpp::Object<QuestionDTO>>(
                objectMapper.get());
        OATPP_ASSERT(McResponse->question != "");
        OATPP_ASSERT(McResponse->topicName != "");
        OATPP_ASSERT(McResponse->questionType != "");
        OATPP_ASSERT(McResponse->errorMessage == "");
        std::vector<std::string> MCArr;
        for (const auto &item : *McResponse->options) {
          MCArr.push_back(item->c_str());  // Convert to std::string
        }
        OATPP_ASSERT(MCArr.size() != 0);

        auto response_match = client->getVersionControlMATCH();
        OATPP_ASSERT(response_match->getStatusCode() == OK_STATUS_CODE);
        auto MATCHResponse =
            response_match->readBodyToDto<oatpp::Object<QuestionDTO>>(
                objectMapper.get());
        OATPP_ASSERT(MATCHResponse->question != "");
        OATPP_ASSERT(MATCHResponse->topicName != "");
        OATPP_ASSERT(MATCHResponse->questionType != "");
        OATPP_ASSERT(MATCHResponse->errorMessage == "");
        std::vector<std::string> MATCHArr;
        for (const auto &item : *MATCHResponse->options) {
          MATCHArr.push_back(item->c_str());  // Convert to std::string
        }
        OATPP_ASSERT(MATCHArr.size() != 0);

        auto response_tf = client->getVersionControlTF();
        OATPP_ASSERT(response_tf->getStatusCode() == OK_STATUS_CODE);
        auto tfResponse =
            response_tf->readBodyToDto<oatpp::Object<QuestionDTO>>(
                objectMapper.get());
        OATPP_ASSERT(tfResponse->question != "");
        OATPP_ASSERT(tfResponse->topicName != "");
        OATPP_ASSERT(tfResponse->questionType != "");
        OATPP_ASSERT(tfResponse->errorMessage == "");
        std::vector<std::string> TFArr;
        for (const auto &item : *tfResponse->options) {
          TFArr.push_back(item->c_str());  // Convert to std::string
        }
        OATPP_ASSERT(TFArr.size() != 0);

        auto response_fill = client->getVersionControlFILL();
        OATPP_ASSERT(response_fill->getStatusCode() == OK_STATUS_CODE);
        auto fillResponse =
            response_fill->readBodyToDto<oatpp::Object<QuestionDTO>>(
                objectMapper.get());
        OATPP_ASSERT(fillResponse->question != "");
        OATPP_ASSERT(fillResponse->topicName != "");
        OATPP_ASSERT(fillResponse->questionType != "");
        OATPP_ASSERT(fillResponse->errorMessage == "");

        /* Post Tests */

        /**
         * Correct MC POST TEST
         */
        auto correct_mc_response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MC\", \"topic\": \"VersionControl\", "
            "\"answer\": [\"git branch\"]}");
        OATPP_ASSERT(correct_mc_response->getStatusCode() == OK_STATUS_CODE);
        /* Read response body as MessageDto */
        auto correct_mc_message =
            correct_mc_response->readBodyToDto<oatpp::Object<AnswerDTO>>(
                objectMapper.get());
        OATPP_ASSERT(correct_mc_message);
        OATPP_ASSERT(correct_mc_message->answer == true);

        /**
         * Correct MATCH POST TEST
         */
        auto correct_match_response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MATCH\", \"topic\": \"VersionControl\", "
            "\"answer\": [\"log\", \"diff\", \"clone\", \"push\"]}");
        OATPP_ASSERT(correct_match_response->getStatusCode() == OK_STATUS_CODE);
        /* Read response body as MessageDto */
        auto correct_match_message =
            correct_match_response->readBodyToDto<oatpp::Object<AnswerDTO>>(
                objectMapper.get());
        OATPP_ASSERT(correct_match_message);
        OATPP_ASSERT(correct_match_message->answer == true);

        /**
         * Correct TF POST TEST
         */
        auto correct_tf_response = client->postAnswer(
            "{\"id\": 0, \"type\": \"TF\", \"topic\": \"VersionControl\", "
            "\"answer\": [\"true\"]}");
        OATPP_ASSERT(correct_tf_response->getStatusCode() == OK_STATUS_CODE);
        /* Read response body as MessageDto */
        auto correct_tf_message =
            correct_tf_response->readBodyToDto<oatpp::Object<AnswerDTO>>(
                objectMapper.get());
        OATPP_ASSERT(correct_tf_message);
        OATPP_ASSERT(correct_tf_message->answer == true);

        /**
         * Correct FILL POST TEST
         */
        auto correct_fill_response = client->postAnswer(
            "{\"id\": 0, \"type\": \"FILL\", \"topic\": \"VersionControl\", "
            "\"answer\": [\"rebase\", \"branches\"]}");
        OATPP_ASSERT(correct_fill_response->getStatusCode() == OK_STATUS_CODE);
        /* Read response body as MessageDto */
        auto correct_fill_message =
            correct_fill_response->readBodyToDto<oatpp::Object<AnswerDTO>>(
                objectMapper.get());
        OATPP_ASSERT(correct_fill_message);
        OATPP_ASSERT(correct_fill_message->answer == true);

        /**
         * Incorrect MC POST TEST
         */
        auto incorrect_mc_response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MC\", \"topic\": \"VersionControl\", "
            "\"answer\": [\"git switch\"]}");
        OATPP_ASSERT(incorrect_mc_response->getStatusCode() == OK_STATUS_CODE);
        /* Read response body as MessageDto */
        auto incorrect_mc_message =
            incorrect_mc_response->readBodyToDto<oatpp::Object<AnswerDTO>>(
                objectMapper.get());
        OATPP_ASSERT(incorrect_mc_message);
        OATPP_ASSERT(incorrect_mc_message->answer == false);

        /**
         * Incorrect MATCH POST TEST
         */
        auto incorrect_match_response = client->postAnswer(
            "{\"id\": 0, \"type\": \"MATCH\", \"topic\": \"VersionControl\", "
            "\"answer\": [\"log defn\", \"push def\", \"clone deff\", \"diff` "
            "def\"]}");
        OATPP_ASSERT(incorrect_match_response->getStatusCode() ==
                     OK_STATUS_CODE);
        /* Read response body as MessageDto */
        auto incorrect_match_message =
            incorrect_match_response->readBodyToDto<oatpp::Object<AnswerDTO>>(
                objectMapper.get());
        OATPP_ASSERT(incorrect_match_message);
        OATPP_ASSERT(incorrect_match_message->answer == false);

        /**
         * Incorrect TF POST TEST
         */
        auto incorrect_tf_response = client->postAnswer(
            "{\"id\": 0, \"type\": \"TF\", \"topic\": \"VersionControl\", "
            "\"answer\": [\"false\"]}");
        OATPP_ASSERT(incorrect_tf_response->getStatusCode() == OK_STATUS_CODE);
        /* Read response body as MessageDto */
        auto incorrect_tf_message =
            incorrect_tf_response->readBodyToDto<oatpp::Object<AnswerDTO>>(
                objectMapper.get());
        OATPP_ASSERT(incorrect_tf_message);
        OATPP_ASSERT(incorrect_tf_message->answer == false);

        /**
         * Incorrect FILL POST TEST
         */
        auto incorrect_fill_response = client->postAnswer(
            "{\"id\": 0, \"type\": \"FILL\", \"topic\": \"VersionControl\", "
            "\"answer\": [\"not the answer\", \"not the answer\"]}");
        OATPP_ASSERT(incorrect_fill_response->getStatusCode() ==
                     OK_STATUS_CODE);
        /* Read response body as MessageDto */
        auto incorrect_fill_message =
            incorrect_fill_response->readBodyToDto<oatpp::Object<AnswerDTO>>(
                objectMapper.get());
        OATPP_ASSERT(incorrect_fill_message);
        OATPP_ASSERT(incorrect_fill_message->answer == false);

        // OUT OF BOUNDS ID
        auto extra_large_id_response = client->postAnswer(
            "{\"id\": 9000, \"type\": \"MC\", \"topic\": \"VersionControl\", "
            "\"answer\": [\"git branch\"]}");
        OATPP_ASSERT(extra_large_id_response->getStatusCode() == 400);

        // Multiple Choice - Multi-Element Array
        auto bad_multiple_choice_answer = client->postAnswer(
            "{\"id\": 0, \"type\": \"MC\", \"topic\": \"VersionControl\", "
            "\"answer\": [\"git branch\", \"this isn't supposed to be "
            "here\"]}");
        OATPP_ASSERT(bad_multiple_choice_answer->getStatusCode() == 400);
      },
      std::chrono::minutes(TEST_TIMEOUT));
  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
}
