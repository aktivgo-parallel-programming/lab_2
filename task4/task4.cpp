#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <vector>
#include <execution>
#include <algorithm>

std::vector<double> create_random_vector(int, int, int);
void print_vector(std::vector<double>);
double calculate_sort_time(std::vector<double>);

const int SIZE = 1000000000;
const double LEFT_BORDER = 0.1;
const double RIGHT_BORDER = 10.1;

int main()
{
	srand(time(0));

	std::vector<double> vector = create_random_vector(SIZE, LEFT_BORDER, RIGHT_BORDER);

	/*print_vector(vector);
	std::cout << std::endl;*/

	double time = calculate_sort_time(vector);
	std::cout << "Time to sort: " << time << "s" << std::endl;
}

std::vector<double> create_random_vector(int size, int left_border, int right_border)
{
	std::vector<double> result;
	for (int i = 0; i < size; i++) {
		result.push_back(rand() % right_border + left_border);
	}

	return result;
}

void print_vector(std::vector<double> vector)
{
	for (int i = 0; i < vector.size(); i++) {
		std::cout << vector[i] << " ";
	}
}

double calculate_sort_time(std::vector<double> vector)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	start = std::chrono::high_resolution_clock::now();
	std::sort(std::execution::par, vector.begin(), vector.end());
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	/*print_vector(vector);
	std::cout << std::endl;*/
	return diff.count();
}