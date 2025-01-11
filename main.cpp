#include <cstdio>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <vector>

int main()
{
    std::vector<float> data;
    int size = 1000000;
    for (int x = 0; x < size; x++)
    {
        float y = 1.0 * x / size;
        data.push_back(y);
    }
    FILE *rsv_output = fopen("output.rsv", "wb");
    auto start = std::chrono::high_resolution_clock::now(); // Memory map
    for (int x = 0; x < size; x++)
    {
        float curr_num = data[x];
        fwrite(&data[x], 4, 1, rsv_output);
        // fwrite(&data[x], 4, 1, stdout);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "fwrite time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
    fclose(rsv_output);
    std::ofstream os_output("output.csv");
    start = std::chrono::high_resolution_clock::now();
    for (int x = 0; x < size; x++)
    {
        float curr_num = data[x];
        os_output << data[x] << ",";
        if ((x+1) % 1000 == 0) {
            os_output << "\n";
        }
        // float curr_num = data[x];
        // std::cout << data[x] << " ";
        // if ((x+1) % 1000 == 0) {
        //     std::cout << "\n";
        // }

    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "ostream time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
    os_output.close();
}

// to do:
// find way to turn into 2-d matrix
// find way to convert from rsv to csv
// test speed of above conversion
// ensure accuracy