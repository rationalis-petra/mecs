#ifndef __BLOCK_HPP
#define __BLOCK_HPP

#include <vector>

#include "math/diagonal_matrix.hpp"

/* The SparseMatrix class is for representing matrices which are mostly 0's,
 * and is optimised for constratint equation solving
 *
 * It works by storing a vector of 'blocks', which are n*m submatrices (usually
 * reprsenting one rigidbody/constraint combination)
 */

class Block {

};

class SparseMatrix {
  std::vector<Block> blocks;

public:
  SparseMatrix();
};

SparseMatrix operator*(const DiagonalMatrix& left, const SparseMatrix& right);
SparseMatrix operator*(const SparseMatrix& left, const SparseMatrix& right);
#endif
