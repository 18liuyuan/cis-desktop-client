#pragma once

#include <node.h>
#include <node_object_wrap.h>
#include "inc/dhnetsdk.h"
//#include <uv.h>

using namespace node;
using namespace v8;

class CSdkObject : public node::ObjectWrap
{
public:
	CSdkObject();
	~CSdkObject();

private:
    int mAge;

public:
    //void setAge(int);
    //int getAge();
public:
    static void init(v8::Local<v8::Object> exports);
    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static v8::Persistent<v8::Function> constructor;

    static void setLogCallback(const v8::FunctionCallbackInfo<v8::Value>& args);

    static void setAge(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void getAge(const v8::FunctionCallbackInfo<v8::Value>& args);

    static void login(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void logout(const v8::FunctionCallbackInfo<v8::Value>& args);

    static void realStream(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void stopStream(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
    long mLoginHandle;
    long mStreamHandle;
   
public:
   Isolate* m_pIsolate;
   v8::Persistent<v8::Context> m_CallbackContext;
  // uv_async_t s_async = { 0 };
   Persistent<Function> mfLogCallback;
private:
    void outLog(v8::FunctionCallbackInfo<v8::Value> args, Local<Value> value);
private:
    static void __stdcall fRealStreamCallBack(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,LONG param, LDWORD dwUser);
public:
//	static void __stdcall onCallback(uv_async_t* handle);

	void startListenStreamThread();
	//void AsyncTaskBuffer(uv_work_t * work);
	//void AfterTaskBuffer(uv_work_t * work, int status);
};

