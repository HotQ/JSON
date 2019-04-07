#include "JSON.hpp"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#endif // _WIN32
#include <iostream>

void parse_many(std::initializer_list<std::string> strlist) {
	for (auto str : strlist) {
		std::cout << "\n" << str << "\n";
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
#define r(str) #str
int main()
{
	using namespace std;

	Value* str1 = new class::String("SDFG"),
		* str2 = new class::String("lhlkj"),
		* arr1 = new class::Array({ str1, str2 }),
		* arr2 = new class::Array({ arr1,new class::Boolean(false), new class::Null() }),
		* obj1 = new class::Object({ make_pair(new class::String("arr2"),arr2) , make_pair(new class::String("NULL"),new class::Null())  , make_pair(new class::String("Number"),new class::Number(-4e3)) });
	//(*static_cast<class::Object*>(obj1))[string("String")] = unique_ptr<Value>(new class::String("asdfrweg"));
	std::cout << "================================\n\n\n"
		<< obj1->stringify() << endl
		<< "\n\n\n================================\n";
	delete obj1;


	parse_many({
		// "true", " null", " false  ", " true1", " null1 ", " false 1 ",
		// "123","0.409532765E10","-1.3e+45 "," 567.09"," 0E-3 ","1e-10000",".312","61." 
		// R"("123\n")",R"("l;ziSjdo'\u089")",R"("1"23")",R"("²Ë\"23")",R"("\²Ë\"23")",
		// "[]"," [ ] "," [ 9,] ","[true , null , true]",R"(["²Ë",[-1.3e+5,null]])",R"(["²Ë",[-1.3e+5,null])",
		"{}"," { } ",R"({"key1":1})", R"({"employees": [{ "firstName":"Bill" , "lastName":"Gates" },{ "firstName":"George" , "lastName":"Bush" },{ "firstName":"Thomas" , "lastName":"Carter" }]})"
		});
#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif // _WIN32
}
