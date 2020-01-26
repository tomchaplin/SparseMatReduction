# Sparse Matrix Reduction

This is a small program for executing the 'Sparse Matrix Reduction' algorithm presented in Computational Topology: an introduction [1].
It also keeps track of simplex pairings and can subsequently compute Betti numbers.
All calculations are done over Z/2Z as in Computation Topology [1].

## Usage

Your simplicial complex boundary map should be provided in sparse matrix format stored in some file ``complex.dat``.
Each line represents a column of the boundary matrix by listing the rows containing a 1 (as opposed to a 0).
Equivalently, each line represents a simplex by listing the indices of its boundary simplicies.
These indices should be provided in decreasing order.
Further, the first field in each line should be the dimension of the simplex represented by that column.
Numbers should be separated by a single comma ``,`` with no spaces.

Then make sure the software is complied by running
```
make
```
Then run the code with
```
./main complex.dat
```
Output can be saved by redirecting ``STDOUT``
```
./main complex.dat > complex_out.dat
```

Example inputs are provided in the ``inputs/`` folder.

# References
[1] Edelsbrunner, Herbert, and John Harer. Computational topology: an introduction. American Mathematical Soc., 2010.
