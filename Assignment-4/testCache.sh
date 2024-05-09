#!/bin/bash
if [ -f ./cache-test ]
then
  rm cache-test
fi

echo
echo "Provided Cache TESTS: "
echo
echo "Mystery 0:"
echo
rm cache-test
make cache-test TEST_CACHE=caches/mystery0.o
./cache-test
echo
echo "Mystery 1:"
echo
rm cache-test
make cache-test TEST_CACHE=caches/mystery1.o
./cache-test
echo
echo "Mystery 2: "
echo
rm cache-test
make cache-test TEST_CACHE=caches/mystery2.o
./cache-test
echo
echo "Finished."
echo
rm cache-test
