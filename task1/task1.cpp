#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <execution>

void fill_vector(std::vector<int> &, int, int, int);
void print_vector(const std::vector<int>&);
int calculate_divisor_count(int);
double calculate_search_divisor_count_time(std::vector<int>, std::vector<int> &);

const int SIZE = 500000;
const int LEFT_BORDER = 100000;
const int RIGHT_BORDER = 1000000 + 1;

int main()
{
    srand(time(nullptr));

    std::vector<int> vector;
    fill_vector(vector, SIZE, LEFT_BORDER, RIGHT_BORDER);

    /*print_vector(vector);
    std::cout << std::endl;*/

    std::vector<int> result(vector.size());
    double time = calculate_search_divisor_count_time(vector, result);
    std::cout << "Time to search divisors count: " << time << "s" << std::endl;

    /*print_vector(result);*/

    return 0;
}

void fill_vector(std::vector<int> &vector, int size, int left_border, int right_border)
{
    for (size_t i = 0; i < size; i++) {
        vector.push_back(rand() % right_border + left_border);
    }
}

void print_vector(const std::vector<int>& vector)
{
    for (int i : vector) {
        std::cout << i << " ";
    }
}

int calculate_divisor_count(int n)
{
    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i != n) {
                count++;
            }
            count++;
        }
    }

    return count;
}

double calculate_search_divisor_count_time(std::vector<int> vector, std::vector<int> &result)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    std::transform(std::execution::seq, vector.begin(), vector.end(), result.begin(), calculate_divisor_count);
    
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    return diff.count();
}
