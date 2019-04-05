#ifndef JSON_H
#define JSON_H
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

enum ValueType {
	Array,
	Object,
	Number,
	String,
	Boolean,
	Null,
	Uncertain
};

class Value {
public:
	ValueType type = Uncertain;
	virtual std::string stringify() { return "null"; };
	virtual ~Value() {}
};

class Array : public Value {
	std::vector<std::unique_ptr<Value>> elems;
public:
	ValueType type = ValueType::Array;
	virtual std::string stringify()override;

	Array(std::initializer_list<Value*>);
};

class String : public Value {
	std::string str;
public:
	ValueType type = ValueType::Array;
	virtual std::string stringify()override { return "\"" + str + "\""; };

	String(std::string _str) :str(_str) {}
};

class Object : public Value {
	std::unordered_map<std::string, std::unique_ptr<Value>> dict;
public:
	ValueType type = ValueType::Object;
	virtual std::string stringify()override;
	std::unique_ptr<Value>& operator[](std::string);

	Object(std::initializer_list<std::pair<std::string, Value*>>);
};

class Boolean : public Value {
	bool bol;
public:
	ValueType type = ValueType::Boolean;
	virtual std::string stringify()override { return bol ? "true" : "false"; };

	Boolean(bool bol) :bol(bol) {}
};

class Null : public Value {
public:
	ValueType type = ValueType::Boolean;
	virtual std::string stringify()override { return "null"; };

};
class Number : public Value {
	double num;
public:
	ValueType type = ValueType::Number;
	virtual std::string stringify()override { return std::to_string(num); };
	Number(double num) :num(num) {}
};

#endif // JSON_H