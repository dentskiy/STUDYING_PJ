#include <stack>

#include "../test.h"

TEST(StackTests, TestDefaultConstructor1) {
  s21::stack<int> s1;
  std::stack<int> s2;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(StackTests, TestDefaultConstructor2) {
  s21::stack<double> s1;
  std::stack<double> s2;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(StackTests, TestInitializerListConstructor1) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2;

  s2.push(1);
  s2.push(2);
  s2.push(3);

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.top(), s2.top());
}

TEST(StackTests, TestInitializerListConstructor2) {
  s21::stack<double> s1 = {1.0, 2.0, 3.0};
  std::stack<double> s2;

  s2.push(1.0);
  s2.push(2.0);
  s2.push(3.0);

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.top(), s2.top());
}

TEST(StackTests, TestInitializerListConstructor3) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.top(), s2.top());
}

TEST(StackTests, TestInitializerListConstructor4) {
  s21::stack<double> s1 = {1.0, 2.0, 3.0};
  std::stack<double> s2({1.0, 2.0, 3.0});

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.top(), s2.top());
}

TEST(StackTests, TestCopyConstructor1) {
  s21::stack<int> s1 = {1, 2, 3};
  s21::stack<int> s2(s1);
  std::stack<int> s3({1, 2, 3});
  std::stack<int> s4(s3);

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.size(), s3.size());
  EXPECT_EQ(s1.size(), s4.size());
  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.empty(), s3.empty());
  EXPECT_EQ(s1.empty(), s4.empty());
}

TEST(StackTests, TestCopyConstructor2) {
  s21::stack<int> s1{1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  s21::stack<int> s3;
  std::stack<int> s4;

  s3 = s1;
  s4 = s2;

  EXPECT_EQ(s1.size(), s3.size());
  EXPECT_EQ(s2.size(), s4.size());
  EXPECT_FALSE(s1.empty());
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s1.top(), s3.top());
  EXPECT_EQ(s2.top(), s4.top());
}

TEST(StackTests, TestMoveConstructor1) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});
  s21::stack<int> s3;
  std::stack<int> s4;

  s3 = std::move(s1);
  s4 = std::move(s2);

  EXPECT_EQ(s3.top(), s4.top());
  EXPECT_EQ(s3.size(), s4.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(StackTests, TestMoveConstructor2) {
  s21::stack<double> s1 = {1.0, 2.0, 3.0};
  std::stack<double> s2({1.0, 2.0, 3.0});
  s21::stack<double> s3;
  std::stack<double> s4;

  s3 = std::move(s1);
  s4 = std::move(s2);

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s3.size(), s4.size());
  EXPECT_EQ(s3.top(), s4.top());
}

TEST(StackTests, TestAssignmentOperator1) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});
  s21::stack<int> s3;
  std::stack<int> s4;

  s3 = s1;
  s4 = s2;

  EXPECT_EQ(s3.top(), s4.top());
  EXPECT_EQ(s3.size(), s4.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(StackTests, TestTopMethod1) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  EXPECT_EQ(s1.top(), s2.top());
}

TEST(StackTests, TestTopMethod2) {
  s21::stack<double> s1 = {1.0, 2.0, 3.0};
  std::stack<double> s2({1.0, 2.0, 3.0});

  s1.pop();
  s2.pop();

  EXPECT_EQ(s1.top(), s2.top());
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(StackTests, TestTopMethod3) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  s1.push(4);
  s2.push(4);
  s1.push(5);
  s2.push(5);

  EXPECT_EQ(s1.top(), s2.top());
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(StackTests, TestEmptyMethod1) {
  s21::stack<int> s1;
  std::stack<int> s2;

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.empty());
}

TEST(StackTests, TestEmptyMethod2) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  EXPECT_FALSE(s1.empty());
  EXPECT_FALSE(s2.empty());
}

TEST(StackTests, TestSizeMethod1) {
  s21::stack<int> s1;
  std::stack<int> s2;

  EXPECT_EQ(s1.size(), 0);
  EXPECT_EQ(s2.size(), 0);
}

TEST(StackTests, TestSizeMethod2) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
}

TEST(StackTests, TestSizeMethod3) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  s1.pop();
  s2.pop();

  EXPECT_EQ(s1.size(), 2);
  EXPECT_EQ(s2.size(), 2);
}

TEST(StackTests, TestSizeMethod4) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  s1.push(4);
  s2.push(4);
  s1.push(5);
  s2.push(5);

  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s2.size(), 5);
}

TEST(StackTests, TestPushMethod1) {
  s21::stack<int> s1;
  std::stack<int> s2;

  s1.push(1);
  s2.push(1);
  s1.push(2);
  s2.push(2);
  s1.push(3);
  s2.push(3);

  EXPECT_EQ(s1.top(), s2.top());
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(StackTests, TestPopMethod1) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  s1.pop();
  s2.pop();

  EXPECT_EQ(s1.top(), s2.top());
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(StackTests, TestPopMethod2) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  s1.pop();
  s2.pop();
  s1.pop();
  s2.pop();

  EXPECT_EQ(s1.top(), s2.top());
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(StackTests, TestPopMethod3) {
  s21::stack<int> s1 = {1, 2, 3};
  std::stack<int> s2({1, 2, 3});

  s1.pop();
  s1.pop();
  s2.pop();
  s2.pop();

  EXPECT_EQ(s1.top(), 1);
  EXPECT_EQ(s2.size(), 1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(StackTests, TestSwapMethod1) {
  s21::stack<int> s1 = {1, 2, 3};
  s21::stack<int> s2 = {3, 2, 1};

  s1.swap(s2);

  EXPECT_EQ(s1.top(), 1);
  EXPECT_EQ(s2.top(), 3);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(StackTests, TestSwapMethod2) {
  s21::stack<int> s1 = {1, 2, 3};
  s21::stack<int> s2 = {3, 2, 1};

  s1.swap(s2);
  s2.swap(s1);

  EXPECT_EQ(s1.top(), 3);
  EXPECT_EQ(s2.top(), 1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(StackTests, TestSwapMethod3) {
  s21::stack<int> s1 = {1, 2, 3};
  s21::stack<int> s2;
  std::stack<int> s3({1, 2, 3});
  std::stack<int> s4;

  s1.swap(s2);
  s3.swap(s4);

  EXPECT_EQ(s2.top(), 3);
  EXPECT_EQ(s4.top(), 3);
  EXPECT_EQ(s2.size(), s4.size());
  EXPECT_EQ(s1.empty(), s3.empty());
}

TEST(StackTests, TestInsertManyFrontMethod1) {
  s21::stack<int> s1;
  EXPECT_TRUE(s1.empty());

  s1.insert_many_front(1, 2, 3);

  EXPECT_EQ(s1.top(), 3);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_FALSE(s1.empty());
}