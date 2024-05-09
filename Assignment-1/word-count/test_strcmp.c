#include <acutest.h>
#include <stdint.h>
#include <str_cmp.h>

struct TestVector {
  const index;
  const char *s1;
  const char *s2;
  int expected;
};

struct TestVector test_vectors[] = {
    // Inorder,Preorder,Postorder(Expected)
    {0, "a", "b", 1},
    {1, "apple", "appl@ ", 1},
    {2, "apple and oranges", "apple and oranges", 0},
    {3, "123456", "123456", 0},
    {4, "342342;", "afasdfsafd;", 1}};

void test(void) {
  for (int i = 0; i < 5; i++) {
    int result = my_str_cmp(test_vectors[i].s1, test_vectors[i].s2);

    TEST_CHECK(result == test_vectors[i].expected);
    TEST_MSG("String s1: %s", test_vectors[i].s1);
    TEST_MSG("String s2: %s", test_vectors[i].s2);
  }
}

TEST_LIST = {{"Test", test}, {NULL, NULL}};
