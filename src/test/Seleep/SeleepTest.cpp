#include "SeleepTest.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <vector>



#include "../../controller/SeleepController.hpp"
#include "../app/MyApiTestClient.hpp"
#include "../app/TestComponent.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

void SeleepTest::onRun() {
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

        auto response = client->getTopics();
        OATPP_ASSERT(response->getStatusCode() == 200);
        auto qResponse =
            response->readBodyToDto<oatpp::Object<ListDTO>>(objectMapper.get());
        std::vector<std::string> listArr;
        for (const auto &item : *qResponse->topics) {
          listArr.push_back(item->c_str());  // Convert to std::string
        }
        OATPP_ASSERT(listArr.size() != 0);

        response = client->getRand();
        OATPP_ASSERT(response->getStatusCode() == 200);

        response = client->getDesignPatternsRand();
        OATPP_ASSERT(response->getStatusCode() == 200);
        response = client->getVersionControlRand();
        OATPP_ASSERT(response->getStatusCode() == 200);
        response = client->getSolidRand();
        OATPP_ASSERT(response->getStatusCode() == 200);
        response = client->getTestingRand();
        OATPP_ASSERT(response->getStatusCode() == 200);
        response = client->getDoxygenRand();
        OATPP_ASSERT(response->getStatusCode() == 200);
      },
      std::chrono::minutes(10) /* test timeout */);
  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
