#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <string>
#include <vector>

using grid = std::vector<std::vector<char>>;
using hints = std::vector<unsigned int>;

// Print the contents of the grid.
void print_grid(const grid& nonogram);

// Read the grid from the standard input.
void read_grid(grid& nonogram, std::vector<hints>& row_hints, std::vector<hints>& col_hints);


// Check if the sum of row hints is equal to the sum of column hints.
// This function is used to verify the input consistency.
bool hints_match(const std::vector<hints>& row_hints, const std::vector<hints>& col_hints);

// Get the number of nonogram's rows.
unsigned int get_rows(const grid& nonogram);

// Get the number of nonogram's columns.
unsigned int get_cols(const grid& nonogram);

#endif