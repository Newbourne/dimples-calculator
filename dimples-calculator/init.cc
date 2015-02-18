#include <node.h>
#include "Wrapper.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  Wrapper::Init(exports);
}

NODE_MODULE(addon, InitAll)


