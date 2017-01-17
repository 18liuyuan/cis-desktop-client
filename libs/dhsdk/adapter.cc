#include <node.h>
#include "SdkObject.h"
namespace demo {

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Integer;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  // Isolate* isolate = args.GetIsolate();
  // args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));

  Isolate* isolate = args.GetIsolate();
  Local<Function> cb = Local<Function>::Cast(args[0]);
  const unsigned argc = 1;
  Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "I am come from sdk.cc.") };
  cb->Call(Null(isolate), argc, argv);

}

void NewPlayer(const FunctionCallbackInfo<Value>& args){

  Isolate* isolate = args.GetIsolate();
  //CSdkObject*  pObject = new CSdkObject();
  
  //int age = pObject->getAge();
 // args.GetReturnValue().Set(Integer::New(isolate, age));
}

void DeletePlayer(const FunctionCallbackInfo<Value>& args){
 long ret = 102;
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(Number::New(isolate, ret));

}



void init(Local<Object> exports) {
  // NODE_SET_METHOD(exports, "hello", Method);
  // NODE_SET_METHOD(exports, "newPlayer", NewPlayer);
  // NODE_SET_METHOD(exports, "deletePlayer", DeletePlayer);
  CSdkObject::init(exports);
}

NODE_MODULE(dhsdk, init)

}  // namespace demo