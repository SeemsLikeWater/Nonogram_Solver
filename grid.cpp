#include "grid.h"

// Print the contents of the grid.
void print_grid(const grid& nonogram) {
    unsigned int rows = nonogram.size();
    unsigned int cols = nonogram.at(0).size();
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            std::cout << nonogram.at(i).at(j);
        }
        std::cout << "\n";
    }
}

// Read the grid from the standard input.
void read_grid(grid& nonogram,
               std::vector<hints>& row_hints,
               std::vector<hints>& col_hints) {
    std::string input;
    unsigned int rows, cols;
    std::cin >> rows >> cols >> input;
    nonogram.resize(rows, std::vector<char>(cols, ' '));
    unsigned int ctr = 0;
    while (ctr < rows + cols) {
        std::vector<unsigned int> sequence;
        std::cin >> input;
        while (input != "n") {
            sequence.push_back(std::stoi(input));
            std::cin >> input;
        }
        if (ctr < rows) {
            row_hints.push_back(sequence);
        } else {
            col_hints.push_back(sequence);
        }
        ++ctr;
    }
}

// Check if the sum of row hints is equal to the sum of column hints.
// This function is used to verify the input consistency.
bool hints_match(const std::vector<hints>& row_hints,
                 const std::vector<hints>& col_hints) {
    unsigned int sum_hints_r = 0;
    unsigned int sum_hints_c = 0;
    for (unsigned int i = 0; i < row_hints.size(); ++i) {
        for (unsigned int j = 0; j < row_hints.at(i).size(); ++j) {
            sum_hints_r += row_hints.at(i).at(j);
        }
    }
    for (unsigned int i = 0; i < col_hints.size(); ++i) {
        for (unsigned int j = 0; j < col_hints.at(i).size(); ++j) {
            sum_hints_c += col_hints.at(i).at(j);
        }
    }
    return sum_hints_r == sum_hints_c;
}

// Get the number of nonogram's rows.
unsigned int get_rows(const grid& nonogram) {
    return nonogram.size();
}

// Get the number of nonogram's columns.
unsigned int get_cols(const grid& nonogram) {
    if (nonogram.size() > 0) return nonogram.at(0).size();
    else return 0;
}