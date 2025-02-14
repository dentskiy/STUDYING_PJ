#include <queue>

#include "../test.h"

TEST(QueueTests, TestDefaultConstructor1) {
  s21::queue<int> q1;
  std::queue<int> q2;

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.empty(), q2.empty());
}

TEST(QueueTests, TestDefaultConstructor2) {
  s21::queue<double> q1;
  std::queue<double> q2;

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.empty(), q2.empty());
}

TEST(QueueTests, TestInitializerListConstructor1) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.empty(), q2.empty());
}

TEST(QueueTests, TestInitializerListConstructor2) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.empty(), q2.empty());
}

TEST(QueueTests, TestInitializerListConstructor3) {
  s21::queue<int> q1{1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.empty(), q2.empty());
}

TEST(QueueTests, TestCopyConstructor1) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2(q1);
  std::queue<int> q3({1, 2, 3});
  std::queue<int> q4(q3);

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.size(), q3.size());
  EXPECT_EQ(q1.size(), q4.size());
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.empty(), q3.empty());
  EXPECT_EQ(q1.empty(), q4.empty());
}

TEST(QueueTests, TestCopyConstructor2) {
  s21::queue<int> q1{1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  s21::queue<int> q3 = q1;
  std::queue<int> q4 = q2;

  EXPECT_EQ(q1.size(), q3.size());
  EXPECT_EQ(q2.size(), q4.size());
  EXPECT_FALSE(q1.empty());
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(q1.front(), q3.front());
  EXPECT_EQ(q1.back(), q3.back());
  EXPECT_EQ(q2.front(), q4.front());
  EXPECT_EQ(q2.back(), q4.back());
}

TEST(QueueTests, TestMoveConstructor1) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});
  s21::queue<int> q3;
  std::queue<int> q4;

  q3 = std::move(q1);
  q4 = std::move(q2);

  EXPECT_EQ(q3.front(), 1);
  EXPECT_EQ(q3.back(), 3);
  EXPECT_EQ(q4.front(), 1);
  EXPECT_EQ(q4.back(), 3);
  EXPECT_TRUE(q1.empty());
  EXPECT_TRUE(q2.empty());
}

TEST(QueueTests, TestMoveConstructor2) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});
  s21::queue<double> q3;
  std::queue<double> q4;

  q3 = std::move(q1);
  q4 = std::move(q2);

  EXPECT_EQ(q3.front(), q4.front());
  EXPECT_EQ(q3.back(), q4.back());
  EXPECT_EQ(q1.empty(), q2.empty());
}

TEST(QueueTests, TestAssignmentOperator1) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});
  s21::queue<int> q3;
  std::queue<int> q4;

  q3 = q1;
  q4 = q2;

  EXPECT_EQ(q3.front(), q4.front());
  EXPECT_EQ(q3.back(), q4.back());
  EXPECT_EQ(q1.empty(), q2.empty());
}

TEST(QueueTests, TestFrontMethod1) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  EXPECT_EQ(q1.front(), q2.front());
}

TEST(QueueTests, TestFrontMethod2) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  EXPECT_EQ(q1.front(), q2.front());
}

TEST(QueueTests, TestFrontMethod3) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.front(), q2.front());
}

TEST(QueueTests, TestFrontMethod4) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.front(), q2.front());
}

TEST(QueueTests, TestFrontMethod5) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  q1.pop();
  q2.pop();

  q1.push(4);
  q2.push(4);

  EXPECT_EQ(q1.front(), q2.front());
}

TEST(QueueTests, TestFrontMethod6) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  q1.pop();
  q2.pop();

  q1.push(4.0);
  q2.push(4.0);

  EXPECT_EQ(q1.front(), q2.front());
}

TEST(QueueTests, TestFrontMethod7) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  q1.pop();
  q2.pop();

  q1.push(4);
  q2.push(4);

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.front(), q2.front());
}

TEST(QueueTests, TestFrontMethod8) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  q1.pop();
  q2.pop();

  q1.push(4.0);
  q2.push(4.0);

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.front(), q2.front());
}

TEST(QueueTests, TestFrontMethod9) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  EXPECT_EQ(q1.front(), q2.front());
  EXPECT_EQ(q1.front(), 1);
  EXPECT_EQ(q2.front(), 1);
}

TEST(QueueTests, TestBackMethod1) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTests, TestBackMethod2) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTests, TestBackMethod3) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTests, TestBackMethod4) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTests, TestBackMethod5) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  q1.pop();
  q2.pop();

  q1.push(4);
  q2.push(4);

  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTests, TestBackMethod6) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  q1.pop();
  q2.pop();

  q1.push(4.0);
  q2.push(4.0);

  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTests, TestBackMethod7) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  q1.pop();
  q2.pop();

  q1.push(4);
  q2.push(4);

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTests, TestBackMethod8) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  q1.pop();
  q2.pop();

  q1.push(4.0);
  q2.push(4.0);

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTests, TestEmptyMethod1) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_FALSE(q1.empty());
  EXPECT_FALSE(q2.empty());
}

TEST(QueueTests, TestEmptyMethod2) {
  s21::queue<double> q1;
  std::queue<double> q2;

  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_TRUE(q1.empty());
  EXPECT_TRUE(q2.empty());
}

TEST(QueueTests, TestSizeMethod1) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q2.size(), 3);
}

TEST(QueueTests, TestSizeMethod2) {
  s21::queue<double> q1;
  std::queue<double> q2;

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.size(), 0);
  EXPECT_EQ(q2.size(), 0);
}

TEST(QueueTests, TestSizeMethod3) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q2.size(), 2);
}

TEST(QueueTests, TestPushMethod1) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  q1.push(4);
  q2.push(4);

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.size(), 4);
  EXPECT_EQ(q2.size(), 4);
}

TEST(QueueTests, TestPushMethod2) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  q1.push(4.0);
  q2.push(4.0);

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.size(), 4);
  EXPECT_EQ(q2.size(), 4);
}

TEST(QueueTests, TestPushMethod3) {
  s21::queue<int> q1;
  std::queue<int> q2;

  q1.push(1);
  q1.push(2);
  q1.push(3);

  q2.push(1);
  q2.push(2);
  q2.push(3);

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q1.empty(), q2.empty());
}

TEST(QueueTests, TestPopMethod1) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q2.size(), 2);
}

TEST(QueueTests, TestPopMethod2) {
  s21::queue<double> q1 = {1.0, 2.0, 3.0};
  std::queue<double> q2({1.0, 2.0, 3.0});

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q2.size(), 2);
  EXPECT_EQ(q1.empty(), q2.empty());
}

TEST(QueueTests, TestPopMethod3) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q2({1, 2, 3});

  q1.pop();
  q1.pop();
  q1.pop();

  q2.pop();
  q2.pop();
  q2.pop();

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.size(), 0);
  EXPECT_EQ(q2.size(), 0);
  EXPECT_EQ(q1.empty(), q2.empty());
}

TEST(QueueTests, TestSwapMethod1) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2;
  std::queue<int> q3({1, 2, 3});
  std::queue<int> q4;

  q2.swap(q1);
  q4.swap(q3);

  EXPECT_EQ(q1.size(), 0);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q3.size(), 0);
  EXPECT_EQ(q4.size(), 3);
  EXPECT_TRUE(q1.empty());
  EXPECT_TRUE(q3.empty());
}

TEST(QueueTests, TestSwapMethod2) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2 = {3, 2, 1};
  std::queue<int> q3({1, 2, 3});
  std::queue<int> q4({3, 2, 1});

  q1.swap(q2);
  q3.swap(q4);

  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q3.size(), 3);
  EXPECT_EQ(q4.size(), 3);

  EXPECT_EQ(q1.front(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q3.front(), 3);
  EXPECT_EQ(q4.front(), 1);
  EXPECT_EQ(q1.back(), 1);
  EXPECT_EQ(q2.back(), 3);
  EXPECT_EQ(q3.back(), 1);
  EXPECT_EQ(q4.back(), 3);

  EXPECT_EQ(q1.front(), q2.back());
  EXPECT_EQ(q3.front(), q4.back());
}

TEST(QueueTests, TestInsertManyBackMethod1) {
  s21::queue<int> q1;
  q1.insert_many_back(1, 2, 3);

  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q1.front(), 1);
  EXPECT_EQ(q1.back(), 3);
}