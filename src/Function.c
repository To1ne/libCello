#include "Cello/Function.h"

#include "Cello/List.h"

var call_with_ptr(var self, var* args) {
  
  var wrapped = new(List, 0);
  
  while((*args) != (var)-1) {
    push(wrapped, *args);
    args++;
  }
  
  var res = call_with(self, wrapped);
  
  delete(wrapped);
  
  return res;
}

var call_with(var self, var args) {
  return type_class_method(type_of(self), Call, call_with, self, args);
}

var Function = methods {
  methods_begin(Function),
  method(Function, New),
  method(Function, Copy),
  method(Function, Assign),
  method(Function, Call),
  methods_end(Function),
};

var Function_New(var self, va_list* args) {
  FunctionData* fd = cast(self, Function);
  fd->func = va_arg(*args, var);
  return self;
}

var Function_Delete(var self) {
  return self;
}

size_t Function_Size(void) {
  return sizeof(FunctionData);
}

var Function_Copy(var self) {
  FunctionData* fd = cast(self, Function);
  return new(Function, fd->func);
}

void Function_Assign(var self, var obj) {
  FunctionData* fd = cast(self, Function);
  FunctionData* other = cast(obj, Function);
  fd->func = other->func;
}

var Function_Call(var self, var args) {
  FunctionData* fd = cast(self, Function);
  return fd->func(args);
}
