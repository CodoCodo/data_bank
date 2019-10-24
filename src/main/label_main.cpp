//标注程序主函数

#include <iostream>
#include <string>
#include <memory>
#include "label_core/label_core_context.h"
#include "label_core/label_core.h"
#include "label_core/label_core_command_parser.h"

#include "view/label_core_view.h"

int LabelMain(int argc, char *argv[]) {
  std::shared_ptr<LabelCoreContext> p_context(new LabelCoreContext);
  std::shared_ptr<LabelCoreCommandParser> p_command_parser(new LabelCoreCommandParser);
  std::shared_ptr<LabelCore> p_core(new LabelCore(p_context, p_command_parser));
  std::shared_ptr<LabelCoreView> p_label_core_view = LabelCoreView::Create(p_context, p_command_parser, p_core);

  p_label_core_view->Run();

  return 0;
}

int main(int argc, char *argv[]) {
  return LabelMain(argc, argv);
}
