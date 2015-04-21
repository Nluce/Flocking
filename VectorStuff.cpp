
#include <vector>



class Foo {
public:
	int count;

	void Draw();
};

std::vector<Foo *> fooList;

void test1(){

	// old fashioned loop
	for (int i = 0; i < fooList.size(); i++){
		Foo* temp = fooList[i];
		// do stuf with temp
	}

	// newer type loop
	for (Foo* temp : fooList){
		// do stuf with temp
	}

	// newer type loop using auto
	for (auto temp : fooList){
		// do stuf with temp
	}


	// loop using iterators
	{
		auto it = fooList.begin();
		while (it < fooList.end()) {
			Foo* temp = *it;
			// do stuf with temp
			it++;
		}
	}

	// use the following type of loop to delete items from the list while looping.
	{
		auto it = fooList.begin();
		while (it < fooList.end()) {
			Foo* temp = *it;
			// do stuf with temp


			bool deleteIt = true;
			if (deleteIt){
				it = fooList.erase(it);
			}
			else {
				it++;
			}
		}
	}
}