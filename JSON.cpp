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
