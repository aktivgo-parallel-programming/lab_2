#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <execution>

int** create_matrix(int);
void fill_matrix(int**, int, int, int);
void delete_matrix(int**, int);
void print_matrix(int**, int);
int** multiply_matrix(int**, int**, int);
int multiply(int, int);
double calculate_multiply_time(int**, int**, int);

const int SIZE = 512;
const int LEFT_BORDER = -1000;
const int RIGHT_BORDER = 1000;

int main()
{
    srand(time(0));

    int** matrix_1 = create_matrix(SIZE);
    int** matrix_2 = create_matrix(SIZE);
    fill_matrix(matrix_1, SIZE, LEFT_BORDER, RIGHT_BORDER);
    fill_matrix(matrix_2, SIZE, LEFT_BORDER, RIGHT_BORDER);

    /*print_matrix(matrix_1, SIZE);
    std::cout << std::endl;
    print_matrix(matrix_2, SIZE);
    std::cout << std::endl;*/

    double time = calculate_multiply_time(matrix_1, matrix_2, SIZE);
    std::cout << "Time to multiply: " << time << "s" << std::endl;

    delete_matrix(matrix_1, SIZE);
    delete_matrix(matrix_2, SIZE);
}

int** create_matrix(int size)
{
    int** matrix = new int* [size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

void fill_matrix(int** matrix, int size, int left_border, int right_border)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % right_border - left_border;
        }
    }
}

void delete_matrix(int** matrix, int size)
{
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
}

void print_matrix(int** matrix, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int** multiply_matrix(int** matrix_1, int** matrix_2, int size)
{
    int** result = create_matrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::vector <int> m1;
            std::vector <int> m2;
            for(int k = 0; k < size; k++) {
                m1.push_back(matrix_1[i][k]);
                m2.push_back(matrix_2[k][j]);
            }
            std::vector <int> r(size);
            result[i][j] = std::transform_reduce(std::execution::seq, m1.begin(), m1.end(), m2.begin(), multiply);
        }
    }

    return result;
}

int multiply(int n) {
    return n * m;
}

double calculate_multiply_time(int** matrix_1, int** matrix_2, int size)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    int** result = multiply_matrix(matrix_1, matrix_2, SIZE);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}