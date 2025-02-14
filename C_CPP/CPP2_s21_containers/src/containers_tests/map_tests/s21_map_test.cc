#include <iostream>
#include <map>

#include "../test.h"

TEST(MapTests, TestMapInsertKeyT) {
  s21::map<int, int> m;
  EXPECT_EQ(m.insert(4, 5).second, true);
  EXPECT_EQ(m.insert(3, 3).second, true);
  EXPECT_EQ(m.insert(8, 1).second, true);
  EXPECT_EQ(m.insert(6, 6).second, true);
  EXPECT_EQ(m.insert(-5, -5).second, true);
  EXPECT_EQ(m.insert(7, -3).second, true);
  std::map<int, int> chm;
  chm.insert({4, 5});
  chm.insert({3, 3});
  chm.insert({8, 1});
  chm.insert({6, 6});
  chm.insert({-5, -5});
  chm.insert({7, -3});
  auto iter = chm.begin();
  auto it = m.begin();
  for (; it != m.end() && iter != chm.end(); it++, iter++) {
    EXPECT_EQ(it->second, iter->second);
  }
}

TEST(MapTests, TestMapInsertPair) {
  s21::map<int, int> m;
  EXPECT_EQ(m.insert({4, 5}).second, true);
  EXPECT_EQ(m.insert({3, 3}).second, true);
  EXPECT_EQ(m.insert({8, 1}).second, true);
  EXPECT_EQ(m.insert({6, 6}).second, true);
  EXPECT_EQ(m.insert({-5, -5}).second, true);
  EXPECT_EQ(m.insert({7, -3}).second, true);
  std::map<int, int> chm;
  chm.insert({4, 5});
  chm.insert({3, 3});
  chm.insert({8, 1});
  chm.insert({6, 6});
  chm.insert({-5, -5});
  chm.insert({7, -3});
  auto iter = chm.begin();
  auto it = m.begin();
  for (; it != m.end() && iter != chm.end(); it++, iter++) {
    EXPECT_EQ(it->second, iter->second);
  }
}

TEST(MapTests, TestMapCapacity) {
  s21::map<int, int> m1{{1, 1}, {2, 2}}, m2;
  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m2.size(), 0);
  EXPECT_EQ(m1.empty(), false);
  EXPECT_EQ(m2.empty(), true);
}

TEST(MapTests, TestMapMaxSize) {
  s21::map<int, int> m1{{1, 1}, {2, 2}};
  std::map<int, int> m2{{1, 1}, {2, 2}};
  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(MapTests, TestMapConstIterator1) {
  s21::map<int, int> m1{{2, 2}, {3, 3}, {1, 1}, {5, 5}};
  s21::map m2{m1};
  s21::map m3(std::move(m1));
  int check[]{1, 2, 3, 5};
  auto it2 = m2.begin();
  auto it3 = m3.begin();
  EXPECT_EQ(m1.empty(), true);
  for (int i{}; i < 4; i++, it2++, it3++) {
    EXPECT_EQ(it2->first, check[i]);
    EXPECT_EQ(it2->second, check[i]);
    EXPECT_EQ(it3->first, check[i]);
    EXPECT_EQ(it3->second, check[i]);
  }
}

TEST(MapTests, TestMapConstIterator2) {
  s21::map<int, int> m1{{2, 2}, {3, 3}, {1, 1}, {5, 5}};
  int arr[]{1, 2, 3, 5};
  s21::map<int, int>::iterator it = m1.begin();
  s21::map<int, int>::const_iterator cit = m1.begin();
  for (int i{}; cit != m1.end(); cit++, i++, it++) {
    EXPECT_EQ(arr[i], cit->first);
    EXPECT_EQ(arr[i], it->first);
    EXPECT_EQ(cit->second, it->second);
  }
}

TEST(MapTests, TestMapOperatorMove) {
  s21::map<int, int> m1{{2, 2}, {3, 3}, {1, 1}, {5, 5}};
  s21::map<int, int> m2(m1), m3;
  m3 = std::move(m1);
  int check[]{1, 2, 3, 5};
  auto it2 = m2.begin();
  auto it3 = m3.begin();
  EXPECT_EQ(m1.empty(), true);
  for (int i{}; i < 4; i++, it2++, it3++) {
    EXPECT_EQ(it2->first, check[i]);
    EXPECT_EQ(it2->second, check[i]);
    EXPECT_EQ(it3->first, check[i]);
    EXPECT_EQ(it3->second, check[i]);
  }
}

TEST(MapTests, TestMapAccessAt) {
  s21::map<int, int> m{{2, 2}, {3, 3}, {1, 1}, {5, 5}};
  int check[]{1, 2, 3, 5};
  auto it = m.begin();
  for (int& n : check) {
    EXPECT_EQ(m.at(n), it->second);
    it++;
  }
}

TEST(MapTests, TestMapAccessAtThrow) {
  s21::map<int, int> m{{2, 2}, {3, 3}, {1, 1}, {5, 5}};
  s21::map<int, int> m0;
  EXPECT_ANY_THROW(m.at(-7));
  EXPECT_ANY_THROW(m0.at(2));
}
TEST(MapTests, TestMapAccessOperator) {
  s21::map<std::string, int> m;
  std::map<std::string, int> std_m;
  EXPECT_EQ(m.size(), std_m.size());
  m["abc"] = 5;
  m["aaa"] = 3;
  m["ccc"] = 7;
  std_m["abc"] = 5;
  std_m["aaa"] = 3;
  std_m["ccc"] = 7;
  EXPECT_EQ(m.size(), std_m.size());
  auto it = m.begin();
  auto iter = std_m.begin();
  for (; it != m.end() && iter != std_m.end(); it++, iter++) {
    EXPECT_EQ(it->first, iter->first);
    EXPECT_EQ(it->second, iter->second);
  }
  EXPECT_EQ(m["abc"], 5);
  EXPECT_EQ(std_m["abc"], 5);
}

TEST(MapTests, TestMapInsertOrAssign) {
  s21::map<int, int> m;
  std::map<int, int> std_m;
  m[5] = 5;
  m[3] = 3;
  m[6] = 6;
  std_m[5] = 5;
  std_m[3] = 3;
  std_m[6] = 6;
  EXPECT_EQ(m.size(), std_m.size());
  m.insert_or_assign(3, -3);
  std_m.insert_or_assign(3, -3);
  EXPECT_EQ(m.size(), std_m.size());
  EXPECT_EQ(m[3], -3);
  EXPECT_EQ(m[3], std_m[3]);
  m.insert_or_assign(4, -4);
  std_m.insert_or_assign(4, -4);
  EXPECT_EQ(m.size(), std_m.size());
  EXPECT_EQ(m[4], -4);
  EXPECT_EQ(m[4], std_m[4]);
}

// erase(end()) - delete not alloceted memory
TEST(MapTests, TestMapErase) {
  s21::map<int, int> m{{1, 2}, {5, 5}};
  int key[]{1, 5, 6, 8};
  int val[]{2, 5, -5, 9};
  int i{};
  auto it = m.end();
  EXPECT_EQ(m.erase(m.begin())->first, 5);
  EXPECT_EQ(m.begin()->first, 5);
  m.insert({1, 2});
  m.insert({8, 9});
  it = m.insert({3, 3}).first;
  m.insert({6, -5});
  it = m.erase(it);
  EXPECT_EQ(it->first, 5);
  for (auto pr : m) {
    EXPECT_EQ(pr.first, key[i]);
    EXPECT_EQ(pr.second, val[i]);
    i++;
  }
  while (!m.empty()) {
    EXPECT_EQ(m.size(), i);
    m.erase(m.begin());
    i--;
  }
  EXPECT_EQ(m.empty(), true);
}

TEST(MapTests, TestMapSwap11) {
  s21::map<int, int> m1{{1, 1}, {2, 2}}, m2(m1);
  int check[]{6, 1, 2}, i{};
  m2[-3] = 6;
  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m2.size(), 3);
  m1.swap(m2);
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m2.size(), 2);
  for (auto& val : m1) {
    EXPECT_EQ(val.second, check[i]);
    i++;
  }
  i = 1;
  for (auto& val : m2) {
    EXPECT_EQ(val.second, check[i]);
    i++;
  }
}

TEST(MapTests, TestMapSwap10) {
  s21::map<int, int> m1{{1, 1}, {2, 2}}, m2;
  m1.swap(m2);
  EXPECT_EQ(m1.empty(), true);
  EXPECT_EQ(m2.size(), 2);
}

TEST(MapTests, TestMapSwap01) {
  s21::map<int, int> m1{{1, 1}, {2, 2}}, m2;
  m2.swap(m1);
  EXPECT_EQ(m1.empty(), true);
  EXPECT_EQ(m2.size(), 2);
}

TEST(MapTests, TestMapSwap00) {
  s21::map<int, int> m1, m2;
  m2.swap(m1);
  EXPECT_EQ(m1.empty(), true);
  EXPECT_EQ(m2.empty(), true);
}

TEST(MapTests, TestMapMerge1) {
  s21::map<int, int> m1{{5, 5}, {8, 8}, {3, 3}};
  s21::map<int, int> m2{{3, -3}, {1, 1}, {6, 6}};
  std::map<int, int> std_m1{{5, 5}, {8, 8}, {3, 3}};
  std::map<int, int> std_m2{{3, -3}, {1, 1}, {6, 6}};
  m1.merge(m2);
  std_m1.merge(std_m2);
  EXPECT_EQ(m1.size(), std_m1.size());
  EXPECT_EQ(m2.size(), std_m2.size());
  auto it = m1.begin();
  auto std_it = std_m1.begin();
  for (; it != m1.end() && std_it != std_m1.end(); it++, std_it++) {
    EXPECT_EQ(it->first, std_it->first);
    EXPECT_EQ(it->second, std_it->second);
  }
}

TEST(MapTests, TestMapMerge2) {
  s21::map<int, int> m1;
  s21::map<int, int> m2{{3, -3}, {1, 1}, {6, 6}};
  std::map<int, int> std_m1;
  std::map<int, int> std_m2{{3, -3}, {1, 1}, {6, 6}};
  m1.merge(m2);
  std_m1.merge(std_m2);
  EXPECT_EQ(m1.size(), std_m1.size());
  EXPECT_EQ(m2.empty(), true);
  auto it = m1.begin();
  auto std_it = std_m1.begin();
  for (; it != m1.end() && std_it != std_m1.end(); it++, std_it++) {
    EXPECT_EQ(it->first, std_it->first);
    EXPECT_EQ(it->second, std_it->second);
  }
}

TEST(MapTests, TestMapInsertMany) {
  s21::map<int, int> m{{1, 2}, {5, 5}};
  int i{};
  bool check[]{false, true, false};
  auto v = m.insert_many(std::pair{1, 1}, std::pair{-3, 2}, std::pair{5, 6});
  for (auto& pr : v) {
    EXPECT_EQ(pr.second, check[i]);
    i++;
  }
}

TEST(MapTests, TestMapContains1) {
  s21::map<std::string, int> m;
  m["abc"] = 5;
  m["aaa"] = 3;
  m["ccc"] = 7;
  EXPECT_EQ(m.contains("abc"), true);
  EXPECT_EQ(m.contains("aaa"), true);
  EXPECT_EQ(m.contains("ccc"), true);
  EXPECT_EQ(m.contains("bbb"), false);
  m["bbb"] = 0;
  EXPECT_EQ(m.contains("bbb"), true);
}

TEST(MapTests, TestMapContainsEmpty) {
  s21::map<std::string, int> m;
  EXPECT_EQ(m.contains("abc"), false);
  EXPECT_EQ(m.contains("aaa"), false);
  EXPECT_EQ(m.contains("ccc"), false);
  EXPECT_EQ(m.contains("bbb"), false);
  m["bbb"] = 0;
  EXPECT_EQ(m.contains("bbb"), true);
}