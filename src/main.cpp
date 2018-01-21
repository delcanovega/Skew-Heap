#include <iostream>
#include <fstream>
#include <chrono>
#include <array>
#include <numeric>
#include <random>

#include "SkewHeap.hpp"

void test_insert();
void test_merge();
void test_min();
void test_remove();
void test_mod();

int main(int argc, char* argv[]) {
    
    SkewHeap<int> h = SkewHeap<int>();
    h.insert(10);
    h.insert(20);
    h.insert(30);
    h.insert(40);
    h.insert(50);
    h.insert(60);
    h.insert(70);

    h.print();
    h.mod_key(h.nodes[1], 5);
    h.print();
    

    //test_insert();
    //test_merge();
    //test_min();
    //test_remove();
    //test_mod();
}

void test_insert() {
    const int N = 5;
    std::array<int, N> steps = {10000, 20000, 30000, 40000, 50000};
    std::array<double, N> average = std::array<double, N>();

    std::ofstream outputFile( "./tests/plot_insert.dat" );
    outputFile << "0 0" << std::endl;

    int num{0};
    SkewHeap<int> h;
    /*
    // "Small" test case
    auto start = std::chrono::system_clock::now();
    for (int j{0}; j < 100; j++) {
        h = SkewHeap<int>();
        for (int k{0}; k < 1000; k++) {
            std::cin >> num;
            h.insert(num);
        }
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    outputFile << 500 << " ";
    outputFile << elapsed_seconds.count() / (1000*100) << std::endl;
    */
    
    // "Big" test cases
    h = SkewHeap<int>();
    int step{steps[0]/2};
    for (int i{0}, j{0}; i < N; i++) {

        auto start = std::chrono::system_clock::now();
        for (; j < steps[i]; j++) {
            std::cin >> num;
            h.insert(num);
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;

        int insertions{10000};

        average[i] = elapsed_seconds.count() / insertions;
        outputFile << step << " " << average[i] << std::endl;
        step += 10000;
    }
}

void test_merge() {
    const int N = 10;
    std::array<int, N> steps = {5, 50, 500, 5000, 15000, 25000, 35000, 45000,
                                55000, 65000};
    std::array<double, N> average = std::array<double, N>();
    
    std::ofstream outputFile( "./tests/plot_merge.dat" );
    //outputFile << "0 0" << std::endl;

    for (int i{0}; i < N; i++) {
        double time_sum{0};
        for (int j{0}; j < 10; j++) {
            SkewHeap<int> h1 = SkewHeap<int>();
            SkewHeap<int> h2 = SkewHeap<int>();

            int num{0};
            for (int k{0}; k < steps[i]; k++) {
                std::cin >> num;
                h1.insert(num);
                std::cin >> num;
                h2.insert(num);
            }

            auto start = std::chrono::system_clock::now();
            h1.merge(h2);
            auto end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsed_seconds = end-start;
            time_sum += elapsed_seconds.count();
        }
        average[i] = time_sum / 10;
        outputFile << steps[i] << " " << average[i] << std::endl;
    }
}

void test_min() {
    const int N = 13;
    std::array<int, N> steps = {5, 50, 500, 5000, 15000, 25000, 35000, 45000,
                                55000, 65000, 75000, 85000, 95000};
    std::array<double, N> average = std::array<double, N>();

    std::ofstream outputFile( "./tests/plot_min.dat" );
    //outputFile << "0 0" << std::endl;

    for (int i{0}; i < N; i++) {
        double time_sum{0};
        for (int j{0}; j < 10; j++) {
            SkewHeap<int> h1 = SkewHeap<int>();

            int num{0};
            for (int k{0}; k < steps[i]; k++) {
                std::cin >> num;
                h1.insert(num);
            }
            

            auto start = std::chrono::system_clock::now();
            for (int k{0}; k < 1000; k++) {
                h1.min();
            }
            auto end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsed_seconds = end-start;
            time_sum += elapsed_seconds.count()/1000;
        }
        average[i] = time_sum / 10;
        outputFile << steps[i] << " " << average[i] << std::endl;
    }
}

void test_remove() {
    const int N = 10;
    std::array<int, N> steps = {5000, 15000, 25000, 35000, 45000,
                                55000, 65000, 75000, 85000, 95000};
    std::array<double, N> average = std::array<double, N>();

    SkewHeap<int> h = SkewHeap<int>();
    int num{0};
    for (int i{0}; i < 100000; i++) {
        std::cin >> num;
        h.insert(num);
    }

    std::ofstream outputFile( "./tests/plot_delete.dat" );
    //outputFile << "0 0" << std::endl;

    for (int i{N-1}; i >= 0; i--) {
        auto start = std::chrono::system_clock::now();
        
        for (int j{0}; j < 10000; j++) {
            h.delete_min();
        }
        
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end-start;
        average[i] = elapsed_seconds.count()/10000;

        outputFile << steps[i] << " " << average[i] << std::endl;
    }
}

void test_mod() {
    const int N = 13;
    std::array<int, N> steps = {5, 50, 500, 5000, 15000, 25000, 35000, 45000,
                                55000, 65000, 75000, 85000, 95000};
    std::array<double, N> average = std::array<double, N>();

    std::ofstream outputFile( "./tests/plot_mod.dat" );
    outputFile << "0 0" << std::endl;

    SkewHeap<int> h = SkewHeap<int>();

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i{0}; i < N; i++) {
        int num{0};
        int insertions{5};
        if (i != 0)
            insertions = steps[i] - steps[i-1];

        for (int j{0}; j < insertions; j++) {
            std::cin >> num;
            h.insert(num);
        }

        std::uniform_int_distribution<> dis(0, h.n-1);

        auto start = std::chrono::system_clock::now();
        for (int j{0}; j < 100000; j++) {
            int k{dis(gen)};
            //std::cout << h.n << " " << k << std::endl;
            //h.print();
            h.mod_key(h.nodes[k], 150000);
        }
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end-start;
        average[i] = elapsed_seconds.count()/100000;

        outputFile << steps[i] << " " << average[i] << std::endl;
    }
}