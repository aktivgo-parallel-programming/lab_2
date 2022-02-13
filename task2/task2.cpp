﻿#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <execution>
#include <algorithm>

void fill_vector(std::vector<int>&, int, int, int);
void print_vector(std::vector<int>);
double calculate_sum_time(std::vector<int>, long &);

const long SIZE = 2000000000;
const int LEFT_BORDER = -1000;
const int RIGHT_BORDER = 1000;

int main()
{
    srand(time(0));

    std::vector<int> vector;
    fill_vector(vector, SIZE, LEFT_BORDER, RIGHT_BORDER);

    /*print_vector(vector);
    std::cout << std::endl;*/

    long result = 0;
    double time = calculate_sum_time(vector, result);
    std::cout << "Time to sum vector: " << time << "s" << std::endl;

    std::cout << "Result: " << result << std::endl;

    return 0;
}

void fill_vector(std::vector<int>& vector, int size, int left_border, int right_border)
{
    for (size_t i = 0; i < size; i++) {
        vector.push_back(rand() % right_border + left_border);
    }
}

void print_vector(std::vector<int> vector)
{
    for (size_t i = 0; i < vector.size(); i++) {
        std::cout << vector[i] << " ";
    }
}

double calculate_sum_time(std::vector<int> vector, long &result)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    result = std::reduce(std::execution::par_unseq, vector.begin(), vector.end());
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}