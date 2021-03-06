#include "SdkObject.h"
#include  <iostream>
#include <uv.h>

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Exception;

Persistent<Function> CSdkObject::constructor;
bool g_initLib = false ;

CSdkObject::CSdkObject()
{
     mAge = 1;
     if(!g_initLib){
       boolean b = CLIENT_Init(NULL,NULL);
      // printf("%d",b);
       g_initLib = true;
     }
      mLoginHandle = 0;
     mStreamHandle = 0;
    
    
}


CSdkObject::~CSdkObject()
{

}

void CSdkObject::init(v8::Local<v8::Object> exports){
 Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "CSdkObject"));
  tpl->InstanceTemplate()->SetInternalFieldCount(6);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "getAge", getAge);
 NODE_SET_PROTOTYPE_METHOD(tpl, "setAge", setAge);
 NODE_SET_PROTOTYPE_METHOD(tpl, "login", login);
  NODE_SET_PROTOTYPE_METHOD(tpl, "realStream", realStream);
   NODE_SET_PROTOTYPE_METHOD(tpl, "stopStream", stopStream);
   NODE_SET_PROTOTYPE_METHOD(tpl, "setLogCallback", setLogCallback);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "CSdkObject"),
               tpl->GetFunction());
               
}

void CSdkObject::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    CSdkObject* obj = new CSdkObject();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Context> context = isolate->GetCurrentContext();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Object> result =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(result);
  }
}


void CSdkObject::setLogCallback(const v8::FunctionCallbackInfo<v8::Value>& args){
   Isolate* isolate = args.GetIsolate();
CSdkObject* obj = ObjectWrap::Unwrap<CSdkObject>(args.Holder());

 // Local<Function> cb = Local<Function>::Cast(args[0]);

  Local<Function> callback = Local<Function>::Cast(args[0]);
  obj->mfLogCallback.Reset(isolate, callback);


}

void CSdkObject::setAge(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

Local<Value> age = args[0];
  CSdkObject* obj = ObjectWrap::Unwrap<CSdkObject>(args.Holder());
  obj->mAge = age->ToInteger()->Value();

 // const unsigned argc = 1;
  Local<Value> value =  String::NewFromUtf8(isolate, "setAge") ;
 // Local<Function>::New(isolate, obj->mfLogCallback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);
  obj->outLog(args, value);
  //args.GetReturnValue().Set(Number::New(isolate, obj->value_));
}

void CSdkObject::getAge(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  CSdkObject* obj = ObjectWrap::Unwrap<CSdkObject>(args.Holder());
  int age = obj->mAge;

  args.GetReturnValue().Set(Number::New(isolate, age));

  
}

/*
登录,ip,port,user,pwd
*/
void CSdkObject::login(const v8::FunctionCallbackInfo<v8::Value>& args){
    Isolate* isolate = args.GetIsolate();
     CSdkObject* obj = ObjectWrap::Unwrap<CSdkObject>(args.Holder());

     if (args.Length() < 4) {
    // Throw an Error that is passed back to JavaScript
    obj->outLog(args, String::NewFromUtf8(isolate, "login param too less"));
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));

    return ;
  }

  // Check the argument types
 if (!args[0]->IsString() || !args[1]->IsNumber() || !args[2]->IsString() || !args[3]->IsString()) {
    obj->outLog(args, String::NewFromUtf8(isolate, "login param wrong format"));
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return ;
  }

 //boolean b = CLIENT_Init(NULL,NULL);
 // CLIENT_Cleanup();
 // obj->outLog(args, String::NewFromUtf8(isolate, "CLIENT_Init="));
//   obj->outLog(args, Number::New(isolate, b));

int err=0;
  NET_DEVICEINFO devInfo ;
  memset(&devInfo,0,sizeof(NET_DEVICEINFO));
  obj->mLoginHandle = CLIENT_LoginEx("192.168.6.52",37777, "admin", "admin", 0, NULL, &devInfo, &err );
   

  if(obj->mLoginHandle == 0){
    obj->outLog(args, String::NewFromUtf8(isolate, "login result failure"));
  } else {
     obj->outLog(args, String::NewFromUtf8(isolate, "login result success"));
     int num = devInfo.byChanNum;
     obj->outLog(args, Number::New(isolate, num));
  }
  
  args.GetReturnValue().Set(Number::New(isolate, obj->mLoginHandle));

}


/*
登出
*/
void CSdkObject::logout(const v8::FunctionCallbackInfo<v8::Value>& args){

     Isolate* isolate = args.GetIsolate();
    CSdkObject* obj = ObjectWrap::Unwrap<CSdkObject>(args.Holder());
    CLIENT_Logout(obj->mLoginHandle);
    obj->mLoginHandle = 0;
}

 void CSdkObject::fRealStreamCallBack(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,LONG param, LDWORD dwUser){
      CSdkObject* obj = (CSdkObject*)dwUser;
   // Isolate* isolate = Isolate::GetCurrent();
	obj->mAge = obj->mAge+1;
	std::cout << "age="<<obj->mAge<<";handle="<<obj->mLoginHandle<< std::endl; 
  //  v8::Handle<v8::Value> v = Number::New(v8::Null(), obj->mAge);
  
//	HandleScope scope(isolate);

 //     char log[128] = {0};
  //   sprintf(log,"get stream data, len=%d", dwBufSize);
//std::cout << log<< std::endl; 
 //   CSdkObject* obj = (CSdkObject*)dwUser;

    //std::cout << "a1 age="<< obj->mAge << std::endl; 
 // uv_async_send(&obj->async);
    //Context::GetCurrent()->Global();
  // const unsigned argc = 1;
      // Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world")};
    //  Locker locker(obj->m_pIsolate);
    //  Isolate* curIsolate = Isolate::GetCurrent();

    //  if(obj->m_pIsolate != NULL){
    //     std::cout << "isolate begin:" <<obj->m_pIsolate << std::endl; 
    //     Local<Value> value = String::NewFromUtf8(curIsolate, log);
    //      std::cout << "isolate end" <<obj->m_pIsolate << std::endl; 
    //  }
	  
	   // Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world")};
	   
	  // Local<Function>::New(obj->m_pIsolate, obj->mfLogCallback)->Call(obj->m_pIsolate->GetCurrentContext()->Global(), argc, argv);

    // v8::FunctionCallbackInfo<v8::Value> args =  obj->m_Args;
    // Isolate* isolate = m_Args.GetIsolate();
     // CSdkObject* obj = ObjectWrap::Unwrap<CSdkObject>(pArgs->Holder());


    // char log[128] = {0};
    //  sprintf(log,"get stream data, len=%d", dwBufSize);

  //   obj->outLog(*pArgs, String::NewFromUtf8(isolate, log));
 }


 //void CSdkObject::onCallback(uv_async_t* handle) {
	// /*
	//  const unsigned argc = 1;
	//   Local<Value> argv[argc] = { String::NewFromUtf8(m_pIsolate, "hello world")};
	//   Local<Function>::New(m_pIsolate, mfLogCallback)->Call(m_pIsolate->GetCurrentContext()->Global(), argc, argv);
	//   */
 //}

 //void fStreamCallback(uv_async_t* handle) {
	// std::cout << "out put stream in callback ." << std::endl;
 //}

/*
开始实时流,参数1通道号，参数2数据回调
*/
void CSdkObject::realStream(const v8::FunctionCallbackInfo<v8::Value>& args){

     Isolate* isolate = args.GetIsolate();
     CSdkObject* obj = ObjectWrap::Unwrap<CSdkObject>(args.Holder());

    obj->outLog(args, String::NewFromUtf8(isolate, "realstream start"));

     if(args.Length() < 2){
       obj->outLog(args, String::NewFromUtf8(isolate, "realstream param too less"));
         isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
       return ;
     }

     if(!args[0]->IsNumber()){

        obj->outLog(args, String::NewFromUtf8(isolate, "realstream channel not number"));
        isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
        return ;
     }

   // obj->outLog(args, String::NewFromUtf8(isolate, "realstream start 1"));
     int channel  = args[0]->ToInteger()->Value();

 // obj->outLog(args, String::NewFromUtf8(isolate, "realstream start 2"));


    HWND hWnd = NULL;
     obj->mStreamHandle =  CLIENT_RealPlayEx(obj->mLoginHandle, 0, hWnd, DH_RType_Realplay);
    // obj->mStreamHandle =CLIENT_StartRealPlay(obj->mLoginHandle, 0, hWnd,DH_RType_Realplay ,fRealStreamCallBack,NULL,NULL);
      // obj->outLog(args, String::NewFromUtf8(isolate, "realstream start 3"));
     if(obj->mStreamHandle != 0){ 
       obj->m_pIsolate = isolate;
	//   uv_async_init(uv_default_loop(), &(obj->s_async), fStreamCallback);
       CLIENT_SetRealDataCallBackEx(obj->mStreamHandle,fRealStreamCallBack,(DWORD)&obj,0x00000001);
        obj->outLog(args, String::NewFromUtf8(isolate, "realstream success"));
     } else {
       DWORD dwErr = CLIENT_GetLastError();
      // obj->outLog(args, String::NewFromUtf8(isolate, "realstream start 4"));
      // const unsigned argc = 1;
     
     // Local<Function>::New(isolate, obj->mfLogCallback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

     char log[128] = {0};
     sprintf(log,"get stream error ,login=%d,channel=%d,code=%d", obj->mLoginHandle, channel,dwErr);
      obj->outLog(args, String::NewFromUtf8(isolate, log));
        //obj->outLog(args, Number::New(isolate, dwErr));
      //  obj->outLog(args, String::NewFromNumber(isolate, dwErr));
     }
     
     args.GetReturnValue().Set(Number::New(isolate, obj->mStreamHandle));

     


}

/*
关闭实时流
*/
void CSdkObject::stopStream(const v8::FunctionCallbackInfo<v8::Value>& args){
    Isolate* isolate = args.GetIsolate();
    CSdkObject* obj = ObjectWrap::Unwrap<CSdkObject>(args.Holder());

    CLIENT_StopRealPlay(obj->mStreamHandle);
    obj->mStreamHandle = 0;
}

 
 void CSdkObject::outLog( v8::FunctionCallbackInfo<v8::Value> args, Local<Value> value){
      Isolate* isolate = args.GetIsolate();
     CSdkObject* obj = ObjectWrap::Unwrap<CSdkObject>(args.Holder());

      const unsigned argc = 1;
      // Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world")};
       Local<Value> argv[argc] = {value};
       Local<Function>::New(isolate, obj->mfLogCallback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);
 }


void AsyncTaskBuffer(uv_work_t * work) {
	 CSdkObject* pObject = (CSdkObject*)work->data;
 }

void AfterTaskBuffer(uv_work_t * work, int status) {
	 CSdkObject* pObject = (CSdkObject*)work->data;
	 const int argc = 1;
	 Local<Value> argv[argc] = { String::NewFromUtf8(pObject->m_pIsolate, "completed task buffer")};
	 Local<Function>::New(pObject->m_pIsolate, pObject->mfLogCallback)->Call(pObject->m_pIsolate->GetCurrentContext()->Global(), argc, argv);
 }


 void process(uv_async_t* handle) {

 }
void CSdkObject::startListenStreamThread() {

    uv_loop_t* loop = uv_default_loop();
	uv_async_t async_t;
    uv_work_t req;
	req.data = this;

    uv_async_init(loop, &async_t, process);
    uv_queue_work(loop, &req, AsyncTaskBuffer, AfterTaskBuffer);

}



