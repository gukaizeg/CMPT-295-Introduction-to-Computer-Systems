import random


SIZE = 256
VLEN = 8;

l = [random.randint(-100,100)
     for i in range(SIZE)]
m = [max(0,i) for i in l]



for i in range (0, 8):
    l.append(0x1eadbeef)

def print_arr(array_type, array_name, array_sz, pyarr):
  print( "{} {}[{}] = ".format(array_type, array_name, array_sz))
  print( "{")
  print(", ".join(map(str, pyarr)))
  print( "};")


print( "#define SIZE {}".format(SIZE))
print_arr("int", "input_data", "SIZE+"+str(VLEN), l)
print_arr("int", "gold", "SIZE+"+str(VLEN), m)
