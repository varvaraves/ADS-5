// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int size>
class TStack {
 private:
  T data[size];
  int top_index;

 public:
  TStack() : top_index(-1) {}

  void Push(const T& value) {
    if (top_index < size - 1) {
      data[++top_index] = value;
    }
  }

  T Pop() {
    if (!IsEmpty()) {
      return data[top_index--];
    }
    return T();
  }

  T Top() const {
    if (!IsEmpty()) {
      return data[top_index];
    }
    return T();
  }

  bool IsEmpty() const {
    return top_index == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
