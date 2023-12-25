// RUN: %check_clang_tidy %s rawspeed-std-array-no-operator-at %t

namespace std {

template <typename T, int S> class array {
public:
  const T &operator[](int i) const;
  T &operator[](int i);

  const T &operator*(int i) const;
  T &operator*(int i);
};

template <typename T, int S> class not_an_array {
public:
  const T &operator[](int i) const;
  T &operator[](int i);

  const T &operator*(int i) const;
  T &operator*(int i);
};

} // namespace std

namespace some_other_namespace {

template <typename T, int S> class array {
public:
  const T &operator[](int i) const;
  T &operator[](int i);

  const T &operator*(int i) const;
  T &operator*(int i);
};

template <typename T, int S> class not_an_array {
public:
  const T &operator[](int i) const;
  T &operator[](int i);

  const T &operator*(int i) const;
  T &operator*(int i);
};

} // namespace some_other_namespace

template <typename T, int S> using my_array = std::array<T, S>;

namespace {

template <typename T, int S> class array : public std::array<T, S> {
public:
  const T &operator[](int i) const;
  T &operator[](int i);

  const T &operator*(int i) const;
  T &operator*(int i);
};

} // namespace

void sink(int);
int source();

void f0(std::array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'std::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'std::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  sink(arr.operator[](0));
  sink(arr.operator[](source()));
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'std::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'std::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  int& (decltype(arr)::*funPtr)(int);
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f1(const std::array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'std::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'std::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  sink(arr.operator[](0));
  sink(arr.operator[](source()));
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'std::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'std::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  const int& (decltype(arr)::*funPtr)(int) const;
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f2(std::not_an_array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);

  sink(arr.operator[](0));
  sink(arr.operator[](source()));

  int& (decltype(arr)::*funPtr)(int);
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f3(const std::not_an_array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);

  sink(arr.operator[](0));
  sink(arr.operator[](source()));

  const int& (decltype(arr)::*funPtr)(int) const;
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f4(some_other_namespace::array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);

  sink(arr.operator[](0));
  sink(arr.operator[](source()));

  int& (decltype(arr)::*funPtr)(int);
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f5(const some_other_namespace::array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);

  sink(arr.operator[](0));
  sink(arr.operator[](source()));

  const int& (decltype(arr)::*funPtr)(int) const;
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f6(some_other_namespace::not_an_array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);

  sink(arr.operator[](0));
  sink(arr.operator[](source()));

  int& (decltype(arr)::*funPtr)(int);
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f7(const some_other_namespace::not_an_array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);

  sink(arr.operator[](0));
  sink(arr.operator[](source()));

  const int& (decltype(arr)::*funPtr)(int) const;
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f8(my_array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'my_array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'my_array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  sink(arr.operator[](42));
  sink(arr.operator[](source()));
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'my_array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'my_array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  int& (decltype(arr)::*funPtr)(int);
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f9(const my_array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'my_array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'my_array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  sink(arr.operator[](0));
  sink(arr.operator[](source()));
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'my_array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of 'my_array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  const int& (decltype(arr)::*funPtr)(int) const;
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f10(array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of '(anonymous namespace)::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of '(anonymous namespace)::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  int& (decltype(arr)::*funPtr)(int);
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr.operator[](0));
  sink(arr.operator[](source()));
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of '(anonymous namespace)::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of '(anonymous namespace)::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}

void f11(const array<int, 2> arr) {
  sink(arr[0]);
  sink(arr[source()]);
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of '(anonymous namespace)::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of '(anonymous namespace)::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  sink(arr.operator[](0));
  sink(arr.operator[](source()));
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of '(anonymous namespace)::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}
  // CHECK-MESSAGES: :[[@LINE-2]]:8: warning: Do not access elements of '(anonymous namespace)::array' via 'operator[]', use 'Array1DRef' / 'Array2DRef' abstractions [rawspeed-std-array-no-operator-at]{{$}}

  const int& (decltype(arr)::*funPtr)(int) const;
  (arr.*funPtr)(0);
  (arr.*funPtr)(source());

  sink(arr * 0);
  sink(arr * source());

  sink(arr.operator*(0));
  sink(arr.operator*(source()));
}
