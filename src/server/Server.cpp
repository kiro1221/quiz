#include <memory>
#include "oatpp/network/Server.hpp"
#include "../controller/SeleepController.hpp"
#include "ServerComponents.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

void run() {
  ServerComponent components;

  /* Create Router for HTTP requests routing */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  /* Create SeleepController and add all of its endpoints to router */
  auto controller = std::make_shared<SeleepController>();
  router->addController(controller);

  /* Create HTTP connection handler with router */
  auto connectionHandler =
      oatpp::web::server::HttpConnectionHandler::createShared(router);

  /* Create TCP connection provider */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>,
                  connectionProvider);

  /* Create server which takes provided TCP connections and passes them to HTTP
   * connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print info about server port */
  OATPP_LOGI("Seleep Service", "Server running on port %d",
             connectionProvider->getProperty("port").getData());

  /* Run server */
  server.run();
}

int main() {
  /* Init oatpp Environment */
  oatpp::base::Environment::init();

  /* Run App */
  run();

  /* Destroy oatpp Environment */
  oatpp::base::Environment::destroy();

  return 0;
}
