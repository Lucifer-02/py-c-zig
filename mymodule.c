// #include <Python.h>
#include "python3.10/Python.h"

// Function to add two numbers
static PyObject *add_numbers(PyObject *self, PyObject *args) {
  int a, b, result;

  // Parse the Python arguments (two integers)
  if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
    return NULL;
  }

  // Perform the addition
  result = a + b;

  // Return the result as a Python object
  return PyLong_FromLong(result);
}

// Function to calculate the sum of a list of integers
static PyObject *sum_list(PyObject *self, PyObject *args) {
  PyObject *listObj;
  if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &listObj)) {
    return NULL; // Parsing failed
  }

  // Ensure the input is a list
  Py_ssize_t list_size = PyList_Size(listObj);
  long sum = 0;

  for (Py_ssize_t i = 0; i < list_size; i++) {
    PyObject *item = PyList_GetItem(listObj, i);
    if (!PyLong_Check(item)) {
      PyErr_SetString(PyExc_TypeError, "List elements must be integers");
      return NULL;
    }
    sum += PyLong_AsLong(item);
  }

  return PyLong_FromLong(sum);
}

// Method definitions
static PyMethodDef MyMethods[] = {
    {"add_numbers", add_numbers, METH_VARARGS, "Add two numbers"},
    {"sum_list", sum_list, METH_VARARGS,
     "Calculate the sum of a list of integers"},
    {NULL, NULL, 0, NULL} // Sentinel
};

// Module definition
static struct PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    "mymodule",         // Module name
    "Example C module", // Module documentation
    -1,                 // Module state (-1 for global state)
    MyMethods           // Methods
};

// Module initialization
PyMODINIT_FUNC PyInit_mymodule(void) { return PyModule_Create(&mymodule); }
