
matrix = [[1, 1, 1, 0, 0, 0],
          [0, 1, 0, 0, 0, 0],
          [1, 1, 1, 0, 0, 0],
          [0, 0, 2, 4, 4, 0],
          [0, 0, 0, 2, 0, 0],
          [0, 0, 1, 2, 4, 0]]

sub = []

for iline in range(3):
          line = []
          for jcol in range(3):
                    line.append(matrix[iline][jcol])
          sub.append(line)

print(sub)

print(len(matrix[0]))

def submat(mat, n, m):
          '''
          from a square matrix, returns a list of n x n submatrices
          '''
          if len(mat) == 0:
                    return None

          N = len(mat)
          M = len(mat[0])

          mat_list = []

          for j in range(M-m+1):
                    for i in range(N-n+1):
                              mat = []
                              for iline in range(i+3):
                                        line = []
                                        for jcol in range(j+3):
                                                  line.append(matrix[iline][jcol])
                                        mat.append(line)
                              mat_list.append(mat)
          return mat_list

mat_list = submat(matrix, 3, 3)
print('---- \n')
for mat in mat_list:
          print(mat, '\n')
