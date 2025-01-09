#include <iostream>
#include <fstream>
#include <cstdio>
#include <chrono>

int main() {
    size_t num_values = 10;
    double value = 1.34;

    // fwrite
    auto start = std::chrono::high_resolution_clock::now();
    FILE *file = fopen("data_fwrite.bin", "wb");
    for (size_t i = 0; i < num_values; ++i) {
        fwrite(&value, sizeof(double), 1, file);
    }
    fclose(file);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "fwrite time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";

    // std::ofstream <<
    start = std::chrono::high_resolution_clock::now();
    std::ofstream ofs("data_ofstream.txt");
    for (size_t i = 0; i < num_values; ++i) {
        ofs << value << "\n";
    }
    ofs.close();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "<< time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";

    return 0;
}
