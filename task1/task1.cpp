#include <iostream>
#include <vector>
#include <ctime>

void fill_vector(std::vector<int>, int, int);
void print_vector(std::vector<int>);

const int SIZE = 10;
const int LEFT_BORDER = 100000;
const int RIGHT_BORDER = 1000000;

int main()
{
    srand(time(0));

    std::vector<int> vector(SIZE);
    fill_vector(vector, LEFT_BORDER, RIGHT_BORDER);
    print_vector(vector);
}

void fill_vector(std::vector<int> vector, int left_border, int right_border) {
    std::cout << vector.size() << std::endl;
    for (size_t i = 0; i < vector.size(); i++) {
        vector.push_back(rand() % right_border + left_border);
        std::cout << vector[i] << std::endl;
    }
}

void print_vector(std::vector<int> vector) {
    std::cout << vector.size() << std::endl;
    for (size_t i = 0; i < vector.size(); i++) {
        std::cout << vector[i] << " " << std::endl;
    }
}