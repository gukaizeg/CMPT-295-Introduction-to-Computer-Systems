#include <acutest.h>
#include <stdint.h>
#include <arraylist.h>

struct TestVector
{
  const index;
  const char *name;
  const char *output;
};

struct TestVector test_vectors[] = {
    // Inorder,Preorder,Postorder(Expected)
    {0, "Add:1-5", "[0, 1, 2, 3, 4, 5]\n"},
    {1, "Add:1-3,Insert:100:0-3", "[0, 1, 2, 3]\n\
[100, 0, 1, 2, 3]\n\
[0, 1, 2, 3]\n"},
    {2, "Add:1-5,Insert:100:0-6,Free", "[0, 1, 2, 3, 4, 5]\n\
[100, 0, 1, 2, 3, 4, 5]\n\
[0, 100, 1, 2, 3, 4, 5]\n\
[0, 1, 100, 2, 3, 4, 5]\n\
[0, 1, 2, 100, 3, 4, 5]\n\
[0, 1, 2, 3, 100, 4, 5]\n\
[0, 1, 2, 3, 4, 100, 5]\n\
[0, 1, 2, 3, 4, 5]\n"}};

void test2(void)
{
  struct TestVector *vec = &test_vectors[2];
  /* Output the name of the tested test vector. */
  TEST_CASE(vec->name);

  char output[10000];
  int pos = 0;

  // START OF TEST
  arraylist *a = arraylist_new();
  int ints[] = {0, 1, 2, 3, 4, 5, 100};

  arraylist_add(a, ints);
  arraylist_add(a, ints + 1);
  arraylist_add(a, ints + 2);
  arraylist_add(a, ints + 3);
  arraylist_add(a, ints + 4);
  arraylist_add(a, ints + 5);
  arraylist_output(a, output, &pos);

  for (unsigned int i = 0; i < a->length; i++)
  {
    arraylist_insert(a, i, ints + 6);
    //    printf("Insert position %d: ", i);
    arraylist_output(a, output, &pos);
    arraylist_remove(a, i);
  }
  // //  printf("Clean: ");
  arraylist_output(a, output, &pos);

  output[pos] = '\0';
  //  printf("%s", output);
  TEST_CHECK(!strcmp(vec->output, output));
  TEST_MSG("Expected: %s", vec->output);
  TEST_MSG("Produced: %s", output);

  arraylist_free(a);
}

void test0(void)
{
  struct TestVector *vec = &test_vectors[0];
  /* Output the name of the tested test vector. */
  TEST_CASE(vec->name);

  char output[10000];
  int pos = 0;

  // START OF TEST
  arraylist *a = arraylist_new();
  int ints[] = {0, 1, 2, 3, 4, 5};

  arraylist_add(a, ints);
  arraylist_add(a, ints + 1);
  arraylist_add(a, ints + 2);
  arraylist_add(a, ints + 3);
  arraylist_add(a, ints + 4);
  arraylist_add(a, ints + 5);
  arraylist_output(a, output, &pos);

  output[pos] = '\0';
  //  printf("%s", output);
  TEST_CHECK(!strcmp(vec->output, output));
  TEST_MSG("Expected: %s", vec->output);
  TEST_MSG("Produced: %s", output);

  // arraylist_free(a);
}

void test1(void)
{
  struct TestVector *vec = &test_vectors[1];
  /* Output the name of the tested test vector. */
  TEST_CASE(vec->name);

  char output[10000];
  int pos = 0;

  // START OF TEST
  arraylist *a = arraylist_new();
  int ints[] = {0, 1, 2, 3, 4, 5, 100};

  arraylist_add(a, ints);
  arraylist_add(a, ints + 1);
  arraylist_add(a, ints + 2);
  arraylist_add(a, ints + 3);
  arraylist_output(a, output, &pos);

  for (unsigned int i = 0; i < 1; i++)
  {
    arraylist_insert(a, i, ints + 6);
    arraylist_output(a, output, &pos);
    arraylist_remove(a, i);
  }
  // //  printf("Clean: ");
  arraylist_output(a, output, &pos);

  output[pos] = '\0';

  TEST_CHECK(!strcmp(vec->output, output));
  TEST_MSG("Expected: %s", vec->output);
  TEST_MSG("Produced: %s", output);

  // arraylist_free(a);
}

TEST_LIST = {{"Test 0", test0}, {"Test 1", test1}, {"Test 2", test2}, {NULL, NULL}

};

//