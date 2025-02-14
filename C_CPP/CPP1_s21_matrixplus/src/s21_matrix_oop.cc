#include "s21_matrix_oop.h"

#include <iostream>

using std::domain_error;
using std::invalid_argument;
using std::range_error;

namespace s21 {

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw invalid_argument("rows or cols value is less than 1");
  }
  allocate_matrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  allocate_matrix();
  copy_matrix_arg(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { FreeMatrix_(); }

void S21Matrix::SetRows(int rows) {
  S21Matrix buff(rows, cols_);
  for (int i = 0; i < rows_ && i < rows; i++)
    for (int j = 0; j < cols_; j++) buff(i, j) = matrix_[i][j];
  *this = buff;
}

void S21Matrix::SetCols(int cols) {
  S21Matrix buff(rows_, cols);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_ && j < cols; j++) buff(i, j) = matrix_[i][j];
  *this = buff;
}

double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw range_error("Elem doesn't exist");
  }
  return matrix_[row][col];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    FreeMatrix_();
    rows_ = other.rows_;
    cols_ = other.cols_;
    allocate_matrix();
    copy_matrix_arg(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    FreeMatrix_();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double& num) {
  MulNumber(num);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix operator*(double num, S21Matrix& other) { return other * num; }

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
#define ABS(x) (((x) < 0) ? -(x) : (x))
  bool result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; result && i < rows_; i++)
    for (int j = 0; result && j < cols_; j++)
      result = ABS(matrix_[i][j] - other(i, j)) < 1E-7;
#undef ABS
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  size_check(other);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other(i, j);
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  size_check(other);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other(i, j);
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw domain_error("Invalid size");
  }
  S21Matrix mult(rows_, other.cols_);
  for (int k = 0; k < other.cols_; k++) {
    for (int i = 0; i < rows_; i++) {
      long double sum = 0;
      for (int j = 0; j < cols_; j++) sum += matrix_[i][j] * other(j, k);
      mult(i, k) = sum;
    }
  }
  *this = mult;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) res(j, i) = matrix_[i][j];
  return res;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_ || !matrix_) {
    throw domain_error("Determinant dosen't exist");
  }
  double res = 0;
  if (rows_ == 1) {
    res = matrix_[0][0];
  } else if (rows_ == 2) {
    res = matrix_[0][0] * matrix_[1][1];
    res -= matrix_[0][1] * matrix_[1][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      S21Matrix minor(Minor(0, i));
      res += (i % 2 ? -1 : 1) * matrix_[0][i] * minor.Determinant();
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_ || !matrix_) {
    throw domain_error("CalcComplements dosen't exist");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res(0, 0) = 1;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix min(Minor(i, j));
        res(i, j) = min.Determinant() * (((i + j) % 2) ? -1 : 1);
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0) {
    throw domain_error("Inverse matrix dosen't exist");
  }
  S21Matrix res(CalcComplements());
  res = res.Transpose();
  res *= (1 / det);
  return res;
}

S21Matrix S21Matrix::Minor(int row, int col) {
  S21Matrix res(rows_ - 1, cols_ - 1);
  for (int i = 0; i < res.rows_; i++) {
    int Ai = i < row ? i : i + 1;
    for (int j = 0; j < res.cols_; j++) {
      int Aj = j < col ? j : j + 1;
      res(i, j) = matrix_[Ai][Aj];
    }
  }
  return res;
}

void S21Matrix::allocate_matrix() {
  if (!rows_ || !cols_) {
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  } else
    matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_];
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = 0.;
}

void S21Matrix::copy_matrix_arg(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
}

void S21Matrix::size_check(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw domain_error("Not equal size");
  }
}

void S21Matrix::FreeMatrix_() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++)
      if (matrix_[i]) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}
}  // namespace s21