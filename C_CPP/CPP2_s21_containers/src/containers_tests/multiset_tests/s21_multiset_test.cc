#include <set>

#include "../test.h"

TEST(MultiSetTests, TestDefaultConstractor1) {
  s21::multiset<int> s1;
  std::multiset<int> s2;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(MultiSetTests, TestDefaultConstractor2) {
  s21::multiset<double> s1;
  std::multiset<double> s2;
  s1.insert(3.3);
  s1.insert(3.3);
  s2.insert(3.3);
  s2.insert(3.3);

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(MultiSetTests, TestInitializerListConstructor1) {
  s21::multiset<int> s1 = {3, 3, 5, 2, 2, 2, 300, 123};
  std::multiset<int> s2 = {3, 3, 5, 2, 2, 2, 300, 123};

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());

  s21::multiset<int>::iterator my_multiset_it;
  std::multiset<int>::iterator std_multiset_it;

  for (my_multiset_it = s1.begin(), std_multiset_it = s2.begin();
       my_multiset_it != s1.end(); ++my_multiset_it, ++std_multiset_it) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
  }
}

TEST(MultiSetTests, TestInitializerListConstructor2) {
  s21::multiset<double> s1 = {3.3, 3.3, 5.5, 2.2, 2.2};
  std::multiset<double> s2 = {3.3, 3.3, 5.5, 2.2, 2.2};

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());

  s21::multiset<double>::iterator my_multiset_it;
  std::multiset<double>::iterator std_multiset_it;

  for (my_multiset_it = s1.begin(), std_multiset_it = s2.begin();
       my_multiset_it != s1.end(); ++my_multiset_it, ++std_multiset_it) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
  }
}

TEST(MultiSetTests, TestCopyConstructor1) {
  s21::multiset<int> s1 = {5, 3, 5, 2, 3};
  s21::multiset<int> s2 = s1;
  std::multiset<int> s3 = {5, 3, 5, 2, 3};
  std::multiset<int> s4 = s3;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.size(), s4.size());

  EXPECT_EQ(s3.empty(), s4.empty());
  EXPECT_EQ(s3.empty(), s2.empty());

  s21::multiset<int>::iterator my_multiset_it;
  std::multiset<int>::iterator std_multiset_it;

  for (my_multiset_it = s1.begin(), std_multiset_it = s3.begin();
       my_multiset_it != s1.end(); ++my_multiset_it, ++std_multiset_it) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
  }
}

TEST(MultiSetTests, TestCopy1) {
  s21::multiset<double> s1 = {5.5, 3.3, 5.5, 2.2, 3.3};
  s21::multiset<double> s2;
  s2 = s1;
  std::multiset<double> s3 = {5.5, 3.3, 5.5, 2.2, 3.3};
  std::multiset<double> s4;
  s4 = s3;

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.size(), s4.size());

  EXPECT_EQ(s3.empty(), s4.empty());
  EXPECT_EQ(s3.empty(), s2.empty());

  s21::multiset<double>::iterator my_multiset_it;
  std::multiset<double>::iterator std_multiset_it;

  for (my_multiset_it = s1.begin(), std_multiset_it = s3.begin();
       my_multiset_it != s1.end(); ++my_multiset_it, ++std_multiset_it) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
  }
}

TEST(MultiSetTests, TestMoveConstructor1) {
  s21::multiset<int> s1 = {5, 3, 5, 2, 3};
  s21::multiset<int> s2;
  s2 = std::move(s1);
  std::multiset<int> s3 = {5, 3, 5, 2, 3};
  std::multiset<int> s4;
  s4 = std::move(s3);

  EXPECT_EQ(s1.size(), 0);
  EXPECT_EQ(s2.size(), 5);

  EXPECT_EQ(s1.empty(), s3.empty());
  EXPECT_EQ(s2.empty(), s4.empty());

  s21::multiset<int>::iterator my_multiset_it;
  std::multiset<int>::iterator std_multiset_it;

  for (my_multiset_it = s2.begin(), std_multiset_it = s4.begin();
       my_multiset_it != s2.end(); ++my_multiset_it, ++std_multiset_it) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
  }
}

TEST(MultiSetTests, TestMoveConstructor2) {
  s21::multiset<double> s1 = {5.5, 3.3, 5.5, 2.2, 3.3};
  auto tmp_size1 = s1.size();
  s21::multiset<double> s2 = std::move(s1);

  std::multiset<double> s3 = {5.5, 3.3, 5.5, 2.2, 3.3};
  auto tmp_size3 = s3.size();
  std::multiset<double> s4 = std::move(s3);

  EXPECT_EQ(s2.size(), tmp_size1);
  EXPECT_EQ(s4.size(), tmp_size3);

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s3.empty());

  s21::multiset<double>::iterator my_multiset_it;
  std::multiset<double>::iterator std_multiset_it;

  for (my_multiset_it = s2.begin(), std_multiset_it = s4.begin();
       my_multiset_it != s2.end(); ++my_multiset_it, ++std_multiset_it) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
  }
}

TEST(MultiSetTests, TestMoveConstructor3) {
  s21::multiset<int> s1 = {5, 3, 5, 2, 3};
  s21::multiset<int> s2 = std::move(s1);
  std::multiset<int> s3 = {5, 3, 5, 2, 3};
  std::multiset<int> s4 = std::move(s3);

  EXPECT_EQ(s1.size(), 0);
  EXPECT_EQ(s2.size(), 5);

  EXPECT_EQ(s1.empty(), s3.empty());
  EXPECT_EQ(s2.empty(), s4.empty());

  s21::multiset<int>::iterator my_multiset_it;
  std::multiset<int>::iterator std_multiset_it;

  for (my_multiset_it = s2.begin(), std_multiset_it = s4.begin();
       my_multiset_it != s2.end(); ++my_multiset_it, ++std_multiset_it) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
  }
}

TEST(MultiSetTests, TestIterator1) {
  s21::multiset<int> s1 = {5, 3, 5, 2, 3};
  std::multiset<int> s2 = {5, 3, 5, 2, 3};

  s21::multiset<int>::iterator my_multiset_it = s1.begin();
  std::multiset<int>::iterator std_multiset_it = s2.begin();

  EXPECT_EQ(*my_multiset_it, *std_multiset_it);

  for (int i = 1; i <= 5; ++i) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
    ++my_multiset_it;
    ++std_multiset_it;
  }
}

TEST(MultiSetTests, TestIterator2) {
  s21::multiset<int> s1 = {5, 3, 5, 2, 3};
  std::multiset<int> s2 = {5, 3, 5, 2, 3};

  s21::multiset<int>::iterator my_multiset_it = s1.begin();
  std::multiset<int>::iterator std_multiset_it = s2.begin();

  EXPECT_EQ(*my_multiset_it, *std_multiset_it);

  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
    ++my_multiset_it;
    ++std_multiset_it;
  }

  for (int i = 3; i >= 1; --i) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
    --my_multiset_it;
    --std_multiset_it;
  }
}

TEST(MultiSetTests, TestIterator3) {
  s21::multiset<int> s1 = {3, 1, 1, 4, 3};
  std::multiset<int> s2 = {3, 1, 1, 4, 3};

  s21::multiset<int>::iterator my_multiset_it = s1.begin();
  std::multiset<int>::iterator std_multiset_it = s2.begin();

  EXPECT_EQ(*my_multiset_it, *std_multiset_it);

  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
    ++my_multiset_it;
    ++std_multiset_it;
  }

  for (int i = 3; i >= 1; --i) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
    --my_multiset_it;
    --std_multiset_it;
  }
}

TEST(MultiSetTests, TestIterator5) {
  s21::multiset<int> s1 = {3, 1, 1, 4, 3};
  std::multiset<int> s2 = {3, 1, 1, 4, 3};

  s21::multiset<int>::iterator my_multiset_it = s1.begin();
  std::multiset<int>::iterator std_multiset_it = s2.begin();
  my_multiset_it--;
  std_multiset_it--;

  EXPECT_EQ(my_multiset_it, s1.end());
  EXPECT_EQ(std_multiset_it, s2.end());
}

TEST(MultiSetTests, TestMethodInsert1) {
  s21::multiset<int> s1;
  std::multiset<int> s2;

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());

  s1.insert(5);
  s1.insert(3);
  s1.insert(3);
  s1.insert(5);
  s1.insert(2);

  s2.insert(5);
  s2.insert(3);
  s2.insert(5);
  s2.insert(3);
  s2.insert(2);

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());

  s21::multiset<int>::iterator my_multiset_it;
  std::multiset<int>::iterator std_multiset_it;

  for (my_multiset_it = s1.begin(), std_multiset_it = s2.begin();
       my_multiset_it != s1.end(); ++my_multiset_it, ++std_multiset_it) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
  }
}

// тестовый тест
TEST(MultiSetTests, TestMethodInsert2) {
  s21::multiset<int> s1;
  std::multiset<int> s2;

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());

  for (int i = 0; i < 2500; i++) {
    int x = rand() % 5049;
    s1.insert(x);
    s2.insert(x);
  }
  auto my_multiset_it = s1.begin();
  auto std_multiset_it = s2.begin();
  for (; my_multiset_it != s1.end(); ++my_multiset_it, ++std_multiset_it) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
  }
}

TEST(MultiSetTests, TestMethodClear1) {
  s21::multiset<int> s1 = {5, 3, 5, 2, 3};
  std::multiset<int> s2 = {5, 3, 5, 2, 3};

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());

  s1.clear();
  s2.clear();

  EXPECT_EQ(s1.empty(), s2.empty());

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.empty());
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(MultiSetTests, TestMethodErase1) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, -1};
  std::multiset<int> s2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, -1};

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

TEST(MultiSetTests, TestMethodSwap1) {
  s21::multiset<int> s1 = {1, 2, 3, 4, 5};
  auto tmp_size1 = s1.size();
  s21::multiset<int> s2 = {3, 4, 5};
  auto tmp_size2 = s2.size();

  s1.swap(s2);

  EXPECT_EQ(s1.size(), tmp_size2);
  EXPECT_EQ(s2.size(), tmp_size1);

  EXPECT_EQ(*s1.begin(), 3);
  EXPECT_EQ(*s2.begin(), 1);
}

TEST(MultiSetTests, TestMethodMerge1) {
  s21::multiset<int> s1 = {3, 2, 2, 4, 5, 5, 1};
  s21::multiset<int> s2 = {1};
  s1.merge(s2);

  std::multiset<int> s3 = {3, 2, 2, 4, 5, 5, 1};
  std::multiset<int> s4 = {1};
  s3.merge(s4);

  s21::set<int>::iterator my_set_iter;
  std::set<int>::iterator std_set_iter;
  for (my_set_iter = s1.begin(), std_set_iter = s3.begin();
       my_set_iter != s1.end(); ++my_set_iter, ++std_set_iter) {
    EXPECT_EQ(*my_set_iter, *std_set_iter);
  }

  EXPECT_EQ(s1.size(), s3.size());
}

TEST(MultiSetTests, TestMethodFind1) {
  s21::multiset<int> s1 = {3, 2, 2, 4, 5, 5, 1};
  std::multiset<int> s2 = {3, 2, 2, 4, 5, 5, 1};

  s21::multiset<int>::iterator my_multiset_it = s1.find(2);
  std::multiset<int>::iterator std_multiset_it = s2.find(2);

  EXPECT_EQ(*my_multiset_it, *std_multiset_it);
}

// как тут сделать???
TEST(MultiSetTests, TestMethodFind2) {
  s21::multiset<int> s1 = {3, 2, 2, 4, 5, 5, 1};
  std::multiset<int> s2 = {3, 2, 2, 4, 5, 5, 1};

  s21::multiset<int>::iterator my_multiset_it = s1.find(5);
  std::multiset<int>::iterator std_multiset_it = s2.find(5);

  EXPECT_EQ(*my_multiset_it, *std_multiset_it);
}

TEST(MultiSetTests, TestMethodCount1) {
  s21::multiset<int> s1 = {3, 2, 2, 4, 5, 5, 1, 1};
  std::multiset<int> s2 = {3, 2, 2, 4, 5, 5, 1, 1};

  EXPECT_EQ(s1.count(2), s2.count(2));
  EXPECT_EQ(s1.count(5), s2.count(5));
  EXPECT_EQ(s1.count(1), s2.count(1));
  EXPECT_EQ(s1.count(3), s2.count(3));
  EXPECT_EQ(s1.count(4), s2.count(4));
}

TEST(MultiSetTests, TestMethodCount2) {
  s21::multiset<int> s1 = {3, 3, 3, 2, 2};

  EXPECT_EQ(s1.count(2), 2);
  EXPECT_EQ(s1.count(3), 3);
}

TEST(MultiSetTests, TestMethodContains1) {
  s21::multiset<int> s1 = {3, 2, 2, 4, 5, 5, 1, 1};

  EXPECT_EQ(s1.contains(2), true);
  EXPECT_EQ(s1.contains(5), true);
  EXPECT_EQ(s1.contains(1), true);
  EXPECT_EQ(s1.contains(3), true);
  EXPECT_EQ(s1.contains(4), true);
  EXPECT_EQ(s1.contains(7), false);
  EXPECT_EQ(s1.contains(-1), false);
  EXPECT_EQ(s1.contains(322), false);
}

TEST(MultiSetTests, TestMethodContains2) {
  s21::multiset<int> s1 = {3, 3, 3, 2, 2};

  EXPECT_EQ(s1.contains(2), true);
  EXPECT_EQ(s1.contains(3), true);
}

TEST(MultiSetTests, TestMultiSetInsertMany) {
  s21::multiset<int> s{5, 5, 5, 4, 12, -1, 4};
  std::multiset<int> s1{5, 5, 5, 4, 12, -1, 4};
  int i{};
  bool check[]{true, true, true, true, true, true};
  auto v = s.insert_many(5, 5, 0, 300, -41, 12);
  for (auto& pr : v) {
    EXPECT_EQ(pr.second, check[i]);
    i++;
  }
  s1.insert(5);
  s1.insert(5);
  s1.insert(0);
  s1.insert(300);
  s1.insert(-41);
  s1.insert(12);

  auto my_multiset_it = s.begin();
  auto std_multiset_it = s1.begin();
  for (; my_multiset_it != s.end(); ++my_multiset_it, ++std_multiset_it) {
    EXPECT_EQ(*my_multiset_it, *std_multiset_it);
  }
}

TEST(MultiSetTests, TestMethodEqualRange1) {
  s21::multiset<int> s1 = {3, 2, 2, 4, 5, 5, 1, 1};
  std::multiset<int> s2 = {3, 2, 2, 4, 5, 5, 1, 1};

  s21::multiset<int>::iterator my_multiset_it = s1.equal_range(2).first;
  std::multiset<int>::iterator std_multiset_it = s2.equal_range(2).first;
  EXPECT_EQ(*my_multiset_it, *std_multiset_it);
}

TEST(MultiSetTests, TestMethodEqualRange2) {
  s21::multiset<int> s1 = {3, 2, 2, 2, 4, 5, 5, 1, 1};
  std::multiset<int> s2 = {3, 2, 2, 2, 4, 5, 5, 1, 1};

  s21::multiset<int>::iterator my_multiset_it = s1.equal_range(2).second;
  std::multiset<int>::iterator std_multiset_it = s2.equal_range(2).second;
  EXPECT_EQ(*my_multiset_it, *std_multiset_it);
}

TEST(MultiSetTests, TestMethodLoverBound1) {
  s21::multiset<int> s1 = {3, 2, 2, 4, 5, 5, 1, 1};
  std::multiset<int> s2 = {3, 2, 2, 4, 5, 5, 1, 1};

  s21::multiset<int>::iterator my_multiset_it = s1.lower_bound(2);
  std::multiset<int>::iterator std_multiset_it = s2.lower_bound(2);
  EXPECT_EQ(*my_multiset_it, *std_multiset_it);
}

TEST(MultiSetTests, TestMethodLoverBound2) {
  s21::multiset<int> s1 = {3, 2, 2, 4, 5, 5, 1, 1};
  std::multiset<int> s2 = {3, 2, 2, 4, 5, 5, 1, 1};

  s21::multiset<int>::iterator my_multiset_it = s1.lower_bound(5);
  std::multiset<int>::iterator std_multiset_it = s2.lower_bound(5);

  EXPECT_EQ(*my_multiset_it, *std_multiset_it);
}

TEST(MultiSetTests, TestMethodUpperBound1) {
  s21::multiset<int> s1 = {3, 2, 2, 4, 5, 5, 1, 1};
  std::multiset<int> s2 = {3, 2, 2, 4, 5, 5, 1, 1};

  s21::multiset<int>::iterator my_multiset_it = s1.upper_bound(2);
  std::multiset<int>::iterator std_multiset_it = s2.upper_bound(2);
  EXPECT_EQ(*my_multiset_it, *std_multiset_it);
}

TEST(MultiSetTests, TestMethodUpperBound2) {
  s21::multiset<int> s1 = {3, 2, 2, 4, 5, 5, 1, 1};
  std::multiset<int> s2 = {3, 2, 2, 4, 5, 5, 1, 1};

  s21::multiset<int>::iterator my_multiset_it = s1.upper_bound(5);
  std::multiset<int>::iterator std_multiset_it = s2.upper_bound(5);
  EXPECT_EQ(my_multiset_it == s1.end(), std_multiset_it == s2.end());
}
