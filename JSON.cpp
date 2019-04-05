#include "JSON.hpp"
#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#endif // _WIN32

#include <iostream>

std::string Array::stringify() {
	std::string ret("[");
	for (auto& elem : elems) {
		ret += (elem)->stringify();
		ret += ',';
	}
	if (ret.back() == ',') ret.pop_back();
	ret += "]";
	return ret;
}
Array::Array(std::initializer_list<Value*> initlist) {
	for (Value* elem : initlist)
		elems.emplace_back(elem);
}

std::string Object::stringify(){
	std::string ret = "{";
	for (auto& pair : dict) {
		ret += '"';
		ret += pair.first;
		ret += "\":";
		ret += (pair.second)->stringify();
		ret += ",";
	}
	if (ret.back() == ',') ret.pop_back();
	ret += '}';
	return ret;
}
std::unique_ptr<Value>& Object::operator[](std::string str) {
	dict.insert(make_pair(str, std::unique_ptr<Value>()));
	return dict[str];
}
Object::Object(std::initializer_list<std::pair<std::string, Value*>> initlist) {
	for (auto elem : initlist)
		dict[elem.first] = std::unique_ptr<Value>(elem.second);
}


int main()
{
	using namespace std;

	Value* str1 = new class::String("SDFG"),
		* str2 = new class::String("lhlkj"),
		* arr1 = new class::Array({ str1, str2 }),
		* arr2 = new class::Array({ arr1,new class::Boolean(false), new class::Null() }),
		* obj1 = new class::Object({ make_pair(string("arr2"),arr2) , make_pair("NULL",new class::Null())  , make_pair("Number",new class::Number(-4e3)) });
	(*static_cast<class::Object*>(obj1))[string("String")] = unique_ptr<Value>( new class::String("asdfrweg"));
	cout << "================================\n\n\n"
		<< obj1->stringify() << endl
		<< "\n\n\n================================";

	delete obj1;

	#ifdef _WIN32
	_CrtDumpMemoryLeaks();
	#endif // _WIN32
}
