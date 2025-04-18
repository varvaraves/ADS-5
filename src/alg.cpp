// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  std::string postfix;
  TStack<char, 100> stack;
  std::map<char, int> precedence = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
  };

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    
    if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        postfix += inf[i++];
      }
      postfix += ' ';
      i--;
    } else if (c == '(') {
      stack.Push(c);
    } else if (c == ')') {
      while (!stack.IsEmpty() && stack.Top() != '(') {
        postfix += stack.Pop();
        postfix += ' ';
      }
      stack.Pop();
    } else if (precedence.count(c)) {
      while (!stack.IsEmpty() && stack.Top() != '(' && 
             precedence[stack.Top()] >= precedence[c]) {
        postfix += stack.Pop();
        postfix += ' ';
      }
      stack.Push(c);
    }
  }

  while (!stack.IsEmpty()) {
    postfix += stack.Pop();
    postfix += ' ';
  }

  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }

  return postfix;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  
  for (size_t i = 0; i < post.size(); ++i) {
    char c = post[i];
    
    if (isdigit(c)) {
      int num = 0;
      while (i < post.size() && isdigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        i++;
      }
      stack.Push(num);
      i--;
    } else if (c == ' ') {
      continue;
    } else {
      int right = stack.Pop();
      int left = stack.Pop();
      
      switch (c) {
        case '+': stack.Push(left + right); break;
        case '-': stack.Push(left - right); break;
        case '*': stack.Push(left * right); break;
        case '/': stack.Push(left / right); break;
      }
    }
  }
  
  return stack.Pop();
}
