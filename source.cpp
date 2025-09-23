#include <iostream>
#include <filesystem>
using namespace std;
int main() {
    // First the program will check if there are any jpg or png files in the dir
    filesystem::path directory_path = std::filesystem::current_path();
    cout << directory_path;
    cout << endl;
    cout << "Hello meowmeow\n";
    return 0;
}