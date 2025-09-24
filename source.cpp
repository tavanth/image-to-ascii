#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

int main() {
    // First the program will check if there are any jpg or png files in the dir
   
    std::string filename = "";
    bool found = false;
    std::filesystem::path directory_path = std::filesystem::current_path();
    std::cout << "Input file name: ";
    std::getline(std::cin, filename);

    for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
        if (entry.is_regular_file()) {
            std::filesystem::path file_path = entry.path();
            if (entry.path().filename() == filename) {
                std::string ext = file_path.extension().string();
                std::transform(ext.begin(), ext.end(), ext.begin(), [] (unsigned char c) {return std::tolower(c); });
                if (ext == ".jpg" || ext == ".png" || ext == ".jpeg") {
                    std::cout << "Found image file: " << file_path << "\n";
                    found = true; 

                    int width, height, channels;
                    unsigned char* img = stbi_load(file_path.string().c_str(), &width, &height, &channels, 1);
                    if (!img) {
                        std::cerr << "Failed to load image.\n";
                        return 1;
                    }
                    const std::string gradient = "@$B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
                    const double scaleX = 0.1;
                    const double scaleY = 0.2;
                    int scaledWidth = static_cast<int>(width * scaleX);
                    int scaledHeight = static_cast<int>(height * scaleY);
                    std::ofstream out(file_path.stem().string() + "_ascii.txt");

                    for (int y=0; y< scaledHeight; ++y) {
                        for (int x = 0; x < scaledWidth; ++x ) {
                            int origX = static_cast<int>( x / scaleX);
                            int origY = static_cast<int>(y / scaleY);
                            int pixelIndex = origY * width + origX;
                            unsigned char pixelValue = img[pixelIndex];
                            int gradientIndex = (pixelValue * (gradient.size() - 1)) / 255;
                            char c = gradient[gradientIndex];
                            std::cout << c;
                            out << c;
                        }
                        std::cout << "\n";
                    }
                    out.close();
                    stbi_image_free(img);
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