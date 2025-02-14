#include <set>

#include "../test.h"

TEST(SetTests, TestDefaultConstructor1) {
  s21::set<int> s1;
  std::set<int> s2;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(SetTests, TestDefaultConstructor2) {
  s21::set<double> s1;
  std::set<double> s2;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(SetTests, TestInitializerListConstructor1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  std::set<int> s2 = {1, 2, 3, 4, 5};

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());

  s21::set<int>::iterator my_set_iter;
  std::set<int>::iterator std_set_iter;

  for (my_set_iter = s1.begin(), std_set_iter = s2.begin();
       my_set_iter != s1.end(); ++my_set_iter, ++std_set_iter) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
  }

  //   for (my_set_iter = s1.end(), std_set_iter = s2.end();
  //        my_set_iter != s1.begin(); --my_set_iter, --std_set_iter) {
  //     EXPECT_EQ(*my_set_iter, *std_set_iter);
  //   }
}

TEST(SetTests, TestInitializerListConstructor2) {
  s21::set<double> s1 = {1.1, 2.2, 3.3, 4.4, 5.5};
  std::set<double> s2 = {1.1, 2.2, 3.3, 4.4, 5.5};

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());

  s21::set<double>::iterator my_set_iter;
  std::set<double>::iterator std_set_iter;
  for (my_set_iter = s1.begin(), std_set_iter = s2.begin();
       my_set_iter != s1.end(); ++my_set_iter, ++std_set_iter) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
  }
}

TEST(SetTests, TestCopyConstructor1) {
  s21::set<int> s1 = {5, 4, 3, 2, 1};
  s21::set<int> s2 = s1;
  std::set<int> s3 = {1, 2, 3, 4, 5};
  std::set<int> s4 = s3;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.size(), s4.size());

  EXPECT_EQ(s3.empty(), s4.empty());
  EXPECT_EQ(s3.empty(), s2.empty());

  s21::set<int>::iterator my_set_iter;
  std::set<int>::iterator std_set_iter;

  for (my_set_iter = s1.begin(), std_set_iter = s3.begin();
       my_set_iter != s1.end(); ++my_set_iter, ++std_set_iter) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
  }
}

TEST(SetTests, TestCopy1) {
  s21::set<int> s1 = {5, 4, 3, 2, 1};
  s21::set<int> s2;
  s2 = s1;
  std::set<int> s3 = {1, 2, 3, 4, 5};
  std::set<int> s4;
  s4 = s3;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.size(), s4.size());

  EXPECT_EQ(s3.empty(), s4.empty());
  EXPECT_EQ(s3.empty(), s2.empty());

  s21::set<int>::iterator my_set_iter;
  std::set<int>::iterator std_set_iter;

  for (my_set_iter = s1.begin(), std_set_iter = s3.begin();
       my_set_iter != s1.end(); ++my_set_iter, ++std_set_iter) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
  }
}

TEST(SetTests, TestMoveConstructor1) {
  s21::set<int> s1 = {5, 4, 3, 2, 1};
  s21::set<int> s2;
  s2 = std::move(s1);
  std::set<int> s3 = {1, 2, 3, 4, 5};
  std::set<int> s4;
  s4 = std::move(s3);

  EXPECT_EQ(s1.size(), 0);
  EXPECT_EQ(s2.size(), 5);

  EXPECT_EQ(s1.empty(), s3.empty());
  EXPECT_EQ(s2.empty(), s4.empty());

  s21::set<int>::iterator my_set_iter;
  std::set<int>::iterator std_set_iter;

  for (my_set_iter = s2.begin(), std_set_iter = s4.begin();
       my_set_iter != s2.end(); ++my_set_iter, ++std_set_iter) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
  }
}

TEST(SetTests, TestMoveConstructor2) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  auto tmp_size1 = s1.size();
  s21::set<int> s2 = std::move(s1);

  std::set<int> s3 = {1, 2, 3, 4, 5};
  auto tmp_size3 = s3.size();
  std::set<int> s4 = std::move(s3);

  EXPECT_EQ(s2.size(), tmp_size1);
  EXPECT_EQ(s4.size(), tmp_size3);

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s3.empty());

  s21::set<int>::iterator my_set_iter;
  std::set<int>::iterator std_set_iter;

  for (my_set_iter = s2.begin(), std_set_iter = s4.begin();
       my_set_iter != s2.end(); ++my_set_iter, ++std_set_iter) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
  }
}

TEST(SetTests, TestMoveConstructor3) {
  s21::set<double> s1 = {1.1, 2.2, 3.3, 4.4, 5.5};
  auto tmp_size1 = s1.size();
  s21::set<double> s2 = std::move(s1);

  std::set<double> s3 = {1.1, 2.2, 3.3, 4.4, 5.5};
  auto tmp_size3 = s3.size();
  std::set<double> s4 = std::move(s3);
  EXPECT_EQ(s2.size(), tmp_size1);
  EXPECT_EQ(s4.size(), tmp_size3);

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s3.empty());

  s21::set<double>::iterator my_set_iter;
  std::set<double>::iterator std_set_iter;

  for (my_set_iter = s2.begin(), std_set_iter = s4.begin();
       my_set_iter != s2.end(); ++my_set_iter, ++std_set_iter) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
  }
}

TEST(SetTests, TestIterator1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  std::set<int> s2 = {1, 2, 3, 4, 5};

  s21::set<int>::iterator my_set_iter = s1.begin();
  std::set<int>::iterator std_set_iter = s2.begin();

  EXPECT_EQ(*my_set_iter, *std_set_iter);

  for (int i = 1; i <= 5; ++i) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
    ++my_set_iter;
    ++std_set_iter;
  }
}

TEST(SetTests, TestIterator2) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  std::set<int> s2 = {1, 2, 3, 4, 5};

  s21::set<int>::iterator my_set_iter = s1.begin();
  std::set<int>::iterator std_set_iter = s2.begin();

  EXPECT_EQ(*my_set_iter, *std_set_iter);

  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
    ++my_set_iter;
    ++std_set_iter;
  }

  for (int i = 3; i >= 1; --i) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
    --my_set_iter;
    --std_set_iter;
  }
}

TEST(SetTests, TestIterator3) {
  s21::set<int> s1 = {3, 1, 4, 5, 2};
  std::set<int> s2 = {3, 1, 4, 5, 2};

  s21::set<int>::iterator my_set_iter = s1.begin();
  std::set<int>::iterator std_set_iter = s2.begin();

  EXPECT_EQ(*my_set_iter, *std_set_iter);

  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
    ++my_set_iter;
    ++std_set_iter;
  }

  for (int i = 3; i >= 1; --i) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
    --my_set_iter;
    --std_set_iter;
  }
}

// TEST(SetTests, TestIterator4) {
//   s21::set<int> s1 = {1, 2, 3, 4, 5};
//   std::set<int> s2 = {1, 2, 3, 4, 5};

//   s21::set<int>::iterator my_set_iter = s1.end();
//   std::set<int>::iterator std_set_iter = s2.end();

//   EXPECT_EQ(*my_set_iter, *std_set_iter);

//   for (int i = 1; i <= 5; ++i) {
//     EXPECT_EQ(*my_set_iter, *std_set_iter);
//     --my_set_iter;
//     --std_set_iter;
//   }
// }

TEST(SetTests, TestIterator5) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  std::set<int> s2 = {1, 2, 3, 4, 5};

  s21::set<int>::iterator my_set_iter = s1.begin();
  std::set<int>::iterator std_set_iter = s2.begin();
  my_set_iter--;
  std_set_iter--;

  EXPECT_EQ(my_set_iter, s1.end());
  EXPECT_EQ(std_set_iter, s2.end());
}

TEST(SetTests, TestMethodInsert1) {
  s21::set<int> s1;
  std::set<int> s2;

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());

  s1.insert(1);
  s1.insert(2);
  s1.insert(3);

  s2.insert(1);
  s2.insert(2);
  s2.insert(3);

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());

  s21::set<int>::iterator my_set_iter;
  std::set<int>::iterator std_set_iter;

  for (my_set_iter = s1.begin(), std_set_iter = s2.begin();
       my_set_iter != s1.end(); ++my_set_iter, ++std_set_iter) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
  }
}

TEST(SetTests, TestMethodClear1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  std::set<int> s2 = {1, 2, 3, 4, 5};

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());

  s1.clear();
  s2.clear();

  EXPECT_EQ(s1.empty(), s2.empty());

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.empty());
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(SetTests, TestMethodInsert2) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_pr = my_set.insert("best");
  auto orig_pr = orig_set.insert("best");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
  my_pr = my_set.insert("is");
  orig_pr = orig_set.insert("is");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
}

TEST(SetTests, TestMethodErase1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());
  auto it = s1.begin()++;
  it++;
  it++;
  it++;
  s1.erase(it);
  auto it2 = s2.begin()++;
  it2++;
  it2++;
  it2++;
  s2.erase(it2);

  while (!s1.empty()) {
    EXPECT_EQ(s1.empty(), s2.empty());
    EXPECT_EQ(s1.size(), s2.size());
    s1.erase(s1.begin());
    s2.erase(s2.begin());
  }
}

TEST(SetTests, TestMethodSwap1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  auto tmp_size1 = s1.size();
  s21::set<int> s2 = {3, 4, 5};
  auto tmp_size2 = s2.size();

  s1.swap(s2);

  EXPECT_EQ(s1.size(), tmp_size2);
  EXPECT_EQ(s2.size(), tmp_size1);

  EXPECT_EQ(*s1.begin(), 3);
  EXPECT_EQ(*s2.begin(), 1);
}

TEST(SetTests, TestMethodMerge1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  s21::set<int> s2 = {1};
  s1.merge(s2);

  std::set<int> s3 = {1, 2, 3, 4, 5};
  std::set<int> s4 = {1};
  s3.merge(s4);

  s21::set<int>::iterator my_set_iter;
  std::set<int>::iterator std_set_iter;
  for (my_set_iter = s1.begin(), std_set_iter = s3.begin();
       my_set_iter != s1.end(); ++my_set_iter, ++std_set_iter) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
  }

  EXPECT_EQ(s1.size(), s3.size());
  EXPECT_EQ(s2.size(), s4.size());
}

TEST(SetTests, TestMethodFind1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  std::set<int> s2 = {1, 2, 3, 4, 5};

  s21::set<int>::iterator my_set_iter = s1.find(3);
  std::set<int>::iterator std_set_iter = s2.find(3);

  EXPECT_EQ(*my_set_iter, *std_set_iter);
}

TEST(SetTests, TestMethodFind2) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};
  std::set<int> s2 = {1, 2, 3, 4, 5};

  s21::set<int>::iterator my_set_iter = s1.find(6);
  std::set<int>::iterator std_set_iter = s2.find(6);

  EXPECT_EQ(my_set_iter, s1.end());
  EXPECT_EQ(std_set_iter, s2.end());
}

TEST(SetTests, TestMethodContains1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};

  EXPECT_TRUE(s1.contains(3));
}

TEST(SetTests, TestMethodContains2) {
  s21::set<int> s1 = {1, 2, 3, 4, 5};

  EXPECT_FALSE(s1.contains(6));
}

TEST(SetTests, TestMaxSize1) {
  s21::set<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  EXPECT_EQ(s1.max_size(), s2.max_size());
}

TEST(SetTests, TestSetInsertMany) {
  s21::set<int> s{5, 5, 5, 4, 12, -1, 4};
  int i{};
  bool check[]{false, false, true, true, true, false};
  auto v = s.insert_many(5, 5, 0, 300, -41, 12);
  for (auto& pr : v) {
    EXPECT_EQ(pr.second, check[i]);
    i++;
  }
}
