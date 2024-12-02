#ifndef DTOS_HPP
#define DTOS_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class Result : public oatpp::DTO {
  DTO_INIT(Result, DTO /* Extends */)

  DTO_FIELD(String, result);
};

class QuestionDTO : public oatpp::DTO {
  DTO_INIT(QuestionDTO, DTO)
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, topicName);
  DTO_FIELD(String, questionType);
  DTO_FIELD(Int32, id);
  DTO_FIELD(String, question);
  DTO_FIELD(Vector<String>, options);
  DTO_FIELD(String, errorMessage);
};

class ListDTO : public oatpp::DTO {
  DTO_INIT(ListDTO, DTO)
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(Vector<String>, topics);
};

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class AnswerDTO : public oatpp::DTO {
  DTO_INIT(AnswerDTO, DTO)
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(Boolean, answer);
  DTO_FIELD(String, errorMessage);
};

class AnswerBodyDTO : public oatpp::DTO {
  DTO_INIT(AnswerBodyDTO, DTO)
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(Int32, id);
  DTO_FIELD(String, topic);
  DTO_FIELD(String, type);
  DTO_FIELD(Vector<String>, answer);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* SHAPE_DTO_hpp */
