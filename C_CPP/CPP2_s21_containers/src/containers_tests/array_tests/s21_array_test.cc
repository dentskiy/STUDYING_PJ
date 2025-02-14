#include "../test.h"
#include "array"

TEST(ArrayTest, TestDefaultArrayConstructor1) {
  s21::array<int, 3> a1;
  std::array<int, 3> a2;

  EXPECT_EQ(a1.size(), a2.size());
  EXPECT_EQ(a1.empty(), a2.empty());

  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], 0);
  }
}

TEST(ArrayTest, TestDefaultArrayConstructor2) {
  s21::array<double, 3> a1;
  std::array<double, 3> a2;

  EXPECT_EQ(a1.size(), a2.size());
  EXPECT_EQ(a1.empty(), a2.empty());

  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], 0);
  }
}

TEST(ArrayTest, TestDefaultArrayConstructor3) {
  s21::array<int, 0> a1;
  std::array<int, 0> a2;

  EXPECT_EQ(a1.size(), a2.size());
  EXPECT_EQ(a1.empty(), a2.empty());
}

TEST(ArrayTest, TestInitializerListConstructor1) {
  s21::array<int, 3> a1{1, 2, 3};
  std::array<int, 3> a2{1, 2, 3};

  EXPECT_EQ(a1.size(), a2.size());
  EXPECT_EQ(a1.empty(), a2.empty());

  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], i + 1);
    EXPECT_EQ(a2[i], i + 1);
    EXPECT_EQ(a1[i], a2[i]);
  }
}

TEST(ArrayTest, TestInitializerListConstructor2) {
  s21::array<double, 3> a1 = {};
  std::array<double, 3> a2 = {};

  EXPECT_EQ(a1.size(), a2.size());
  EXPECT_EQ(a1.empty(), a2.empty());

  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], 0);
    EXPECT_EQ(a2[i], 0);
  }
}

TEST(ArrayTest, TestInitializerListConstructor3) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  std::array<int, 5> a2 = {1, 2, 3, 4, 5};

  EXPECT_EQ(a1.size(), a2.size());
  EXPECT_EQ(a1.empty(), a2.empty());
  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], i + 1);
    EXPECT_EQ(a2[i], i + 1);
    EXPECT_EQ(a1[i], a2[i]);
  }
}

TEST(ArrayTest, TestCopyConstructor1) {
  s21::array<int, 3> a1{1, 2, 3};
  s21::array<int, 3> a2(a1);
  std::array<int, 3> a3{1, 2, 3};
  std::array<int, 3> a4(a3);

  EXPECT_EQ(a1.size(), a2.size());
  EXPECT_EQ(a1.size(), a3.size());
  EXPECT_EQ(a1.size(), a4.size());

  EXPECT_EQ(a1.empty(), a2.empty());
  EXPECT_EQ(a1.empty(), a3.empty());
  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], a2[i]);
    EXPECT_EQ(a1[i], a3[i]);
    EXPECT_EQ(a1[i], a4[i]);
  }
}

TEST(ArrayTest, TestCopyConstructor2) {
  s21::array<int, 3> a1 = {1};
  std::array<int, 3> a2 = {1};
  s21::array<int, 3> a3(a1);
  std::array<int, 3> a4(a2);

  EXPECT_EQ(a1.size(), a2.size());
  EXPECT_EQ(a1.size(), a3.size());
  EXPECT_EQ(a1.empty(), a2.empty());
  EXPECT_EQ(a1.empty(), a3.empty());
  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], a2[i]);
    EXPECT_EQ(a1[i], a3[i]);
    EXPECT_EQ(a1[i], a4[i]);
  }
}

TEST(ArrayTest, TestMoveConstructor1) {
  s21::array<int, 3> a1{1, 2, 3};
  s21::array<int, 3> a2(std::move(a1));
  std::array<int, 3> a3{1, 2, 3};
  std::array<int, 3> a4(std::move(a3));

  EXPECT_EQ(a1.size(), a2.size());
  EXPECT_EQ(a1.size(), a3.size());
  EXPECT_EQ(a1.size(), a4.size());
  EXPECT_EQ(a1.empty(), a2.empty());
  EXPECT_EQ(a1.empty(), a3.empty());
  EXPECT_EQ(a1.empty(), a4.empty());
  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], a2[i]);
    EXPECT_EQ(a1[i], a3[i]);
    EXPECT_EQ(a1[i], a4[i]);
  }
}

TEST(ArrayTest, TestMoveConstructor2) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  size_t tmp_size = a1.size();
  s21::array<int, 5> a2(std::move(a1));

  EXPECT_EQ(a2.size(), tmp_size);
  EXPECT_EQ(a1.size(), a2.size());

  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a2[i], i + 1);
  }
}

TEST(ArrayTest, TestOperatorEqual1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> a2;

  a2 = a1;

  EXPECT_EQ(a1.size(), a2.size());
  EXPECT_EQ(a1.empty(), a2.empty());
  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], a2[i]);
  }
}

TEST(ArrayTest, TestOperatorEqual2) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> a2 = {7, 8, 9, 10, 11};

  a1 = std::move(a2);

  EXPECT_EQ(a1.size(), 5);

  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], i + 7);
  }
}

TEST(ArrayTest, TestOperatorBracket1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};

  for (size_t i = 0; i != a1.size(); i++) {
    EXPECT_EQ(a1[i], i + 1);
  }
}

TEST(ArrayTest, TestOperatorBracket2) {
  s21::array<std::string, 3> a1 = {"a", "b", "c"};
  EXPECT_EQ(a1[0], "a");
  EXPECT_EQ(a1[1], "b");
  EXPECT_EQ(a1[2], "c");
}

TEST(ArrayTest, TestOperatorBracket3) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1[0], 1);
  EXPECT_EQ(a1[1], 2);
  EXPECT_EQ(a1[2], 3);
  EXPECT_EQ(a1[3], 4);
  EXPECT_EQ(a1[4], 5);
}

TEST(ArrayTest, TestOperatorBracket4) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> a2 = {6, 7, 8, 9, 10};

  a1[0] = 6;
  a1[1] = 7;
  a1[2] = 8;
  a1[3] = 9;
  a1[4] = 10;

  EXPECT_EQ(a1[0], 6);
  EXPECT_EQ(a1[1], 7);
  EXPECT_EQ(a1[2], 8);
  EXPECT_EQ(a1[3], 9);
  EXPECT_EQ(a1[4], 10);
}
// const
TEST(ArrayTest, TestOperatorBracket5) {
  const s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1[0], 1);
  EXPECT_EQ(a1[1], 2);
  EXPECT_EQ(a1[2], 3);
  EXPECT_EQ(a1[3], 4);
  EXPECT_EQ(a1[4], 5);
}

// operator[] exception
TEST(ArrayTest, TestOperatorBracket6) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_THROW(a1[-1], std::out_of_range);
}

// const operator[] exception
TEST(ArrayTest, TestOperatorBracket7) {
  const s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_THROW(a1[-1], std::out_of_range);
}

TEST(ArrayTest, TestFrontMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.front(), 1);
}

TEST(ArrayTest, TestFrontMethod2) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.front(), 1);
  a1.front() = 6;
  EXPECT_EQ(a1.front(), 6);
}
// const
TEST(ArrayTest, TestFrontMethod3) {
  const s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.front(), 1);
}

TEST(ArrayTest, TestBackMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.back(), 5);
}

TEST(ArrayTest, TestBackMethod2) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.back(), 5);
  a1.back() = 6;
  EXPECT_EQ(a1.back(), 6);
}

// const
TEST(ArrayTest, TestBackMethod3) {
  const s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.back(), 5);
}

TEST(ArrayTest, TestAtMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.at(0), 1);
  EXPECT_EQ(a1.at(1), 2);
  EXPECT_EQ(a1.at(2), 3);
  EXPECT_EQ(a1.at(3), 4);
  EXPECT_EQ(a1.at(4), 5);
}

TEST(ArrayTest, TestAtMethod2) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.at(0), 1);
  EXPECT_EQ(a1.at(1), 2);
  EXPECT_EQ(a1.at(2), 3);
  EXPECT_EQ(a1.at(3), 4);
  EXPECT_EQ(a1.at(4), 5);
  a1.at(0) = 6;
  a1.at(1) = 7;
  a1.at(2) = 8;
  a1.at(3) = 9;
  EXPECT_EQ(a1.at(0), 6);
  EXPECT_EQ(a1.at(1), 7);
  EXPECT_EQ(a1.at(2), 8);
  EXPECT_EQ(a1.at(3), 9);
}

TEST(ArrayTest, TestAtMethod3) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < a1.size(); i++) {
    EXPECT_EQ(a1.at(i), i + 1);
  }
}

TEST(ArrayTest, TestAtMethod4) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < a1.size(); i++) {
    EXPECT_EQ(a1.at(i), i + 1);
  }
  a1.at(0) = 6;
  a1.at(1) = 7;
  a1.at(2) = 8;
  a1.at(3) = 9;
  a1.at(4) = 10;

  for (size_t i = 0; i < a1.size(); i++) {
    EXPECT_EQ(a1.at(i), i + 6);
  }
}

// at exception
TEST(ArrayTest, TestAtMethod5) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_THROW(a1.at(5), std::out_of_range);
}

TEST(ArrayTest, TestDataMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(a1.data()[0], 1);
  EXPECT_EQ(a1.data()[1], 2);
  EXPECT_EQ(a1.data()[2], 3);
  EXPECT_EQ(a1.data()[3], 4);
  EXPECT_EQ(a1.data()[4], 5);
}

TEST(ArrayTest, TestDataMethod2) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(a1.data()[0], 1);
  EXPECT_EQ(a1.data()[1], 2);
  EXPECT_EQ(a1.data()[2], 3);
  EXPECT_EQ(a1.data()[3], 4);
  EXPECT_EQ(a1.data()[4], 5);

  a1.data()[0] = 6;
  a1.data()[1] = 7;
  a1.data()[2] = 8;
  a1.data()[3] = 9;

  EXPECT_EQ(a1.data()[0], 6);
  EXPECT_EQ(a1.data()[1], 7);
  EXPECT_EQ(a1.data()[2], 8);
  EXPECT_EQ(a1.data()[3], 9);
}

// const
TEST(ArrayTest, TestDataMethod3) {
  const s21::array<int, 5> a1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(a1.data()[0], 1);
  EXPECT_EQ(a1.data()[1], 2);
  EXPECT_EQ(a1.data()[2], 3);
  EXPECT_EQ(a1.data()[3], 4);
  EXPECT_EQ(a1.data()[4], 5);
}

TEST(ArrayTest, TestBeginMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(*a1.begin(), 1);
  EXPECT_EQ(*(a1.begin() + 1), 2);
  EXPECT_EQ(*(a1.begin() + 2), 3);
  EXPECT_EQ(*(a1.begin() + 3), 4);
  EXPECT_EQ(*(a1.begin() + 4), 5);
}

TEST(ArrayTest, TestBeginMethod2) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  *a1.begin() = 6;

  EXPECT_EQ(*a1.begin(), 6);
  EXPECT_EQ(*(a1.begin() + 1), 2);
  EXPECT_EQ(*(a1.begin() + 2), 3);
  EXPECT_EQ(*(a1.begin() + 3), 4);
  EXPECT_EQ(*(a1.begin() + 4), 5);
}

// end
TEST(ArrayTest, TestEndMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(*(a1.end() - 1), 5);
  EXPECT_EQ(*(a1.end() - 2), 4);
  EXPECT_EQ(*(a1.end() - 3), 3);
  EXPECT_EQ(*(a1.end() - 4), 2);
  EXPECT_EQ(*(a1.end() - 5), 1);
}

TEST(ArrayTest, TestEndMethod2) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  *(a1.end() - 1) = 6;

  EXPECT_EQ(*(a1.end() - 1), 6);
  EXPECT_EQ(*(a1.end() - 2), 4);
  EXPECT_EQ(*(a1.end() - 3), 3);
  EXPECT_EQ(*(a1.end() - 4), 2);
  EXPECT_EQ(*(a1.end() - 5), 1);
}

TEST(ArrayTest, TestCbeginMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  auto c1 = a1.cbegin();
  EXPECT_EQ(*c1, 1);
}

TEST(ArrayTest, TestCendMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  auto c1 = a1.cend() - 1;
  EXPECT_EQ(*c1, 5);
}

// empty
TEST(ArrayTest, TestEmptyMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_FALSE(a1.empty());
}
TEST(ArrayTest, TestEmptyMethod2) {
  s21::array<int, 0> a1;
  EXPECT_TRUE(a1.empty());
}

// size
TEST(ArrayTest, TestSizeMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.size(), 5);
}

TEST(ArrayTest, TestSizeMethod2) {
  s21::array<int, 0> a1;
  EXPECT_EQ(a1.size(), 0);
}

TEST(ArrayTest, TestSizeMethod3) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.size(), 5);
  a1.at(0) = 6;
  a1.at(1) = 7;
  a1.at(2) = 8;
  a1.at(3) = 9;
  a1.at(4) = 10;
  EXPECT_EQ(a1.size(), 5);
}

// max_size
TEST(ArrayTest, TestMaxSizeMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.max_size(), 5);
}

TEST(ArrayTest, TestMaxSizeMethod2) {
  s21::array<int, 0> a1;
  EXPECT_EQ(a1.max_size(), 0);
}

TEST(ArrayTest, TestMaxSizeMethod3) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a1.max_size(), 5);
  a1.at(0) = 6;
  a1.at(1) = 7;
  a1.at(2) = 8;
  a1.at(3) = 9;
  a1.at(4) = 10;
  EXPECT_EQ(a1.max_size(), 5);
}

// swap
TEST(ArrayTest, TestSwapMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> a2 = {6, 7, 8, 9, 10};
  a1.swap(a2);

  EXPECT_EQ(a1.at(0), 6);
  EXPECT_EQ(a1.at(1), 7);
  EXPECT_EQ(a1.at(2), 8);
  EXPECT_EQ(a1.at(3), 9);
  EXPECT_EQ(a1.at(4), 10);
}

// fill
TEST(ArrayTest, TestFillMethod1) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  a1.fill(6);

  EXPECT_EQ(a1.at(0), 6);
  EXPECT_EQ(a1.at(1), 6);
  EXPECT_EQ(a1.at(2), 6);
  EXPECT_EQ(a1.at(3), 6);
  EXPECT_EQ(a1.at(4), 6);
}

TEST(ArrayTest, TestFillMethod2) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};
  a1.fill(6);
  a1.at(0) = 7;
  a1.at(1) = 8;
  a1.at(2) = 9;
  a1.at(3) = 10;
  a1.at(4) = 11;

  EXPECT_EQ(a1.at(0), 7);
  EXPECT_EQ(a1.at(1), 8);
  EXPECT_EQ(a1.at(2), 9);
  EXPECT_EQ(a1.at(3), 10);
}

TEST(ArrayTest, TestFillMethod3) {
  s21::array<int, 5> a1 = {1, 2, 3, 4, 5};

  a1.fill(0);
  EXPECT_EQ(a1.at(0), 0);
  EXPECT_EQ(a1.at(1), 0);
  EXPECT_EQ(a1.at(2), 0);
  EXPECT_EQ(a1.at(3), 0);
  EXPECT_EQ(a1.at(4), 0);

  EXPECT_EQ(a1.size(), 5);
  EXPECT_FALSE(a1.empty());
}