#ifndef JSON_H
#define JSON_H
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <exception>

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
	virtual std::string stringify() { return "null"; }
	virtual ~Value() {}
};

Value* parse(std::string& str);
Value* parse(std::string&, size_t&);


class JSONexception :public std::exception
{
	std::vector < std::pair<size_t, std::string>> info;
public:
	JSONexception() {}
	JSONexception(size_t no, std::string str) {
		info.push_back(std::make_pair(no, str));
	}

	std::string to_string() {
		std::string ret(info.back().first, '~');
		ret += "^\n";
		for (auto record : info)
			ret += std::to_string(record.first) + "\t" + record.second + "\n";
		return ret;
	}
	void push(size_t no, std::string str) {
		info.push_back(std::make_pair(no, str));
	}
};


class Array : public Value {
	std::vector<std::unique_ptr<Value>> elems;
public:
	ValueType type = ValueType::Array;
	virtual std::string stringify()override;

	Array() {}
	Array(std::initializer_list<Value*>);
	Value* push(Value*);
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