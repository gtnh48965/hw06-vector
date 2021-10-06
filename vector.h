#pragma once

template <typename T>
class vector_t {
  // приватные поля
  size_t pos{0};
  size_t cap{0};
  T *arr{nullptr};

  // получить ближайшую степень двойки >= числа
  size_t get_closest_power_of_two(size_t number) {
    size_t result = 1;
    while (result < number) {
      result *= 2;
    }
    return result;
  }

public:
  // пустой конструктор
  vector_t() = default;

  // fill конструктор
  vector_t(size_t n, const T &element) : vector_t() {
    if (!n) {
      return;
    }
    pos = n;
    cap = get_closest_power_of_two(n);
    arr = new T[cap];
    for (size_t i = 0; i < pos; ++i) {
      arr[i] = element;
    }
  }

  // конструктор копирования
  vector_t(const vector_t &other) : vector_t() {
    if (!other.pos) {
      return;
    }
    pos = other.pos;
    cap = get_closest_power_of_two(pos);
    arr = new T[cap];
    for (size_t i = 0; i < pos; ++i) {
      arr[i] = other.arr[i];
    }
  }

  // оператор присвоения
  vector_t &operator=(vector_t other) {
    swap(other);
    return *this;
  }

  // деструктор
  ~vector_t() { delete[] arr; }

  // оператор квадратные скобки
  T &operator[](size_t i) { return arr[i]; }
  const T &operator[](size_t i) const { return arr[i]; }

  // первый элемент
  T &front() { return arr[0]; }
  const T &front() const { return arr[0]; }

  // последний элемент
  T &back() { return arr[pos - 1]; }
  const T &back() const { return arr[pos - 1]; }

  // указатель на внутреннее хранилище
  T *data() { return arr; }
  const T *data() const { return arr; }

  // пуст ли вектор
  bool empty() const { return pos == 0; }

  // размер вектора
  size_t size() const { return pos; }

  // вместимость вектора
  size_t capacity() const { return cap; }

  // увеличить размер вектора минимум до данного размера
  void reserve(size_t new_size) {
    if (new_size <= cap) {
      return;
    }
    cap = get_closest_power_of_two(new_size);
    T *old_arr = arr;
    arr = new T[cap];
    for (size_t i = 0; i < pos; ++i) {
      arr[i] = old_arr[i];
    }
    delete[] old_arr;
  }

  // уменьшить размер вектора до минимально возможного
  void shrink_to_fit() {
    if (pos == 0) {
      *this = vector_t();
      return;
    }
    size_t new_cap = get_closest_power_of_two(pos);
    if (new_cap == cap) {
      return;
    }
    cap = new_cap;
    T *old_arr = arr;
    arr = new T[cap];
    for (size_t i = 0; i < pos; ++i) {
      arr[i] = old_arr[i];
    }
    delete[] old_arr;
  }

  // очистка
  void clear() { *this = vector_t(); }

  // вставка
  void insert(size_t i, const T &element) { insert(i, 1, element); }
  void insert(size_t i, size_t n, const T &element) {
    reserve(pos + n);
    pos += n;
    for (size_t j = pos - 1; j > i + n - 1; --j) {
      arr[j] = arr[j - n];
    }
    for (size_t j = i; j < i + n; ++j) {
      arr[j] = element;
    }
  }

  // удаление
  void erase(size_t i) { erase(i, i + 1); }
  void erase(size_t i, size_t j) {
    pos -= j - i;
    for (size_t k = i; k < pos; ++k) {
      arr[k] = arr[k + j - i];
    }
  }

  // добавление элемента в конец
  void push_back(const T &element) {
    reserve(pos + 1);
    ++pos;
    arr[pos - 1] = element;
  }

  // удаление элемента с конца
  void pop_back() { --pos; }

  // изменить размер и заполнить новыми элементами
  void resize(size_t new_size, const T &element = T()) {
    if (new_size <= pos) {
      pos = new_size;
      return;
    }
    insert(pos, new_size - pos, element);
  }

  // свап
  void swap(vector_t &other) {
    std::swap(pos, other.pos);
    std::swap(cap, other.cap);
    std::swap(arr, other.arr);
  }

  // сравнение
  bool operator<(const vector_t &other) const {
    for (size_t i = 0; i < std::min(pos, other.pos); ++i) {
      if (arr[i] != other.arr[i]) {
        return arr[i] < other.arr[i];
      }
    }
    return pos < other.pos;
  }
  bool operator>(const vector_t &other) const { return other < *this; }
  bool operator<=(const vector_t &other) const { return !(*this > other); }
  bool operator>=(const vector_t &other) const { return other <= *this; }
  bool operator!=(const vector_t &other) const { return (*this < other) || (*this > other); }
  bool operator==(const vector_t &other) const { return !(*this != other); }
};