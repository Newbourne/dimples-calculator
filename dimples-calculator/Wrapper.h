#ifndef WRAPPER
#define WRAPPER

#include <node.h>
#include <node_object_wrap.h>
#include "NodeBuilder.h"

using namespace v8;

class Wrapper : public node::ObjectWrap {
 public:
  static void Init(Handle<Object> exports);

 private:
  explicit Wrapper();
  ~Wrapper();

  NodeBuilder* nodeBuilder;
  static Persistent<Function> constructor;
  static void New(const FunctionCallbackInfo<Value>& args);
  static void GetProblem(const FunctionCallbackInfo<Value>& args);
  static void Solve(const FunctionCallbackInfo<Value>& args);
};

#endif // WRAPPER
