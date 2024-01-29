#include <iostream>
#include <cstdlib>
#include <filesystem>


using namespace std;

int main()
{
	string name;
	string dir;
	
	system("lsblk");
	printf("Введите имя флеш носителя:");
	std::cin >> name;
	
	cout << "Директория для монтирования (0 - по умолчанию '/media/flash'):";
	cin >> dir;
	if (dir == "0"){
		dir = "/media/flash";
	};
	
	bool exist = std::filesystem::exists(dir);
	if (!exist){
		system(("mkdir " + dir).c_str());
	}
	
	system(("sudo mount /dev/" + name + " " + dir).c_str());
	std::cout << "Монтирование выполнено в: " << dir << "\n";
	return 0;
}
