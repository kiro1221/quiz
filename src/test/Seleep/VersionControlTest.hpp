/**
 * @author James Huston | huston@uleth.ca
 * @date 25/11/2024
 */

#ifndef VERSION_CONTROL_TEST
#define VERSION_CONTROL_TEST


#include "oatpp-test/UnitTest.hpp"

class VersionControlTest : public oatpp::test::UnitTest {
 public:
  VersionControlTest() : UnitTest("TEST[VersionControlTestSeleep]") {}
  void onRun() override;
};

#endif  /* VERSION_CONTROL_TEST */
