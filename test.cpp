#include "JSON.hpp"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#endif // _WIN32
#include <iostream>

void parse_many(std::initializer_list<std::string> strlist) {
	for (auto str : strlist) {
		std::cout << "\n\"" << str << "\"\n";
		Value* demo = nullptr;
		try {
			demo = parse(str);
		}
		catch (JSONexception e) {
			std::cout << e.to_string();
		}
		if (demo) std::cout << demo->stringify() << std::endl;
		else std::cout << "NO PARSE OUTPUT\n";
		delete demo;
	}
}

int main()
{
	using namespace std;

	Value* str1 = new class::String("SDFG"),
		* str2 = new class::String("lhlkj"),
		* arr1 = new class::Array({ str1, str2 }),
		* arr2 = new class::Array({ arr1,new class::Boolean(false), new class::Null() }),
		* obj1 = new class::Object({ make_pair(string("arr2"),arr2) , make_pair("NULL",new class::Null())  , make_pair("Number",new class::Number(-4e3)) });
	(*static_cast<class::Object*>(obj1))[string("String")] = unique_ptr<Value>(new class::String("asdfrweg"));
	cout << "================================\n\n\n"
		<< obj1->stringify() << endl
		<< "\n\n\n================================\n";
	delete obj1;


	parse_many({
		"true", " null", " false  ", " true1", " null1 ", " false 1 ",
		});

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif // _WIN32
}
