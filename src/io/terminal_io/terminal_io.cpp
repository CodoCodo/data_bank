#include "terminal_io.h"
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

TerminalIo::TerminalIo(std::shared_ptr< QueueTs<CommandObject> > p_command_queue)
  : b_run_(true),
    p_command_queue_(p_command_queue),
    get_input_th_(&TerminalIo::Run, this) {
}

TerminalIo::~TerminalIo() {
  b_run_ = false;
  get_input_th_.join();
}

bool TerminalIo::GetInput(std::string & str_line) {
  fd_set rfds;
  struct timeval tv;
  int retval = 0;
  bool input_ok = false;

  FD_ZERO(&rfds);
  FD_SET(0, &rfds);

  tv.tv_sec = 0;
  tv.tv_usec = 20000;

  retval = select(1, &rfds, NULL, NULL, &tv);
  if (retval > 0) {
    // 命令行直接输入
    std::getline(std::cin, str_line);
    input_ok = true;
  }
  return input_ok;
}

void TerminalIo::Run() {
  CommandObject cmd_obj;
  std::string cmd_line;
  while (b_run_) {
    if (GetInput(cmd_line)) {
      cmd_obj.Parse(cmd_line);
      p_command_queue_->Push(cmd_obj);
    }
  }
}