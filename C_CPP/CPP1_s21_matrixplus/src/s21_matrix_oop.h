#ifndef S21_MATRIX_OOP
#define S21_MATRIX_OOP

namespace s21 {
class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  void size_check(const S21Matrix& other);
  void allocate_matrix();
  void copy_matrix_arg(const S21Matrix& other);
  S21Matrix Minor(int row, int col);
  void FreeMatrix_();

 public:
  //  constructors n destructer
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int GetRows() const { return rows_; };
  int GetCols() const { return cols_; };
  void SetRows(int rows);
  void SetCols(int cols);

  double& operator()(int row, int col) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator*=(const double& num);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double num) const;
  friend S21Matrix operator*(double num, S21Matrix& matrix);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  bool operator==(const S21Matrix& other);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
};
}  // namespace s21
#endif