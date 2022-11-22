import numpy
array=numpy.zeros(10)
print("array of 10 zeros:")
print(array)
array=numpy.ones(10)
print("array of 10 ones:")
print(array)
array=numpy.ones(10)*5
print("array of 10 fives:")
print(array)

print("creating a 2D array of 3x4 size ")
numbers= numpy.arange(10,22).reshape((3, 4))
print(numbers)

import os
y = numpy.arange(12).reshape(4, 3)
print("array made:")
print(y)
header = ' col1  col2  col3'
numpy.savetxt('file.txt', y, fmt="%d", header=header)
print("file content after loading")
result = numpy.loadtxt('file.txt')
print(result)