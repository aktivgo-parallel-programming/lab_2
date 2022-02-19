#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <vector>
#include <execution>
#include <algorithm>

std::vector<double> create_random_vector(int, int, int);
void print_vector(const std::vector<double>&);
double calculate_sort_time(std::vector<double>);

const int SIZE = 500000000;
const int LEFT_BORDER = 0;
const int RIGHT_BORDER = 1000;

int main()
{
	srand(time(nullptr));

	std::vector<double> vector = create_random_vector(SIZE, LEFT_BORDER, RIGHT_BORDER);

	/*print_vector(vector);
	std::cout << std::endl;*/

	double time = calculate_sort_time(vector);
	std::cout << "Time to sort: " << time << "s" << std::endl;
}

double get_random_number(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<double>(rand() * fraction * (max - min + 1) + min);
}

std::vector<double> create_random_vector(int size, int left_border, int right_border)
{
	std::vector<double> result;
	result.reserve(size);
    for (int i = 0; i < size; i++) {
		result.push_back(get_random_number(left_border, right_border));
	}

	return result;
}

void print_vector(const std::vector<double>& vector)
{
	for (double i : vector) {
		std::cout << i << " ";
	}
}

double calculate_sort_time(std::vector<double> vector)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	start = std::chrono::high_resolution_clock::now();
	std::sort(std::execution::par_unseq, vector.begin(), vector.end());
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	/*print_vector(vector);
	std::cout << std::endl;*/
	return diff.count();
}