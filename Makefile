CXX=g++
CXXFLAGS= -std=c++17 -g -fprofile-arcs -ftest-coverage

OATPP_INCLUDE_LIB = /usr/local/include/oatpp-1.3.0/oatpp
OATPP_INCLUDE = -I src -I $(OATPP_INCLUDE_LIB)

LINKFLAGS_LOCAL = -L /usr/local/lib/oatpp-1.3.0
LINKFLAGS_APP = -loatpp $(LINKFLAGS_LOCAL)
LINKFLAGS_TEST = $(LINKFLAGS_APP) -loatpp-test

SRC_DIR_SERVER = src/server
SRC_DIR_DTO = src/dto
SRC_DIR_MODEL = src/service/Model
SRC_DIR_QUESTION = src/service/Question
SRC_DIR_TOPIC = src/service/TopicController
SRC_DIR_CONTROLLER = src/controller
SRC_DIR_TESTS = src/test
SRC_DIR_TESTS_SELEEP = src/test/Seleep


GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

STATIC_ANALYSIS = cppcheck

STYLE_CHECK = cpplint

PROGRAM_SERVER = seleepServer
TEST_SERVER = testServer

.PHONY: all
all: $(PROGRAM_SERVER) coverage docs static style

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno \
	$(COVERAGE_RESULTS) \
	$(PROGRAM_SERVER) \
	$(COVERAGE_DIR) \
	doxygen/html \
	obj bin \

$(PROGRAM_SERVER): $(SRC_DIR_SERVER) $(SRC_DIR_SERVICE)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_SERVER) $(OATPP_INCLUDE) \
	$(SRC_DIR_SERVER)/*.cpp \
	$(SRC_DIR_DTO)/*.hpp \
	$(SRC_DIR_CONTROLLER)/*.hpp \
	$(SRC_DIR_QUESTION)/*.hpp \
	$(SRC_DIR_QUESTION)/*.cpp \
	$(SRC_DIR_MODEL)/*.hpp \
	$(SRC_DIR_MODEL)/*.cpp \
	$(SRC_DIR_TOPIC)/*.hpp \
	$(SRC_DIR_TOPIC)/*.cpp \
	$(LINKFLAGS_APP)

docker:
	docker build --pull --rm -f "Dockerfile" -t seleep:latest "."

start:
	docker compose -f "compose.yml" up -d --build

stop:
	docker compose -f "compose.yml" down

# $(TEST_SERVER): $(SRC_DIR_TESTS)
# 	$(CXX) $(CXXFLAGS) -o $(TEST_SERVER) $(OATPP_INCLUDE) \
# 	$(SRC_DIR_TESTS_SELEEP)/*.cpp \
# 	$(SRC_DIR_TESTS_SELEEP)/*.hpp \
# 	$(SRC_DIR_DTO)/*.hpp \
# 	$(SRC_DIR_CONTROLLER)/*.hpp \
# 	$(SRC_DIR_QUESTION)/*.hpp \
# 	$(SRC_DIR_QUESTION)/*.cpp \
# 	$(SRC_DIR_MODEL)/*.hpp \
# 	$(SRC_DIR_MODEL)/*.cpp \
# 	$(SRC_DIR_TOPIC)/*.hpp \
# 	$(SRC_DIR_TOPIC)/*.cpp \
# 	$(SRC_DIR_TESTS)/*.cpp $(LINKFLAGS_TEST)

static: ${SRC_DIR_SERVER} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVICE} ${TEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR_SERVER} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVICE} ${TEST_DIR} ${SRC_INCLUDE} --suppress=missingInclude

style: ${SRC_DIR_SERVICE} ${SRC_INCLUDE}
	${STYLE_CHECK} src/controller/* src/dto/* src/server/* src/service/*/* src/test/*/* src/test/*.cpp
