#include "JSON.hpp"
#include <sstream>

Value* parse_true(std::string& str, size_t& crt);
Value* parse_false(std::string& str, size_t& crt);
Value* parse_null(std::string& str, size_t& crt);
Value* parse_number(std::string& str, size_t& crt);
Value* parse_string(std::string& str, size_t& crt);
Value* parse_object(std::string& str, size_t& crt);
Value* parse_array(std::string& str, size_t& crt);

#define ISDIGIT(ch) ((ch)>='0' && (ch)<='9')
#define ISD1TO9(ch) ((ch)>='1' && (ch)<='9')



static void eat_white(std::string& str, size_t& crt) {
	while (crt < str.size()) {
		if (str[crt] == ' ' || str[crt] == '\t' || str[crt] == '\r' || str[crt] == '\n' || str[crt] == '\v') ++crt;
		else break;
	}
}
static void eat_digit(std::string & str, size_t & crt) {
	while (crt < str.size()) {
		if (ISDIGIT(str[crt]))++crt;
		else break;
	}
}

Value* parse(std::string & str) {
	size_t crt = 0;
	Value* ret = parse(str, crt);
	eat_white(str, crt);
	if (crt != str.size()) {
		delete ret;
		throw JSONexception(crt, "EXTRA NONE-WHITESPACE-CHAR");
	}
	return ret;
}
Value* parse(std::string & str, size_t & crt) {
	eat_white(str, crt);
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

Value* parse_number(std::string & str, size_t & crt) {
	using namespace std;
	size_t lo = crt;
	double  x = 0;

	if (str[crt] == '-')++crt;

	if (str[crt] == '0')++crt;
	else if (ISD1TO9(str[crt])) {
		++crt;
		eat_digit(str, crt);
	}
	else throw JSONexception(crt, "SHOULD HAVE DIGITS THERE");

	if (str[crt] == '.') {
		size_t sublo = ++crt;
		eat_digit(str, crt);
		if (sublo == crt)throw JSONexception(crt, "AT LEAST ONE DIGIT AFTER '.'");
	}

	if (str[crt] == 'e' || str[crt] == 'E') {
		++crt;
		if (str[crt] == '+' || str[crt] == '-') {
			++crt;
		}
		eat_digit(str, crt);
	}

	return (istringstream(string(str, lo, crt - lo + 1)) >> x) ? new class::Number(x) : new class::Number(0);
}
Value * parse_string(std::string & str, size_t & crt) {
	++crt;
	std::string ret;
	while (crt < str.size()) {
		if (str[crt] == '"') { ++crt; return new class::String(ret); }
		else if (str[crt] == '\\') {
			ret.push_back(str[crt++]);
			switch (str[crt])
			{
			case '"':case '\\':case '/':case 'b':case 'f':case 'n':case 'r':case 't':
			case 'u':ret.push_back(str[crt++]); break;
			default: throw JSONexception(crt, "ILLEGAL ESCAPE-CHAR");
			}
		}
		else
			ret.push_back(str[crt++]);
	}
	throw JSONexception(crt, "NO END MARKS '\"'");
}
Value* parse_array(std::string & str, size_t & crt) {
	++crt;
	class::Array* ret = new class::Array();
	eat_white(str, crt);
	if (str[crt] == ']') {
		++crt; return ret;
	}
	while (1) {
		Value* tmp = nullptr;
		try {
			tmp = parse(str, crt);
		}
		catch (...) {
			delete tmp;
			delete ret;
			throw;
		}

		ret->push(tmp);
		eat_white(str, crt);
		if (str[crt] == ',') ++crt;
		else if (str[crt] == ']') {
			++crt; return ret;
		}
		else { delete ret; throw JSONexception(crt, "array() ENDLESS PAIN BRO"); }
	}
	return nullptr;
}
/////////////////////////////////////////////////////

Value* parse_object(std::string & str, size_t & crt) {
	// throw JSONexception(crt, "parse_object() NOT IMPLEMENTED YET");
	++crt;
	class::Object* ret = new class::Object();
	eat_white(str, crt);
	if (str[crt] == '}') {
		++crt; return ret;
	}
	while (1) {
		class::String* tmpstr = nullptr;
		try {
			tmpstr = static_cast<class::String*>(parse(str, crt));
		}
		catch (...) {
			delete tmpstr;
			delete ret;
			throw;
		}
		eat_white(str, crt);
		if (str[crt] == ':') ++crt;
		else { throw JSONexception(crt, "object() SHOULD BE ':' HERE"); }

		eat_white(str, crt);
		Value* tmpval = nullptr;
		try {
			tmpval = parse(str, crt);
		}
		catch (...) {
			delete tmpval;
			delete ret;
			throw;
		}
		ret->insert(tmpstr, tmpval);
		eat_white(str, crt);

		if (str[crt] == ',') ++crt;
		else if (str[crt] == '}') {
			++crt; return ret;
		}
		else { delete ret; throw JSONexception(crt, "object() ENDLESS PAIN BRO"); }
	}
	return nullptr;
	return nullptr;
}
