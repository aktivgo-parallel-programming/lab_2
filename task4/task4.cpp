#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <execution>
#include <algorithm>

double* create_random_array(int, int, int);
void print_array(double*, int);
double calculate_sort_time(double*, int);

const int SIZE = 1000000;
const int LEFT_BORDER = 0;
const int RIGHT_BORDER = 1000 + 1;

int main()
{
	srand(time(nullptr));

	double* array = create_random_array(SIZE, LEFT_BORDER, RIGHT_BORDER);

    /*print_array(array, SIZE);
	std::cout << std::endl;*/

	double time = calculate_sort_time(array, SIZE);
	std::cout << "Time to sort: " << time << "s" << std::endl;

    /*print_array(array, SIZE);
    std::cout << std::endl;*/
}

double get_random_number(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<double>(rand() * fraction * (max - min + 1) + min);
}

double* create_random_array(int size, int left_border, int right_border)
{
	auto *result = new double[size];
    for (int i = 0; i < size; i++) {
		result[i] = get_random_number(left_border, right_border);
	}

	return result;
}

void print_array(double* array, int size)
{
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
}

double calculate_sort_time(double* array, int size)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	start = std::chrono::high_resolution_clock::now();

	std::sort(std::execution::seq, array, array + size);

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}