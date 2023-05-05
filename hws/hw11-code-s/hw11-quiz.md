HW 11 Quiz

# 1
Which of the following best describes how the `matrix_t` type in the lab stores numerical matrices?

( ) The 2D matrix is stored as a 2D array in the field data; this allows direct access via 2D indexing via `mat.data[i][j]`
( ) The type `matrix_t` is defined as the same as a `int[][]` so the 2D data can be directly accessed via `mat[i][j]`
(X) The 2D matrix is stored as a 1D array in the mat.data field. 2D accesses like `(i,j)` must be translated to 1D locations via the formula `mat.data[i*mat.cols) + j]`
( ) The 2D matrix is stored in a hash table with the `mat.data` field storing data and a hashing function used to compute the 1D location of a 2D element.

# 2
The code provided in matvec.h provides the following easy method to access and change elements of a `matrix_t`.

( ) The functions `MGET(mat,i,j)` and `MSET(mat,i,j,x)` are implemented in the header to get and set elements of a `matrix_t`
(X) The macros `MGET(mat,i,j)` and `MSET(mat,i,j,x)` are `#define`'d in the header to get and set elements of a `matrix_t`
( ) Instructions are given about what formula and fields to use when accessing and changing elements of the matrix.
( ) No easy way is given for to work with the `matrix_t` type or its elements.

# 3
How does one access the number of rows and columns in a matrix that is stored in a '`matrix_t`' type?

( ) Code iterates through the matrix to count its elements in order to determine the number of rows and columns.
( ) There are macros that will calculate the number of rows and columns for a `matrix_t`
( ) The `mat.data` field stores the rows and columns in it as all C arrays store their size.
(X) The `matrix_t` struct has fields mat.rows and mat.cols contain the number of rows and columns

# 4
Which of the following best describes the `vector_t` that is provided in the lab?

(X) It is a struct which has a `vec.data` field which is an array and a `vec.length` field which is the length of the array.
( ) It is the same as the `int[]` type so is a 1D array.
( ) It is a struct which has a `vec.data` field which is a 2D array and fields `vec.rows` and `vec.cols` which track the size of the vector.
( ) It is an extensible array type with a `vec.push_back()` method to append data to it.

# 5
The HW asked that the timing difference between
- Calculating sums of each ROW for a matrix
- Calculating the sums of each COLUMN for a matrix

The result of this timing indicated the following relative speeds of these two provided algorithms.

( ) Summing ROWS was SLOWER than summing COLUMNS
( ) Summing ROWS was the SAME speed as summing COLUMNS
(X) Summing ROWS was FASTER than summing COLUMNS

# 6
What primary factor accounted for the relative speeds of summing rows versus summing columns in the provided algorithms?

( ) The two algorithms had equal speed as they perform the same number of operations and have the same `O(R*C)` complexity.
(X) Row Summing was Faster because it accessed memory sequentially while Column summing jumped around in memory leading to poor cache performance.
( ) Column Summing was Faster because it accessed memory sequentially while Row summing jumped around in memory leading to poor cache performance.
( ) Column summing was slower because the Row summing algorithm exhibited better processor pipelining features allowing more instructions per cycle to be executed.

# 7
Which option below best describes the potential to calculate column sums at the same speed as row sums using custom-written code?

(X) It is POSSIBLE to calculate column sums quickly by accessing memory in the same sequential fashion as the row sums algorithm.
( ) It is POSSIBLE to calculate column sums quickly by improving the instruction pipelining for column sums similar to the row sums approach.
( ) It is NOT possible to calculate column sums as fast as row sums as they require visiting memory in different orders.
( ) Both methods already run at the same speed so no special approach is needed to sum columns differently than rows.

# 8
Predict the relative speed of the following nested two loops which compute how many non-zero elements are in a `matrix_t`.

```c
  // LOOP 1
  int nonzeros = 0;
  for(int j=0; j<mat.cols; j++){
    for(int i=0; i<mat.rows; i++){
      nonzeros += MGET(mat,i,j) != 0;
    }
  }
  
  // LOOP 2
  int nonzeros = 0;
  for(int i=0; i<mat.rows; i++){
    for(int j=0; j<mat.cols; j++){
      nonzeros += MGET(mat,i,j) != 0;
    }
  }
```

(X) Loop 1 will run SLOWER than Loop 2
( ) Loop 1 will run at the SAME speed as Loop 2
( ) Loop 1 will run FASTER than Loop 2

# 9
Within the benchmarking code `matsums_main.c`, what function is used to time specific sections of the code so that differing times for the row and column sum approaches can be reported?

( ) `time()`
(X) `clock()`
( ) `stat()`
( ) `getrusage()`

# 10
What general feature of the memory system affects performance of programs?

( ) Accessing memory is uniformly fast; all orders of visiting memory cells will result in the same speed.
( ) Accessing memory in increasing addresses is faster than accessing it in decreasing addresses.
(X) Accessing memory sequentially is faster and will lead to better performance than accessing it out of order
( ) It is never possible for a program with a bad memory access pattern to be improved.
