#include <cstdio>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <vector>

int main()
{
    std::vector<float> data;
    for (int x = 0; x < 1000000; x++) {
        float y = 1.0*x/1000000;
        data.push_back(y);
    }
    FILE *rsv_output = fopen("output.rsv", "wb");
    auto start = std::chrono::high_resolution_clock::now();
    for (int x = 0; x < 1000000; x++)
    {
        fwrite(&data[x], 4, 1, rsv_output);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "fwrite time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
    fclose(rsv_output);
    std::ofstream os_output("output.csv");
    start = std::chrono::high_resolution_clock::now();
    for (int x = 0; x < 1000000; x++)
    {
        os_output << data[x];
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "ostream time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
    os_output.close();
}

// to do:
// 