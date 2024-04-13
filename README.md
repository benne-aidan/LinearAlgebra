# LinearAlgebra
C library to solve common Linear Algebra problems implemented with basic text-based UI. 

**NOTE**: This description (and this project) is far from complete and still being worked on.

## Custom datatypes
So far the only custom datatype to be implemented is the `Matrix` datatype. It stores elements in a single dimensional, dynamically allocated array that can be accessed and modified using associated functions. Its data members include `numRows` and `numCols` to hold the number of rows and columns (respectively), the list of elements (`elements`), as well as an `identifier` unique to each `Matrix` for the purpose of identifying matrices from a list. I plan to later add a vector datatype, which is essentially a $1\times n$ matrix.

## Functions
### Matrix modifiers and accessors
The `Matrix` datatype has numerous functions to easily create, access and modify matrices.
The most used functions are detailed below.

`Matrix_initialize()`:
Returns type `Matrix` initialized with requested parameters, creates empty list for elements.

`Matrix_populate()`:
Void function, fills parameter `Mat` with list `elements` of size `listSize`.

`Matrix_elementAt()`:
Returns pointer to element at position `row`, `col` of `mat`. Pointer return type allows function to be used to modify element using `Matrix_elementChangeTo()`.
