// familyTree.cc
#include "familyTree.hpp"
#include "familyTree.cpp"
#include <iostream>
#include <string>
#include <node.h>
#include <v8.h>

familyTree root;
using std::cout;
using std::string;

namespace demo {

using v8::Boolean;
using v8::FunctionCallbackInfo;
using v8::Integer;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void CreateObject(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();
    Local<Object> obj = Object::New(isolate);

    int option = args[0]->Int32Value();
    switch (option) {
    case 0/*parent*/: {
        if (args.Length() != 7)
            break;

        String::Utf8Value firstName_0(args[1]);
        String::Utf8Value lastName_0(args[2]);
        String::Utf8Value birthDay_0(args[3]);
        String::Utf8Value deadDay_0(args[4]);
        Local<Boolean> isMale_0 = Local<Boolean>::Cast(args[5]);
        int id_0 = args[6]->Int32Value();
        Detail detail(*firstName_0, *lastName_0, *birthDay_0, *deadDay_0, args[5]->BooleanValue());
        
        toReturn temp = root.addToParent(detail, id_0);
        Local<String> str = v8::String::NewFromUtf8(isolate, temp.data.c_str());
        Local<Boolean> flag = v8::Boolean::New(isolate, temp.isError);
        obj->Set(String::NewFromUtf8(isolate, "isError"), flag);
        obj->Set(String::NewFromUtf8(isolate, "data"), str);
        break;
    } case 1/*couple*/: {
        if (args.Length() != 7)
            break;

        String::Utf8Value firstName_1(args[1]);
        String::Utf8Value lastName_1(args[2]);
        String::Utf8Value birthDay_1(args[3]);
        String::Utf8Value deadDay_1(args[4]);
        Local<Boolean> isMale_1 = Local<Boolean>::Cast(args[5]);
        int id_1 = args[6]->Int32Value();
        Detail detail(*firstName_1, *lastName_1, *birthDay_1, *deadDay_1, args[5]->BooleanValue());

        toReturn temp = root.addToCouple(detail, id_1);
        Local<String> str = v8::String::NewFromUtf8(isolate, temp.data.c_str());
        Local<Boolean> flag = v8::Boolean::New(isolate, temp.isError);
        obj->Set(String::NewFromUtf8(isolate, "isError"), flag);
        obj->Set(String::NewFromUtf8(isolate, "data"), str);
        break;
    } case 2/*subling*/: {
        if (args.Length() != 7)
            break;

        String::Utf8Value firstName_2(args[1]);
        String::Utf8Value lastName_2(args[2]);
        String::Utf8Value birthDay_2(args[3]);
        String::Utf8Value deadDay_2(args[4]);
        Local<Boolean> isMale_2 = Local<Boolean>::Cast(args[5]);
        int id_2 = args[6]->Int32Value();
        Detail detail(*firstName_2, *lastName_2, *birthDay_2, *deadDay_2, args[5]->BooleanValue());

        toReturn temp = root.addToSublings(detail, id_2);
        Local<String> str = v8::String::NewFromUtf8(isolate, temp.data.c_str());
        Local<Boolean> flag = v8::Boolean::New(isolate, temp.isError);
        obj->Set(String::NewFromUtf8(isolate, "isError"), flag);
        obj->Set(String::NewFromUtf8(isolate, "data"), str);
        break;
    } case 3/* children */: {
        if (args.Length() != 7)
            break;

        String::Utf8Value firstName_3(args[1]);
        String::Utf8Value lastName_3(args[2]);
        String::Utf8Value birthDay_3(args[3]);
        String::Utf8Value deadDay_3(args[4]);
        Local<Boolean> isMale_3 = Local<Boolean>::Cast(args[5]);
        int id_3 = args[6]->Int32Value();
        Detail detail(*firstName_3, *lastName_3, *birthDay_3, *deadDay_3, args[5]->BooleanValue());

        toReturn temp = root.addToChildren(detail, id_3);
        Local<String> str = v8::String::NewFromUtf8(isolate, temp.data.c_str());
        Local<Boolean> flag = v8::Boolean::New(isolate, temp.isError);
        obj->Set(String::NewFromUtf8(isolate, "isError"), flag);
        obj->Set(String::NewFromUtf8(isolate, "data"), str);
        break;
    } case 4/* get */: {
        if (args.Length() != 2)
            break;

        unsigned int id_4 = args[1]->Uint32Value();

        Node temp_4 = root.getNode(id_4);

        Local<String> firstName_4 = v8::String::NewFromUtf8(isolate, temp_4.detail.firstName.c_str());
        Local<String> lastName_4 = v8::String::NewFromUtf8(isolate, temp_4.detail.lastName.c_str());
        Local<String> birthDay_4 = v8::String::NewFromUtf8(isolate, temp_4.detail.birthDay.c_str());
        Local<String> deadDay_4 = v8::String::NewFromUtf8(isolate, temp_4.detail.deadDay.c_str());
        Local<Boolean> isMale_4 = v8::Boolean::New(isolate, temp_4.detail.isMale);

        obj->Set(String::NewFromUtf8(isolate, "firstName"), firstName_4);
        obj->Set(String::NewFromUtf8(isolate, "lastName"), lastName_4);
        obj->Set(String::NewFromUtf8(isolate, "birthDay"), birthDay_4);
        obj->Set(String::NewFromUtf8(isolate, "deadDay"), deadDay_4);
        obj->Set(String::NewFromUtf8(isolate, "isMale"), isMale_4);
        break;
    } case 5/* rm */: {
        if (args.Length() != 2)
            break;

        unsigned int id_5 = args[1]->Uint32Value();
        toReturn temp_5 = root.deleteSubTree(id_5);
        Local<String> str_5 = v8::String::NewFromUtf8(isolate, temp_5.data.c_str());
        Local<Boolean> flag_5 = v8::Boolean::New(isolate, temp_5.isError);
        obj->Set(String::NewFromUtf8(isolate, "isError"), flag_5);
        obj->Set(String::NewFromUtf8(isolate, "data"), str_5);
        break;
    } case 6/* refresh */: {
        cout << "w";
        Local<String> str_6 = v8::String::NewFromUtf8(isolate, root.printTree().c_str());
        obj->Set(String::NewFromUtf8(isolate, "data"), str_6);
    } case 7/* set */: {
        if (args.Length() != 7)
            break;
        
        int id_7 = args[6]->Int32Value();
        Node& temp_7 = root.getNode(id_7);

        
        String::Utf8Value firstName_7(args[1]);
        String::Utf8Value lastName_7(args[2]);
        String::Utf8Value birthDay_7(args[3]);
        String::Utf8Value deadDay_7(args[4]);
        
        Detail detail(*firstName_7, *lastName_7, *birthDay_7, *deadDay_7, args[5]->BooleanValue());
        temp_7.detail = detail;
        
        Local<String> str_7 = v8::String::NewFromUtf8(isolate, root.printTree().c_str());
        obj->Set(String::NewFromUtf8(isolate, "data"), str_7);
    } 
    
    default:
        break;
    }

    args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports, Local<Object> module) {
    NODE_SET_METHOD(module, "exports", CreateObject);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

} // namespace demo