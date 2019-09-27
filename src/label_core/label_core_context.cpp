#include "label_core_context.h"

LabelCoreContext::LabelCoreContext()
  : b_run_(true),
    output_img_(720, 1280, CV_8UC3) {
}