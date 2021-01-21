#ifndef __DIAGONAL_MATRIX_HPP
#define __DIAGONAL_MATRIX_HPP

#include <vector>


class DiagonalMatrix {
private:
  std::vector<float> values;

public:
  DiagonalMatrix(std::vector<float> values);
};


// operations
DiagonalMatrix operator*(const DiagonalMatrix& left, const DiagonalMatrix& right);

#endif
