#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <functional>
#include <type_traits>

namespace pipeline {
// ������� ����� ��� ����������� �������� �� ������������ ������ ����������
class BasicPipeline {};

// ����� ���������
template <typename T, typename F> class Pipeline : public BasicPipeline {
private:
  T value;
  F func;

public:
  // ����������� ���������
  explicit Pipeline(T value, F func) : value(value), func(func){};

  // �������� ������
  auto operator()() {
    // ���������, �������� �� ������������ ��������� ���������� �� �����
    // ����������, ���� ��, �� ���������� ����� ������� �� �������������
    // ���������� ��������, ����� ������ �� ��������
    if constexpr (std::is_base_of_v<BasicPipeline, std::remove_reference_t<T>>)
      return func(value.operator()());
    else
      return func(value);
  }
};

// ������ ���������, �������� ���������� ��������
template <typename T, typename F> auto operator|(T &&value, F &&func) {

  return Pipeline<T, F>(std::forward<T>(value), std::forward<F>(func));
}

// ������� ����� ������� ������� ���� ����� ���� ����������.
template <typename T> auto to_callable(T func) {
  return [func](auto &&...args) {
    return func(std::forward<decltype(args)>(args)...);
  };
}
} // namespace pipeline

#endif