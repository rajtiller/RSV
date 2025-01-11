#include <cstdio>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <cstdint> // For uint32_t

int main() {
    const std::string rsv_file = "output.rsv";
    std::ofstream csv_file("output_2.csv");
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream file(rsv_file, std::ios::binary);
    int counter = 0;
    if (!file) {
        std::cerr << "Failed to open file: " << rsv_file << '\n';
        return 0;
    }

    float buffer; 
    while (file.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {
        // Output the value in decimal format
        csv_file << buffer << ",";
        if (++counter == 1000) {
            csv_file << "\n";
            counter = 0;
        }
    }

    // Check if there were leftover bytes
    if (file.gcount() > 0) {
        std::cerr << "Incomplete 32-bit chunk encountered: " << file.gcount() << " byte(s) remaining.\n";
    }

    file.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to convert rsv to csv: " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms\n";
    return 0;
}
// TO DO: Add meta data to find dimensions of array
// Questions: Do I definitely need to add meta data for the dimensions?
// 
