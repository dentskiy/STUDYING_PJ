#include <fstream>
#include <sstream>
#include <stdexcept>

#include "ObjModel.h"

namespace s21 {

void ObjReader::readFile(std::string& fileName) {
  std::ifstream file;
  file.open(fileName, std::ios::in);
  if (file.is_open()) {
    objClear();
    counterVertexFaces(file);
    // file.seekg(std::ios::beg);
    file.close();
    file.open(fileName);
    vertices.resize(v_count * 3);
    faces.resize(f_count);
    writeObjectData(file);
  }
  file.close();
}

void ObjReader::counterVertexFaces(std::ifstream& referance) {
  std::string str;
  while (std::getline(referance, str)) {
    if (str.find("v ") != static_cast<size_t>(-1)) v_count++;
    if (str.find("f ") != static_cast<size_t>(-1)) {
      for (size_t i = str.find_first_of("0123456789"); i < str.length(); i++) {
        f_count++;  // случай что только один пробел
        while (str[i] != ' ' && i < str.length()) i++;
      }
      f_count++;
    }
  }
}

void ObjReader::writeObjectData(std::ifstream& referance) {
  std::string str, token;
  size_t v_i{0}, f_i{0}, f_current{0};
  while (std::getline(referance, str)) {
    std::stringstream strstream(str);
    strstream >> token;
    if (str.find("v ") != static_cast<size_t>(-1)) {
      strstream >> vertices[v_i * 3];
      strstream >> vertices[v_i * 3 + 1];
      strstream >> vertices[v_i * 3 + 2];
      v_i++;
    }
    if (str.find("f ") != static_cast<size_t>(-1)) {
      while (strstream >> token) {
        std::istringstream iss(token);
        int num;
        iss >> num;

        if (num < 0) {
          faces[f_i] = v_i + num;
        } else {
          faces[f_i] = num - 1;
        }
        f_i++;
      }
      faces[f_i++] = faces[f_current];
      f_current = f_i;
    }
  }
}

void ObjReader::objClear() noexcept {
  v_count = 0;
  f_count = 0;
  vertices.clear();
  faces.clear();
}

}  // namespace s21
