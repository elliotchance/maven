#include "/Users/elliot/Xcode/maven/maven/build/src/mavencore/mavencore.h"
#include "/Users/elliot/Xcode/maven/maven/build/Debug/examples/Chapter_6_Objects_and_Classes/.mmap"
namespace global {

} namespace maven{
 maven::ClassVariable* ClassVariable::copy(){
maven::ClassVariable* r = new maven::ClassVariable();
r->isPublic = this->isPublic;
return r;
}
} namespace maven{
 maven::Application* Application::copy(){
maven::Application* r = new maven::Application();
return r;
}
} namespace maven{
 maven::Exception* Exception::copy(){
maven::Exception* r = new maven::Exception();
r->line = this->line;
r->errorCode = this->errorCode;
return r;
}
} namespace maven{
 maven::BoundsException* BoundsException::copy(){
maven::BoundsException* r = new maven::BoundsException();
r->line = this->line;
r->errorCode = this->errorCode;
return r;
}
} namespace maven{
 maven::Date* Date::copy(){
maven::Date* r = new maven::Date();
r->year = this->year;
r->month = this->month;
r->day = this->day;
r->hour = this->hour;
r->minute = this->minute;
r->second = this->second;
return r;
}
} namespace maven{
 maven::Calendar* Calendar::copy(){
maven::Calendar* r = new maven::Calendar();
return r;
}
} namespace maven{
 maven::Data* Data::copy(){
maven::Data* r = new maven::Data();
r->size = this->size;
r->allocatedSize = this->allocatedSize;
r->position = this->position;
return r;
}
} namespace maven{
 maven::Debug* Debug::copy(){
maven::Debug* r = new maven::Debug();
return r;
}
} namespace maven{
 maven::Dictionary* Dictionary::copy(){
maven::Dictionary* r = new maven::Dictionary();
return r;
}
} namespace maven{
 maven::Integer* Integer::copy(){
maven::Integer* r = new maven::Integer();
r->value = this->value;
return r;
}
} namespace maven{
 maven::Math* Math::copy(){
maven::Math* r = new maven::Math();
return r;
}
} namespace maven{
 maven::ObjectNilException* ObjectNilException::copy(){
maven::ObjectNilException* r = new maven::ObjectNilException();
r->line = this->line;
r->errorCode = this->errorCode;
return r;
}
} namespace maven{
 maven::Quad* Quad::copy(){
maven::Quad* r = new maven::Quad();
r->value = this->value;
return r;
}
} namespace maven{
 maven::SelectorException* SelectorException::copy(){
maven::SelectorException* r = new maven::SelectorException();
r->line = this->line;
r->errorCode = this->errorCode;
return r;
}
} namespace maven{
 maven::Thread* Thread::copy(){
maven::Thread* r = new maven::Thread();
return r;
}
} namespace maven{

} namespace maven{
 ClassVariable::ClassVariable(boolean _isPublic, maven::String* _name, maven::String* _type){
super("maven.ClassVariable");
  isPublic =  _isPublic ;
  name =  _name ;
  type =  _type ;
}
} namespace maven{

} namespace global{

} namespace maven{

} namespace global{

} namespace maven{

} namespace global{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{

} namespace maven{
 SelectorException::SelectorException(){
super("maven.SelectorException");
}
} namespace maven{

}

int main(int argc, char** argv) {
maven::initMaven();
try {
maven::Math$static::PI =   (quad)3.14159265358979323846 ;
maven::Math$static::E =   (quad)2.71828182845904523536 ;
} catch(maven::Exception* caughtGlobalException) { std::cout << caughtGlobalException->description()->s; }
}

