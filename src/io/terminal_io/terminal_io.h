#ifndef _TERMINAL_IO_H
#define _TERMINAL_IO_H

#include "util/queue_ts.hpp"
#include "common/command_object.h"
#include <memory>
#include <string>
#include <thread>

class TerminalIo {
  bool b_run_;
  std::shared_ptr< QueueTs<CommandObject> > p_command_queue_;
  std::thread get_input_th_;

  void Run();
  bool GetInput(std::string & str_line);
 public:
  TerminalIo(std::shared_ptr< QueueTs<CommandObject> > p_command_queue);
  ~TerminalIo(); 
};

#endif //_TERMINAL_IO_H
