#include <iostream>
#include <fstream> // Fayllarni ochish va yozish uchun kutubxona
#include <filesystem>
#include <chrono>
#include <thread>

namespace fs = std::filesystem;

void copyFile(const fs::path& source, const fs::path& destination) {
    std::ifstream sourceFile(source, std::ios::binary); // std::ifstream qo'shildi
    std::ofstream destFile(destination, std::ios::binary); // std::ofstream qo'shildi

    if (!sourceFile.is_open()) {
        std::cerr << "Manba faylini ochib bo'lmadi: " << source << std::endl;
        return;
    }

    if (!destFile.is_open()) {
        std::cerr << "Belgilangan faylni ochib bo‘lmadi: " << destination << std::endl;
        return;
    }

    destFile << sourceFile.rdbuf();

    sourceFile.close();
    destFile.close();
}

void backupFiles(const fs::path& sourceDir, const fs::path& destinationDir) {
    if (!fs::exists(sourceDir) || !fs::is_directory(sourceDir)) {
        std::cerr << "Manba katalogi mavjud emas yoki katalog emas:" << sourceDir << std::endl;
        return;
    }

    if (!fs::exists(destinationDir) || !fs::is_directory(destinationDir)) {
        std::cerr << "Belgilangan katalog mavjud emas yoki katalog emas: " << destinationDir << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(sourceDir)) {
        if (entry.is_regular_file()) {
            fs::path sourceFile = entry.path();
            fs::path destinationFile = destinationDir / sourceFile.filename();
            copyFile(sourceFile, destinationFile);
            std::cout << "Fayl nusxalandi: " << sourceFile << " -> " << destinationFile << std::endl;
        }
    }
}

int main() {
    fs::path sourceDir = "papka"; // manbani aniqlang
    fs::path destinationDir = "bekab"; // hedefni aniqlang

    while (true) {
        backupFiles(sourceDir, destinationDir);
        std::this_thread::sleep_for(std::chrono::seconds(36)); // har 24 soatda bir
    }

    return 0;
}
