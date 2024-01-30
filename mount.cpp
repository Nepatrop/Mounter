#include <cstdlib> 
#include <iostream>
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
        cout << mount_point << " не удалось отмонтировать ." << endl;
        return false;
    }
    cout << mount_point << " отмонтирован." << endl;
    return true;
}

int main() {
    string device;
    string mount_dir;

    system("lsblk");
    printf("Введите имя носителя:");
    std::cin >> device;
    device = "/dev/" + device;

    cout << "Директория для монтирования (0 - по умолчанию '/media/flash'): ";
    cin >> mount_dir;
    if (mount_dir == "0") {
        mount_dir = "/media/flash";
    };

    if (!DriveMount(device, mount_dir)) {
        cerr << "Ошибка монтирования диска." << endl;
        exit(EXIT_FAILURE);
    }

    if (!DriveUnmount(mount_dir)) {
        cerr << "Ошибка отмонтирования диска." << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}