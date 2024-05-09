import random


SIZE = 96
VLEN = 8;

l = [random.getrandbits(16) for i in range(SIZE)]
m = sum(l)


for i in range (0, 8):
    l.append(0x1eadbeef)

def print_arr(array_type, array_name, array_sz, pyarr):
  print( "{} {}[{}] = ".format(array_type, array_name, array_sz))
  print( "{")
  print(", ".join(map(str, pyarr)))
  print( "};")


print( "#define SIZE {}".format(SIZE))
print( "int sum = {};".format(m))
print_arr("int", "input_data", "SIZE+"+str(VLEN), l)
