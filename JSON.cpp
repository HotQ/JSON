#include "JSON.hpp"


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

Value* Array::push(Value * elem) {
	elems.emplace_back(elem);
	return this;
}

std::string Object::stringify() {
	std::string ret = "{";
	for (auto& pair : dict) {
		ret += pair.first->stringify();
		ret += ":";
		ret += pair.second->stringify();
		ret += ",";
	}
	if (ret.back() == ',') ret.pop_back();
	ret += '}';
	return ret;
}
void Object::insert(class::String * strptr, Value * valptr)
{
	dict.insert(make_pair(std::unique_ptr<class::String>(strptr), std::unique_ptr<Value>(valptr)));
}
Object::Object(std::initializer_list<std::pair<class::String*, Value*>>initlist)
{
	for (auto elem : initlist)
		dict.insert(make_pair(std::unique_ptr<class::String>(elem.first), std::unique_ptr<Value>(elem.second)));
}
