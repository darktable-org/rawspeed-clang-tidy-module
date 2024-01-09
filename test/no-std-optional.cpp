// RUN: %check_clang_tidy -std=c++17-or-later %s rawspeed-no-std-optional %t

namespace std {

template <typename T> class optional {
public:
  optional() = default;

  template <typename U> optional(U);
};

template <typename T> class not_an_optional {
public:
  not_an_optional() = default;

  template <typename U> not_an_optional(U);
};

template <typename T> struct tuple {
  T t;
};

}; // namespace std

namespace some_other_namespace {

template <typename T> class optional {
public:
  optional() = default;

  template <typename U> optional(U);
};

template <typename T> class not_an_optional {
public:
  not_an_optional() = default;

  template <typename U> not_an_optional(U);
};

template <typename T> struct tuple {
  T t;
};

}; // namespace some_other_namespace

template <typename T> using my_optional_alias = std::optional<T>;

namespace {

template <typename T> class my_another_optional : public std::optional<T> {
// CHECK-MESSAGES: :[[@LINE-1]]:58: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
public:
  my_another_optional() = default;

  template <typename U> my_another_optional(U);
};

} // namespace

//------------------------------------------------------------------------------

std::optional<int> f0_return_type() {}
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
void f0_argument_type(std::optional<int>) {}
// CHECK-MESSAGES: :[[@LINE-1]]:23: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
std::tuple<std::optional<int>> f0_other_return_type() {}
// CHECK-MESSAGES: :[[@LINE-1]]:12: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}

struct S0 {
  std::optional<int> f;
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  std::optional<int> a, b;
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
};

void exprrs_f0() {
  std::optional<int>(1);
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  std::optional<int> a(1);
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  std::optional<int> b = 1;
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}

  f0_argument_type(1);
  f0_argument_type(std::optional<int>(1));
// CHECK-MESSAGES: :[[@LINE-1]]:20: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  auto c = f0_return_type();
  auto [d] = f0_other_return_type();
}

//------------------------------------------------------------------------------

std::not_an_optional<int> f1_return_type() {}
void f1_argument_type(std::not_an_optional<int>) {}
std::tuple<std::not_an_optional<int>> f1_other_return_type() {}

struct S1 {
  std::not_an_optional<int> f;
  std::not_an_optional<int> a, b;
};

void exprrs_f1() {
  std::not_an_optional<int>(1);
  std::not_an_optional<int> a(1);
  std::not_an_optional<int> b = 1;

  f1_argument_type(1);
  f1_argument_type(std::not_an_optional<int>(1));
  auto c = f1_return_type();
  auto [d] = f1_other_return_type();
}

//------------------------------------------------------------------------------

some_other_namespace::optional<int> f2_return_type() {}
void f2_argument_type(some_other_namespace::optional<int>) {}
some_other_namespace::tuple<some_other_namespace::optional<int>>
f2_other_return_type() {}

struct S2 {
  some_other_namespace::optional<int> f;
  some_other_namespace::optional<int> a, b;
};

void exprrs_f2() {
  some_other_namespace::optional<int>(1);
  some_other_namespace::optional<int> a(1);
  some_other_namespace::optional<int> b = 1;

  f2_argument_type(1);
  f2_argument_type(some_other_namespace::optional<int>(1));
  auto c = f2_return_type();
  auto [d] = f2_other_return_type();
}

//------------------------------------------------------------------------------

some_other_namespace::not_an_optional<int> f3_return_type() {}
void f3_argument_type(some_other_namespace::not_an_optional<int>) {}
some_other_namespace::tuple<some_other_namespace::not_an_optional<int>>
f3_other_return_type() {}

struct S3 {
  some_other_namespace::not_an_optional<int> f;
  some_other_namespace::not_an_optional<int> a, b;
};

void exprrs_f3() {
  some_other_namespace::not_an_optional<int>(1);
  some_other_namespace::not_an_optional<int> a(1);
  some_other_namespace::not_an_optional<int> b = 1;

  f3_argument_type(1);
  f3_argument_type(some_other_namespace::not_an_optional<int>(1));
  auto c = f3_return_type();
  auto [d] = f3_other_return_type();
}

//------------------------------------------------------------------------------

my_optional_alias<int> f4_return_type() {}
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
void f4_argument_type(my_optional_alias<int>) {}
// CHECK-MESSAGES: :[[@LINE-1]]:23: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
std::tuple<my_optional_alias<int>> f4_other_return_type() {}
// CHECK-MESSAGES: :[[@LINE-1]]:12: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}

struct S4 {
  my_optional_alias<int> f;
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  my_optional_alias<int> a, b;
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
};

void exprrs_f4() {
  my_optional_alias<int>(1);
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  my_optional_alias<int> a(1);
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  my_optional_alias<int> b = 1;
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}

  f4_argument_type(1);
  f4_argument_type(my_optional_alias<int>(1));
// CHECK-MESSAGES: :[[@LINE-1]]:20: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  auto c = f4_return_type();
  auto [d] = f4_other_return_type();
}

//------------------------------------------------------------------------------

my_another_optional<int> f5_return_type() {}
// CHECK-MESSAGES: :[[@LINE-1]]:1: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
void f5_argument_type(my_another_optional<int>) {}
// CHECK-MESSAGES: :[[@LINE-1]]:23: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
std::tuple<my_another_optional<int>> f5_other_return_type() {}
// CHECK-MESSAGES: :[[@LINE-1]]:12: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}

struct S5 {
  my_another_optional<int> f;
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  my_another_optional<int> a, b;
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
};

void exprrs_f5() {
  my_another_optional<int>(1);
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  my_another_optional<int> a(1);
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  my_another_optional<int> b = 1;
// CHECK-MESSAGES: :[[@LINE-1]]:3: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}

  f5_argument_type(1);
  f5_argument_type(my_another_optional<int>(1));
// CHECK-MESSAGES: :[[@LINE-1]]:20: warning: Do not use 'std::optional' directly, use 'Optional' wrapper [rawspeed-no-std-optional]{{$}}
  auto c = f5_return_type();
  auto [d] = f5_other_return_type();
}

//------------------------------------------------------------------------------
