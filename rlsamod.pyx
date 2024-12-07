import numpy as np
cimport numpy as np
from cpython cimport PyObject
np.import_array()
import cython

cdef extern from "wrapper.h":
    cdef int* rlsa_smear_c(int* img, long int rows, long int cols, int r)


cpdef rlsa_helper(img, rows, cols, r):
    arr_view = cython.declare(cython.int[:], img)
    cdef int* out 
    out = rlsa_smear_c(&arr_view[0], rows, cols, r)
    cdef np.ndarray[int, ndim=1] B = np.PyArray_SimpleNewFromData(1, [rows * cols], np.NPY_INT32, out)
    return B.copy()


def rlsa(img, r):
    h, w = img.shape
    out = rlsa_helper(img.ravel(), h, w, r)
    return np.reshape(out, (h, w))


 

