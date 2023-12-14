#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <functional>
#include <type_traits>

namespace pipeline {
// базовый класс для определения является ли передаваемый объект пайплайном
class BasicPipeline {};

// класс пайплайна
template <typename T, typename F> class Pipeline : public BasicPipeline {
private:
  T value;
  F func;

public:
  // конструктор пайплайна
  explicit Pipeline(T value, F func) : value(value), func(func){};

  // оператор вызова
  auto operator()() {
    // проверяет, является ли передаваемое выражение пайплайном во время
    // компиляции, если да, то происходит вызов функции от возвращаемого
    // пайплайном значения, иначе просто от значения
    if constexpr (std::is_base_of_v<BasicPipeline, std::remove_reference_t<T>>)
      return func(value.operator()());
    else
      return func(value);
  }
};

// шаблон оператора, оператор возвращает пайплайн
template <typename T, typename F> auto operator|(T &&value, F &&func) {

  return Pipeline<T, F>(std::forward<T>(value), std::forward<F>(func));
}

// функция чтобы обычные функции тоже можно было передавать.
template <typename T> auto to_callable(T func) {
  return [func](auto &&...args) {
    return func(std::forward<decltype(args)>(args)...);
  };
}
} // namespace pipeline

#endif