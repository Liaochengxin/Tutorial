#ifndef OPERATOR_H
#define OPERATOR_H

namespace ops{
//+
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b){
  return a + b;
}

template<typename T1, typename T2>
auto subtract(T1 a, T2 b) -> decltype(a - b){
  return a - b;
}

//*
template<typename T1, typename T2>
auto multiply(T1 a, T2 b) -> decltype(a * b){
  return a * b;
}

template <typename T1, typename T2>
auto divide(T1 a, T2 b) -> decltype(a / b) {
    if (b == 0)
        throw std::runtime_error("Divide by zero");
    return a / b;
}

}
#endif
