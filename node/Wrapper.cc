#include "Wrapper.h"
#include "NodeBuilder.h"

using namespace v8;

Persistent<Function> Wrapper::constructor;

Wrapper::Wrapper(){
    this->nodeBuilder = new NodeBuilder();
}

Wrapper::~Wrapper() {

}

void Wrapper::Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Wrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "getProblem", GetProblem);
  NODE_SET_PROTOTYPE_METHOD(tpl, "solve", Solve);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "Wrapper"),
               tpl->GetFunction());
}

void Wrapper::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new Wrapper(...)`
    Wrapper* obj = new Wrapper();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `Wrapper(...)`, turn into construct call.
    const int argc = 0;
    Local<Value> argv[argc] = { };
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void Wrapper::Solve(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Wrapper* obj = ObjectWrap::Unwrap<Wrapper>(args.Holder());

  String::Utf8Value param1(args[0]->ToString());
  std::string eq = std::string(*param1);
  obj->nodeBuilder->parse(eq);
  double solution = obj->nodeBuilder->solve();

  Local<Object> newObj = Object::New(isolate);
  newObj->Set(String::NewFromUtf8(isolate, "problem"), args[0]->ToString());
  newObj->Set(String::NewFromUtf8(isolate, "solution"), String::NewFromUtf8(isolate, std::to_string(solution).c_str()));

  args.GetReturnValue().Set(newObj);
}

void Wrapper::GetProblem(const FunctionCallbackInfo<Value> &args){
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Wrapper* obj = ObjectWrap::Unwrap<Wrapper>(args.Holder());

    String::Utf8Value param1(args[3]->ToString());

    int operandCount = args[0]->NumberValue();
    int operandLengthMin = args[1]->NumberValue();
    int operandLengthMax = args[2]->NumberValue();
    std::string operations = std::string(*param1);

    obj->nodeBuilder->generate(operandCount, operandLengthMin, operandLengthMax, operations);
    std::string eq = obj->nodeBuilder->buildEquation();
    double solution = obj->nodeBuilder->solve();

    Local<Object> newObj = Object::New(isolate);
    newObj->Set(String::NewFromUtf8(isolate, "problem"), String::NewFromUtf8(isolate, eq.c_str()));
    newObj->Set(String::NewFromUtf8(isolate, "solution"), String::NewFromUtf8(isolate, std::to_string(solution).c_str()));

    args.GetReturnValue().Set(newObj);
}
