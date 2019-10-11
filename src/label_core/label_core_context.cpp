#include "label_core_context.h"

LabelCoreContext::LabelCoreContext()
  : state_(IDLE),
    media_index_(0),
    p_media_access_(MediaAccess::Create()),
    b_run_(true),
    default_background_(480, 480, CV_8UC3) {
}