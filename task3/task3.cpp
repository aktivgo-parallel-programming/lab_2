#include <iostream>
#include <cstdlib>
#include <chrono>
#include <utility>
#include <vector>
#include <ctime>
#include <execution>

std::vector<std::vector<int>> create_matrix(int);
void fill_matrix(std::vector<std::vector<int>> &, int, int);
void print_matrix(std::vector<std::vector<int>>);
std::vector<std::vector<int>> multiply_matrix(std::vector<std::vector<int>>, std::vector<std::vector<int>>);
void transposition(std::vector<std::vector<int>> &);
double calculate_multiply_time(std::vector<std::vector<int>>, std::vector<std::vector<int>>);

const int SIZE = 2;
const int LEFT_BORDER = 0;
const int RIGHT_BORDER = 3;

int main()
{
    srand(time(0));

    std::vector<std::vector<int>> matrix_1 = create_matrix(SIZE);
    std::vector<std::vector<int>> matrix_2 = create_matrix(SIZE);
    fill_matrix(matrix_1, LEFT_BORDER, RIGHT_BORDER);
    fill_matrix(matrix_2,  LEFT_BORDER, RIGHT_BORDER);

    print_matrix(matrix_1);
    std::cout << std::endl;
    print_matrix(matrix_2);
    std::cout << std::endl;

    double time = calculate_multiply_time(matrix_1, matrix_2);
    std::cout << "Time to multiply: " << time << "s" << std::endl;
}

std::vector<std::vector<int>> create_matrix(int size)
{
    std::vector<std::vector<int>> matrix;
    matrix.reserve(size);
    for (int i = 0; i < size; i++) {
        matrix.emplace_back();
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i].push_back(0);
        }
    }

    return matrix;
}

void fill_matrix(std::vector<std::vector<int>> &matrix, int left_border, int right_border)
{
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            matrix[i][j] = rand() % right_border - left_border;
        }
    }
}

void print_matrix(std::vector<std::vector<int>> matrix)
{
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> multiply_matrix(std::vector<std::vector<int>> matrix_1, std::vector<std::vector<int>> matrix_2)
{
    int size = matrix_1.size();
    std::vector<std::vector<int>> result = create_matrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[j][i] = std::transform_reduce(std::execution::par, matrix_1[i].begin(), matrix_1[i].end(), matrix_2[j].begin(), 0);
        }
    }

    transposition(result);
    return result;
}

void transposition(std::vector<std::vector<int>> &matrix)
{
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = i; j < matrix[i].size(); j++) {
            int t = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = t;
        }
    }
}

double calculate_multiply_time(std::vector<std::vector<int>> matrix_1, std::vector<std::vector<int>> matrix_2)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> result = multiply_matrix(std::move(matrix_1), std::move(matrix_2));
    print_matrix(result);
    std::cout << std::endl;
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}