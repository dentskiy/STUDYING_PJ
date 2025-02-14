#include <fstream>
#include <iostream>

#include "utils.h"

namespace s21 {

FileManager::FileManager() : fname_{} {}

bool FileManager::SetFilename(const char* fname) {
  bool res = true;
  std::ifstream in;
  for (int i{}; i < 300 && *fname; i++) {
    fname_[i] = *fname++;
  }
  if (*fname) res = false;
  if (res) {
    in.open(fname_);
    res = in.is_open();
    in.close();
  }
  return res;
}

int FileManager::GetSave() {
  int res{};
  std::ifstream in(fname_);
  if (in.is_open()) {
    in >> res;
  }
  in.close();
  return res;
}

void FileManager::SetSave(int score) {
  std::ofstream out(fname_);
  if (out.is_open()) {
    out << score << std::endl;
  }
  out.close();
}
}  // namespace s21