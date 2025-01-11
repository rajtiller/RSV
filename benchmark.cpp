#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void write_using_fwrite(const std::string& filename, const char* data, size_t data_size) {
    FILE* file = fopen(filename.c_str(), "wb");
    if (!file) {
        std::cerr << "Error opening file for fwrite\n";
        return;
    }
    
    fwrite(data, sizeof(char), data_size, file);
    
    fclose(file);
}

void write_using_mmap(const std::string& filename, const char* data, size_t data_size) {
    int fd = open(filename.c_str(), O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        std::cerr << "Error opening file for mmap\n";
        return;
    }

    ftruncate(fd, data_size);

    void* mapped_mem = mmap(NULL, data_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_mem == MAP_FAILED) {
        std::cerr << "Error mapping file for mmap\n";
        close(fd);
        return;
    }

    std::memcpy(mapped_mem, data, data_size);

    msync(mapped_mem, data_size, MS_SYNC);
    munmap(mapped_mem, data_size);

    close(fd);
}

int main() {
    const size_t data_size = 1024 * 1024 * 100; // 100 MB of data
    char* data = new char[data_size];
    std::memset(data, 'A', data_size);  // Fill the data with 'A'

    std::cout << "Benchmarking fwrite:\n";
    auto start = std::chrono::high_resolution_clock::now();
    write_using_fwrite("fwrite_test.bin", data, data_size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> fwrite_duration = end - start;
    std::cout << "Time taken for fwrite: " << fwrite_duration.count() << " seconds\n";

    std::cout << "Benchmarking mmap:\n";
    start = std::chrono::high_resolution_clock::now();
    write_using_mmap("mmap_test.bin", data, data_size);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> mmap_duration = end - start;
    std::cout << "Time taken for mmap: " << mmap_duration.count() << " seconds\n";

    delete[] data;
    return 0;
}
