# Solution description

## Description of the problem
 
Having a set of ranges, we want to count the number of ranges that contain an input number


## Description of the solution

The idea is to increment a counter whenever a range opens and decrement it whenever a range closes

The sum of the counter value will indicate the number of ranges that contain the input value

### Example

Input ranges:
12 14
13 17
16 20

12 -> +1
14 -> -1
13 -> +1
17 -> -1
16 -> +1
20 -> -1

In a sorted array:

| 12 | 13 | 14 | 16 | 17 | 20 |
|----|----|----|----|----|----|
| +1 | +1 | -1 | +1 | -1 | -1 |

Let x = 16.5
count = 1 + 1 - 1 = 2

### Fast query

A simple optimization is to keep a partial sum array so that the count array has not to be looped over at each query

| 12 | 13 | 14 | 16 | 17 | 20 |
|----|----|----|----|----|----|
| +1 | +1 | -1 | +1 | -1 | -1 |
| +1 | +2 | +1 | +2 | +1 | 0  |


## Description of main components and complexity analysis 

`range_db` is the main component. It saves in RAM the values of the ranges and keep track of the counter.

Let N be the number of ranges in the input ranges files

- Reading from range file is O(N log N) time complexity and O(N) space complexity
- querying the db is O(1)

## Description of point of failure and possible enhancements 

* The initialisation of the database requires to load the full input file content into RAM memory with a possible 
"out of memory" exception being thrown if the file is large.  A possible enhancement would be to split the input 
file into bunch of ranges to be read, e.g 1000 and use a temporary file to write the arrays (described in the previous
 example). Once all the ranges have been read, a (real) database could be created by merging the temporary files.

* the internal data structure that is used for the implementation uses comparison operator on floating point values. 
This might create some unexpected result if all the range values are very close to each other (~ 10^{-15})