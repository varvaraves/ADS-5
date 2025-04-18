// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int GetPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  std::string result;
  TStack<char, 100> stack;

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    if (std::isdigit(c)) {
      while (i < inf.size() && std::isdigit(inf[i])) {
        result += inf[i];
        ++i;
      }
      result += ' ';
      --i;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        result += stack.pop();
        result += ' ';
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!stack.isEmpty() && GetPriority(stack.top()) >= GetPriority(c)) {
        result += stack.pop();
        result += ' ';
      }
      stack.push(c);
    }
  }

  while (!stack.isEmpty()) {
    result += stack.pop();
    result += ' ';
  }

  if (!result.empty() && result.back() == ' ') result.pop_back();
  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  size_t i = 0;

  while (i < post.size()) {
    if (std::isdigit(post[i])) {
      int num = 0;
      while (i < post.size() && std::isdigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        ++i;
      }
      stack.push(num);
    } else if (post[i] == '+' || post[i] == '-' ||
               post[i] == '*' || post[i] == '/') {
      int b = stack.pop();
      int a = stack.pop();
      int res = 0;
      switch (post[i]) {
        case '+':
          res = a + b;
          break;
        case '-':
          res = a - b;
          break;
        case '*':
          res = a * b;
          break;
        case '/':
          res = a / b;
          break;
      }
      stack.push(res);
      ++i;
    } else {
      ++i;
    }
  }

  return stack.pop();
}
