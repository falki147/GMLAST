/**
 * \file Error.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>

namespace GMLAST {

/**
 * \brief Node which is a stub. It is inserted if the parser fails to construct
 * an AST.
 *
 * I.e. instead of creating a node with a null pointer it uses an error
 * instance.
 */
class Error : public Value {
 public:
  /**
   * \brief Function which calls IVisitor::onError
   */
  virtual void visit(IVisitor& visitor) const override;
};

}  // namespace GMLAST
