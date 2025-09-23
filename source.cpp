#include <iostream>
#include <filesystem>
#include <string>

int main() {
    // First the program will check if there are any jpg or png files in the dir
   
    std::string filename = "";
    bool found = false;
    std::filesystem::path directory_path = std::filesystem::current_path();
    std::cout << "Input file name: ";
    std::cin >> filename; 

    for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
        if (entry.is_regular_file()) {
            std::filesystem::path file_path = entry.path();
            if (entry.path().filename() == filename) {
                std::string ext = file_path.extension().string();
                std::transform(ext.begin(), ext.end(), ext.begin(), [] (unsigned char c) {return std::tolower(c); });
                if (ext == ".jpg" || ext == ".png") {
                    std::cout << "Found image file: " << file_path << "\n";
                    found = true; 
                } else {
                    std::cout << "\nIncorrect file format (only .png or .jpg allowed).\n";
                }
                break; 
            }
        }
    }
    if (!found) {
        std::cout << "Image file not found, try again.\n";
    }

    return 0;
}