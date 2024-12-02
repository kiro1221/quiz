
#ifndef MyApiTestClient_hpp
#define MyApiTestClient_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/web/client/ApiClient.hpp"

/* Begin Api Client code generation */
#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API client.
 * Use this client to call application APIs.
 */
class MyApiTestClient : public oatpp::web::client::ApiClient {
  API_CLIENT_INIT(MyApiTestClient)
  API_CALL("GET", "/seleep", getTopics)

  API_CALL("GET", "/seleep/questions?topic=Random&type=Random", getRand)

  API_CALL("GET", "/seleep/questions?topic=DesignPatterns&type=Random",
           getDesignPatternsRand)
  API_CALL("GET", "/seleep/questions?topic=VersionControl&type=Random",
           getVersionControlRand)
  API_CALL("GET", "/seleep/questions?topic=Solid&type=Random", getSolidRand)
  API_CALL("GET", "/seleep/questions?topic=Testing&type=Random", getTestingRand)
  API_CALL("GET", "/seleep/questions?topic=Doxygen&type=Random", getDoxygenRand)

  API_CALL("GET", "/seleep/questions?topic=DesignPatterns&type=MC",
           getDesignPatternsMC)
  API_CALL("GET", "/seleep/questions?topic=DesignPatterns&type=TF",
           getDesignPatternsTF)
  API_CALL("GET", "/seleep/questions?topic=DesignPatterns&type=FILL",
           getDesignPatternsFILL)
  API_CALL("GET", "/seleep/questions?topic=DesignPatterns&type=MATCH",
           getDesignPatternsMATCH)

  API_CALL("GET", "/seleep/questions?topic=Solid&type=MC", getSolidMC)
  API_CALL("GET", "/seleep/questions?topic=Solid&type=TF", getSolidTF)
  API_CALL("GET", "/seleep/questions?topic=Solid&type=FILL", getSolidFILL)
  API_CALL("GET", "/seleep/questions?topic=Solid&type=MATCH", getSolidMATCH)

  API_CALL("GET", "/seleep/questions?topic=Testing&type=MC", getTestingMC)
  API_CALL("GET", "/seleep/questions?topic=Testing&type=TF", getTestingTF)
  API_CALL("GET", "/seleep/questions?topic=Testing&type=FILL", getTestingFILL)
  API_CALL("GET", "/seleep/questions?topic=Testing&type=MATCH", getTestingMATCH)

  API_CALL("GET", "/seleep/questions?topic=Doxygen&type=MC", getDoxygenMC)
  API_CALL("GET", "/seleep/questions?topic=Doxygen&type=TF", getDoxygenTF)
  API_CALL("GET", "/seleep/questions?topic=Doxygen&type=FILL", getDoxygenFILL)
  API_CALL("GET", "/seleep/questions?topic=Doxygen&type=MATCH", getDoxygenMATCH)

  API_CALL("GET", "/seleep/questions?topic=VersionControl&type=MC",
           getVersionControlMC)
  API_CALL("GET", "/seleep/questions?topic=VersionControl&type=TF",
           getVersionControlTF)
  API_CALL("GET", "/seleep/questions?topic=VersionControl&type=FILL",
           getVersionControlFILL)
  API_CALL("GET", "/seleep/questions?topic=VersionControl&type=MATCH",
           getVersionControlMATCH)

  API_CALL("POST", "/seleep/answer", postAnswer, BODY_STRING(String, body))
};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif  // MyApiTestClient_hpp
