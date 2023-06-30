#include "Solution.h"

std::string Solution::GetPressedString(const std::string &str) {
  if (str.size() == 0) {
    return str;
  }

  std::string ret = "";
  int chCnt = 0;
  for (auto ch : str) {
    if (ret.size() == 0) {
      ret += ch;
      chCnt = 1;
      continue;
    }

    int maxIdx = ret.size() - 1;
    if (ret[maxIdx] == ch) {
      chCnt++;
    } else {
      ret += std::to_string(chCnt);
      ret += ch;
      chCnt = 1;
    }
  }

  ret += std::to_string(chCnt); // 确保最后1个的字符的数量信息能添加上

  return (ret.size() >= str.size()) ? str : ret;
}