#include <iostream>
#include <chrono>







int main(){
	using namespace std::literals::chrono_literals;
	
	auto start = std::chrono::high_resolution_clock::now();

	system("cls");

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration = end-start;
	std::cout<< "T = "<<duration.count() *1000.0f<<std::endl;




    return 0;
}