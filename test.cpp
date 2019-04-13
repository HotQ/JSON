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

	Value* str1 = new String("SDFG"),
		* str2 = new String("lhlkj"),
		* arr1 = new Array({ str1, str2 }),
		* arr2 = new Array({ arr1,new Boolean(false), new Null() }),
		* obj1 = new Object({ make_pair(new String("arr2"),arr2) , make_pair(new String("NULL"),new Null())  , make_pair(new String("Number"),new Number(-4e3)) });
	std::cout << "================================\n\n\n"
		<< obj1->stringify() << endl
		<< "\n\n\n================================\n";
	delete obj1;


	parse_many({
		// "true", " null", " false  ", " true1", " null1 ", " false 1 ",
		// "123","0.409532765E10","-1.3e+45 "," 567.09"," 0E-3 ","1e-10000",".312","61." 
		// R"("123\n")",R"("l;ziSjdo'\u089")",R"("1"23")",R"("²Ë\"23")",R"("\²Ë\"23")",
		// "[]"," [ ] "," [ 9,] ","[true , null , true]",R"(["²Ë",[-1.3e+5,null]])",R"(["²Ë",[-1.3e+5,null])",
		"{}"," { } ",R"({"key1":1})",R"({"key1":1,})", R"({"employees": [{ "firstName":"Bill" , "lastName":"Gates" },{ "firstName":"George" , "lastName":"Bush" },{ "firstName":"Thomas" , "lastName":"Carter" }]})",
			R"(
			[{
				"_index": "item",
				"_type": "items",
				"_id": "966b0d44-6e1f-4fe6-b971-cf9522d8ec09",
				"firstname": "Francis",
				"lastname": "Backer",
				"age": 3
			}, {
				"_index": "item",
				"_type": "items",
				"_id": "cb26c226-6a59-4696-8cd0-267bea89fb14",
				"firstname": "Michelle",
				"lastname": "Kilmer",
				"age": 42
			}, {
				"_index": "item",
				"_type": "items",
				"_id": "9d34885c-9b21-4329-be08-e89e73935d08",
				"firstname": "Jenna",
				"lastname": "Karst",
				"age": 57
			}]
			)"
		});
#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif // _WIN32
}
