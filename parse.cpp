#include "JSON.hpp"
//Value* parse_root(std::string& str, size_t crt);
Value* parse_true(std::string& str, size_t& crt);
Value* parse_false(std::string& str, size_t& crt);
Value* parse_null(std::string& str, size_t& crt);
Value* parse_number(std::string& str, size_t& crt);
Value* parse_string(std::string& str, size_t& crt);
Value* parse_object(std::string& str, size_t& crt);
Value* parse_array(std::string& str, size_t& crt);

#define ISDIGIT(ch) ((ch)>='0' && (ch)<='9')

#include <iostream>

static void ign_white(std::string& str, size_t& crt) {
	while (crt < str.size()) {
		if (str[crt] == ' ' || str[crt] == '\t' || str[crt] == '\r' || str[crt] == '\n' || str[crt] == '\v') ++crt;
		else break;
	}
}
Value* parse(std::string & str) {
	size_t crt = 0;
	Value* ret = parse(str, crt);
	ign_white(str, crt);
	//std::cout << "crt " << crt << std::endl;
	if (crt != str.size()) {
		delete ret;
		throw JSONexception(crt, "EXTRA NONE-WHITESPACE-CHAR");
	}
	return ret;
}
Value* parse(std::string & str, size_t & crt) {
	ign_white(str, crt);
	if (str.size() <= crt)
		return nullptr;
	switch (str[crt])
	{
	case 't': return parse_true(str, crt);
	case 'f': return parse_false(str, crt);
	case 'n': return parse_null(str, crt);
	case '"': return parse_string(str, crt);
	case '{': return parse_object(str, crt);
	case '[': return parse_array(str, crt);
	default:
		if (str[crt] == '-' || ISDIGIT(str[crt])) {
			return parse_number(str, crt);
		}
		else {
			throw JSONexception(crt, "CAN'T FIGURE OUT WHAT TYPE THIS JSON IS!");
		}
	}

}
Value* parse_true(std::string & str, size_t & crt) {
	if (str.size() >= crt + 4 && str[++crt] == 'r' && str[++crt] == 'u' && str[++crt] == 'e') {
		++crt;
		return new class::Boolean(true);
	}
	else throw JSONexception(crt, "SHOULD BE \"true\"");
}
Value* parse_false(std::string & str, size_t & crt) {
	if (str.size() >= crt + 5 && str[++crt] == 'a' && str[++crt] == 'l' && str[++crt] == 's' && str[++crt] == 'e') {
		++crt;
		return new class::Boolean(false);
	}
	else throw JSONexception(crt, "SHOULD BE \"false\"");
}
Value* parse_null(std::string & str, size_t & crt) {
	if (str.size() >= crt + 4 && str[++crt] == 'u' && str[++crt] == 'l' && str[++crt] == 'l') {
		++crt;
		return new class::Null();
	}
	else throw JSONexception(crt, "SHOULD BE \"null\"");
}

/////////////////////////////////////////////////////

Value* parse_number(std::string & str, size_t & crt) {
	throw JSONexception(crt, "parse_number() NOT IMPLEMENTED YET");
	return nullptr;
}
Value* parse_string(std::string & str, size_t & crt) {
	throw JSONexception(crt, "parse_string() NOT IMPLEMENTED YET");
	return nullptr;
}
Value* parse_object(std::string & str, size_t & crt) {
	throw JSONexception(crt, "parse_object() NOT IMPLEMENTED YET");
	return nullptr;
}
Value* parse_array(std::string & str, size_t & crt) {
	throw JSONexception(crt, "parse_array() NOT IMPLEMENTED YET");
	return nullptr;
}