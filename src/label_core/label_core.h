#ifndef _LABEL_CORE_H
#define _LABEL_CORE_H

#include <memory>
#include "util/queue_ts.hpp"
#include "label_core_context.h"
#include "label_core_command.h"
#include "label_core_command_parser.h"

class LabelCore {
 public:
  virtual void RunOnce() = 0;
  static std::shared_ptr<LabelCore> Create(std::shared_ptr< QueueTs<LabelCoreCommand> > p_cmd_queue);
};

#endif //_LABEL_CORE_H
