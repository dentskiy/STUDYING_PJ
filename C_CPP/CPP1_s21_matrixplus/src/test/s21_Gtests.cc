#include <gtest/gtest.h>

#include <iostream>

#include "../s21_matrix_oop.h"

using namespace s21;
using namespace std;

S21Matrix SetEOne(int n) {
  S21Matrix res(n, n);
  for (int i = 0; i < n; i++) res(i, i) = 1;
  return res;
}

void SetOnes(S21Matrix& other) {
  for (int i = 0; i < other.GetRows(); i++)
    for (int j = 0; j < other.GetCols(); j++) other(i, j) = 1;
}

void PrintMatrix(const S21Matrix& other) {
  for (int i = 0; i < other.GetRows(); i++) {
    for (int j = 0; j < other.GetCols(); j++) {
      cout << other(i, j) << " ";
    }
    cout << endl;
  }
}

// START OF TESTS

TEST(ConstructorTest, costructor1) {
  S21Matrix* m1 = new S21Matrix();
  ASSERT_EQ(m1->GetRows(), 0);
  ASSERT_EQ(m1->GetCols(), 0);
  delete m1;
}

TEST(ConstructorTest, costructor2) {
  S21Matrix* m1 = new S21Matrix(2, 5);
  ASSERT_EQ(m1->GetRows(), 2);
  ASSERT_EQ(m1->GetCols(), 5);
  delete m1;
}

TEST(ConstructorTest, costructor3) {
  S21Matrix m1(5, 5), m2(m1);
  ASSERT_EQ(m2.GetRows(), 5);
  ASSERT_EQ(m2.GetCols(), 5);
}

TEST(ConstructorTest, costructor4) {
  S21Matrix m1(S21Matrix(6, 6));
  ASSERT_EQ(m1.GetRows(), 6);
  ASSERT_EQ(m1.GetCols(), 6);
}

TEST(SetRnCTest, TestOk) {
  S21Matrix m(2, 2);
  m(0, 1) = 5;
  m(1, 0) = 6;
  m.SetRows(1);
  ASSERT_EQ(m.GetRows(), 1);
  m.SetCols(1);
  ASSERT_EQ(m.GetCols(), 1);
  m.SetCols(5);
  m.SetRows(5);
  ASSERT_EQ(m.GetRows(), 5);
  ASSERT_EQ(m.GetCols(), 5);
  for (int i = 0; i < m.GetRows(); i++)
    for (int j = 0; j < m.GetCols(); j++) ASSERT_EQ(m(i, j), 0);
}

TEST(SetRnCTest, TestERR) {
  S21Matrix m(2, 2);
  ASSERT_THROW(m.SetRows(0), invalid_argument);
  ASSERT_THROW(m.SetRows(-1), invalid_argument);
  ASSERT_THROW(m.SetCols(0), invalid_argument);
  ASSERT_THROW(m.SetCols(-1), invalid_argument);
  ASSERT_THROW(m(-1, 1), range_error);
  ASSERT_THROW(m(1, 5), range_error);
}

TEST(EqMatrixTest, TestTrue) {
  S21Matrix m1(SetEOne(5)), m2(SetEOne(5));
  ASSERT_EQ(m1 == m2, true);
  SetOnes(m1);
  SetOnes(m2);
  m2.SetRows(8);
  m1.SetRows(8);
  ASSERT_EQ(m1 == m2, true);
  m1 += m2;
  m2 *= 2;
  ASSERT_EQ(m1 == m2, true);
}

TEST(EqMatrixTest, TestFalse) {
  S21Matrix m1(SetEOne(5)), m2(SetEOne(6));
  ASSERT_EQ(m1 == m2, false);
  SetOnes(m1);
  SetOnes(m2);
  m2.SetRows(8);
  m1.SetRows(8);
  ASSERT_EQ(m1 == m2, false);
  m2.SetCols(8);
  m1.SetCols(8);
  ASSERT_EQ(m1 == m2, false);
}

TEST(SumMatrixTest, sum1) {
  S21Matrix m1(5, 6), m2(5, 6);
  SetOnes(m1);
  SetOnes(m2);
  S21Matrix result = m1 + m2;
  m1.SumMatrix(m2);
  ASSERT_EQ(m1 == result, true);
}

TEST(SumMatrixTest, sum2) {
  S21Matrix m1(1, 6), m2(1, 6);
  for (int i = 0; i < m1.GetCols(); i++) {
    m1(0, i) = i;
    m2(0, 5 - i) = i;
  }
  m1 += m2;
  for (int i = 0; i < m1.GetCols(); i++) ASSERT_EQ(m1(0, i), 5);
}

TEST(SumMatrixTest, sumERR) {
  S21Matrix m1(1, 6), m2(6, 1);
  for (int i = 0; i < m1.GetCols(); i++) {
    m1(0, i) = i;
    m2(5 - i, 0) = i;
  }
  ASSERT_THROW(m1 += m2, domain_error);
}

TEST(SubMatrixTest, sub1) {
  S21Matrix m1(5, 6), m2(5, 6);
  SetOnes(m1);
  SetOnes(m2);
  S21Matrix result = m1 - m2;
  m1.SubMatrix(m2);
  ASSERT_EQ(m1 == result, true);
}

TEST(SubMatrixTest, sub2) {
  S21Matrix m1(1, 6), m2(1, 6);
  for (int i = 0; i < m1.GetCols(); i++) {
    m1(0, i) = i;
    m2(0, i) = i + 5;
  }
  m1 -= m2;
  for (int i = 0; i < m1.GetCols(); i++) ASSERT_EQ(m1(0, i), -5);
}

TEST(SubMatrixTest, subERR) {
  S21Matrix m1(1, 6), m2(6, 1);
  for (int i = 0; i < m1.GetCols(); i++) {
    m1(0, i) = i;
    m2(5 - i, 0) = i;
  }
  ASSERT_THROW(m1 -= m2, domain_error);
}

TEST(MulNumberTest, mnum1) {
  S21Matrix m1(5, 6), m2(5, 6);
  SetOnes(m1);
  SetOnes(m2);
  S21Matrix result = m1 * 5.5;
  m1.MulNumber(5.5);
  ASSERT_EQ(m1 == result, true);
  result = 5.5 * m2;
  ASSERT_EQ(m1 == result, true);
}

TEST(MulNumberTest, mnum2) {
  S21Matrix m1(1, 6), m2(1, 6);
  for (int i = 0; i < m1.GetCols(); i++) {
    m1(0, i) = i;
    m2(0, i) = i * 3.2;
  }
  m1 *= 3.2;
  ASSERT_EQ(m1 == m2, true);
}

TEST(MultMatrixTest, MxM1) {
  S21Matrix m1(2, 2), m2(SetEOne(2));
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  S21Matrix res = m1 * m2;
  ASSERT_EQ(m1 == res, true);
  SetOnes(m2);
  res *= m1;
  res *= m2;
  m1.MulMatrix(m1);
  m1.MulMatrix(m2);
  ASSERT_EQ(m1 == res, true);
}

// (1 2)   (1 2)   (7  10) | (7  10)   (1 1)   (17 17)
//       *       =         |         *       =
// (3 4)   (3 4)   (15 22) | (15 22)   (1 1)   (37 37)

TEST(MultMatrixTest, MxM2) {
  S21Matrix m1(8, 2), m2(SetEOne(2)), res;
  SetOnes(m1);
  m1(0, 0) = 8;
  m1(0, 1) = 2;
  m1(1, 0) = 6;
  m1(1, 1) = 4;
  res = m1 * m2;
  ASSERT_EQ(m1 == res, true);
  SetOnes(m2);
  res *= m2;
  m1.MulMatrix(m2);
  ASSERT_EQ(m1 == res, true);
}

TEST(MultMatrixTest, MxM_ERR) {
  S21Matrix m1(8, 2), m2(3, 1), res;
  SetOnes(m1);
  SetOnes(m2);
  ASSERT_THROW(res = m1 * m2, domain_error);
}

TEST(CommonFuncTest, matrix3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 3;
  m(0, 1) = -5;
  m(0, 2) = 6;
  m(1, 0) = -7;
  m(1, 1) = 8;
  m(1, 2) = 2;
  m(2, 0) = 3;
  m(2, 1) = 1;
  m(2, 2) = -1;
  ASSERT_EQ(m.Determinant(), -211.);
  S21Matrix check(3, 3);
  check(0, 0) = 10. / 211.;
  check(0, 1) = -1. / 211.;
  check(0, 2) = 58. / 211.;
  check(1, 0) = 1. / 211.;
  check(1, 1) = 21. / 211.;
  check(1, 2) = 48. / 211.;
  check(2, 0) = 31. / 211.;
  check(2, 1) = 18. / 211.;
  check(2, 2) = 11. / 211.;
  ASSERT_EQ(m.InverseMatrix() == check, true);
}

TEST(CommonFuncTest, BigMatrix) {
  S21Matrix m1(7, 7);
  SetOnes(m1);
  m1 += SetEOne(7);
  S21Matrix result = m1.InverseMatrix();
  for (int i = 0; i < result.GetRows(); i++)
    for (int j = 0; j < result.GetCols(); j++)
      if (i == j)
        ASSERT_EQ(result(i, j), 7. / 8.);
      else
        ASSERT_EQ(result(i, j), -1. / 8.);
}

TEST(CommonFuncTest, Error) {
  S21Matrix m(2, 3);
  SetOnes(m);
  ASSERT_THROW(m.Determinant(), domain_error);
  ASSERT_THROW(m.CalcComplements(), domain_error);
  m.SetCols(2);
  ASSERT_THROW(m.InverseMatrix(), domain_error);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}