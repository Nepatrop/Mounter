#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

bool DriveMount(string device, string mount_point) {
    string command = "sudo mount " + device + " " + mount_point;
    if (system(command.c_str()) == -1) {
        cout << device << " не удалось смонтировать в " << mount_point << "." << endl;
        return false;
    }
    cout << device << " монтирован  в " << mount_point << "." << endl;
    return true;
}

bool DriveUnmount(string mount_point) {
    string command = "sudo umount " + mount_point;
    if (system(command.c_str()) == -1) {
        cout << mount_point << " не удалось отмонтировать." << endl;
        return false;
    }
    cout << mount_point << " отмонтирован." << endl;
    return true;
}

bool FileTransfer(string filePath, string mount_dir) {
    std::ifstream source;
    std::ofstream destination;

    source.open(filePath, std::ios::binary);
    if (!source) {
        std::cout << "Не удалось открыть исходный файл '" << filePath << "'." << std::endl;
        return false;
    }
    
    std::string path = mount_dir + filePath;
    if (!path.empty() && path.back() == '/') {
        path.pop_back();
    }
    destination.open(path, std::ios::binary);
    if (!destination) {
        std::cout << "Не удалос открыть файл назначения '" << path << "'." << std::endl;
        return false;
    }
        
    destination << source.rdbuf();
    source.close();
    destination.close();
    return true;
}

int main() {
    string device;
    string mount_dir;
    string pathToFile;
    bool working = true;

    system("lsblk");
    printf("Введите имя носителя: ");
    cin >> device;
    cin.ignore();
    device = "/dev/" + device;

    cout << "Директория для монтирования (0 - по умолчанию '/media/flash/'): ";
    getline(cin, mount_dir);
    cin.ignore();
    if (mount_dir == "0") {
        mount_dir = "/media/flash/";
    }
    string mkdir = "mkdir -p " + mount_dir;
    system(mkdir.c_str());

    if (!DriveMount(device, mount_dir)) {
        cout << "Ошибка монтирования диска." << endl;
        exit(EXIT_FAILURE);
    }

    while (working){
        cout << "Путь до файла, который необходимо скопировать на носитель (end - завершение): ";
        getline(cin, pathToFile);
        cin.ignore();
        if (pathToFile == "end") {
            working = false;
            break;
        }
        if (FileTransfer(pathToFile, mount_dir)) {
            std::cout << "Копирование выполнено!" << std::endl;
        }
        else {
            std::cout << "Ошибка при копировании файла." << std::endl;
        }
    }

    if (!DriveUnmount(mount_dir)) {
        cerr << "Ошибка отмонтирования диска." << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}