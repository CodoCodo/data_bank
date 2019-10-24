#ifndef _LABEL_CORE_VIEW_H
#define _LABEL_CORE_VIEW_H

#include <memory>
#include "label_core/label_core_context.h"
#include "label_core/label_core.h"

class LabelCoreView {
 public:
  virtual ~LabelCoreView() = default;
  virtual void Run() = 0;

  static std::shared_ptr<LabelCoreView> Create(std::shared_ptr<LabelCoreContext> p_context,
                                               std::shared_ptr<LabelCoreCommandParser> p_command_parser,
                                               std::shared_ptr<LabelCore> p_core);
};

#endif //_LABEL_CORE_VIEW_H
