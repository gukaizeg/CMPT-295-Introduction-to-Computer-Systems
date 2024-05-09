import os
import sys
import argparse
import numpy as np
import scipy.sparse



def read_sparse(filename):
    with open(filename, "rb") as handle:
        rows = int.from_bytes(handle.read(4), byteorder="little")
        cols = int.from_bytes(handle.read(4), byteorder="little")
        nnz = int.from_bytes(handle.read(4), byteorder="little")
        row = []
        col = []
        val = []
        for i in range(nnz):
            row.append(int.from_bytes(handle.read(4), byteorder="little"))
            col.append(int.from_bytes(handle.read(4), byteorder="little"))
            val.append(int.from_bytes(handle.read(4), byteorder="little", signed=True))
    sp_matrix = scipy.sparse.coo_matrix((val, (row,col)), shape=(rows, cols), dtype=np.int32)
    return sp_matrix

def read_dense(filename):
    with open(filename, "rb") as handle:
        rows = int.from_bytes(handle.read(4), byteorder="little")
#         # print(int.from_bytes(rows, byteorder='little'))
        cols = int.from_bytes(handle.read(4), byteorder="little")
#         # print(int.from_bytes(cols, byteorder='little'))
        data = np.empty(shape=(rows, cols),dtype=np.int32)
        for i in range(rows):
            for j in range(cols):
                data[i, j] = int.from_bytes(
                    handle.read(4), byteorder="little", signed=True)
    return data


def print_dense(dense_matrix):
    for i in range(dense_matrix.shape[0]):
        for j in range(dense_matrix.shape[1]):
            print(dense_matrix[i, j], end=" ")
        print("")

def matmul(mat1, mat2):
    result = np.empty(shape=(mat1.shape[0], mat2.shape[1]))
    for i in range(mat1.shape[0]):
        for j in range(mat2.shape[1]):
            for k in range(mat1.shape[1]):
                result[i, j] += mat1[i, k]*mat2[k, j]
    return result


def main():
    # print(sys.argv[1])
    input = read_dense(sys.argv[1])
    m = read_dense(sys.argv[2])
    hidden1 = m.dot(input)
    print("\n**Step result = gemv(matrix, vector)**")
    print_dense(hidden1)

if __name__ == "__main__":
    main()
