// RUN: %check_clang_tidy %s rawspeed-hello-world %t

namespace NS {
// CHECK-MESSAGES: :[[@LINE-1]]:11: warning: Hello world!
}
