import scipy.sparse
import numpy as np
import scipy.io as sio
import sys
import argparse

def main():
    parser = argparse.ArgumentParser(description="Converts between ascii and binary files representing integer matrices")
    parser.add_argument("input_file", help="file to read from")
    parser.add_argument("output_file", help="file to write to")

    args = parser.parse_args()


    filename = args.input_file
    with open(filename, "rb") as handle:
        rows = int.from_bytes(handle.read(4), byteorder="little")
    #        # print(int.from_bytes(rows, byteorder='little'))
        cols = int.from_bytes(handle.read(4), byteorder="little")
    #        # print(int.from_bytes(cols, byteorder='little'))
        data = np.empty(shape=(rows, cols))
        for i in range(rows):
            for j in range(cols):
                data[i, j] = int.from_bytes(
                    handle.read(4), byteorder="little", signed=True)
    #    data = ([[-1, 2, 0], [0, 0, 3], [4, 0, 5]])
        sparse_matrix = scipy.sparse.coo_matrix(data,dtype=np.int32)
        with open(args.output_file, "wb") as handle2:
            handle2.write(sparse_matrix.shape[0].to_bytes(4, byteorder="little"))
            handle2.write(sparse_matrix.shape[1].to_bytes(4, byteorder="little"))
            handle2.write(sparse_matrix.nnz.to_bytes(4, byteorder="little"))
            for i,j,v in zip(sparse_matrix.row, sparse_matrix.col, sparse_matrix.data):
                handle2.write(i.item().to_bytes(4, 'little'))
                handle2.write(j.item().to_bytes(4, 'little'))
                handle2.write(v.item().to_bytes(4, 'little',signed=True))
            handle2.close()

if __name__ == "__main__":
    main()
