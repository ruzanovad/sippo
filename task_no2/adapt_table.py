import simplex.simplex as simplex
import time
from fractions import Fraction
from tabulate import tabulate

with open("Problem.txt", "r") as file:
    n = int(file.readline().strip())
    A_ij = []
    for i in range(n):
        A_ij.append([Fraction(j) for j in file.readline().strip().split(" ")])
        # print(*A_ij[-1])
    file.readline()
    D_ij = []
    for i in range(n):
        D_ij.append([Fraction(j) for j in file.readline().strip().split(" ")])
    
    Z = Fraction(file.readline().strip())
    variables = [["x_{%d%d}" % (i+1, j+1)  for j in range(n)]for i in range(n)]
    function = []
    for i in range(n):
        function+=A_ij[i]
    function.insert(0, Fraction(0))
    function.append('min')
    func = simplex.Function(function)
    
    number_of_restrictions = n

    restrictions = [simplex.Restriction([0]+[1 for i in range(n-1)] + [0 for i in range(n*(n-1))] + ['=', Z])]
    for i in range(1, n-1):
        basematrix = [[0 for j in range(n)]for k in range(n)]
        for j in range(n):
            if j != i:
                basematrix[i][j] = 1
                basematrix[j][i] = -1
        matr = []
        for j in basematrix:
            matr+=j
        matr+=['=', '0']
        restrictions.append(simplex.Restriction(
            matr
        ))
    number_of_soft_restrictions = n*n
    soft_restrictions = [simplex.Inequality.GREATEREQ for i in range(n*n)]

    number_of_restrictions = n*n
    # restrictions = []
    for i in range(n):
        for k in range(n):
            basematrix = [[0 for j in range(n)]for k in range(n)]
            basematrix[i][k] = 1
            
            matr = []
            for j in basematrix:
                matr+=j
            matr+=['<=', D_ij[i][k]]
            restrictions.append(simplex.Restriction(
                matr
            ))
    problem = simplex.Problem(func, restrictions, soft_restrictions)
    # problem.variables = variables


    t = time.time_ns()
    # assert not problem.check_canon()
    print(problem)
    problem.make_canon(False)
    # assert problem.check_canon()
    print(problem)
    print(problem.check_reduced())
    # print(problem)
    # assert problem.check_reduced()
    obj = simplex.SimplexTable.artificial_basis(problem, True)
    print(obj)
    obj.make_function_nonbasis()
    print(obj)
    table = []

    basis = problem.get_basis()
    table.append(["B"] + ["x_0"] + problem.variables)
        # print(*table[0])
    table.append([func, obj.function.c] +
                    [-i for i in problem.function.array])
    for i in range(len(basis)):
        row = [obj.variables[basis[i][0]],
                obj.restrictions[i].b]
        row += obj.restrictions[i].coefs
        table.append(row)
        # print(row)
    print(tabulate(table, headers='firstrow',
                      tablefmt='grid', disable_numparse=True))
    obj = simplex.SimplexTable.simplex_method(obj,'C')
    
    print("GAMS vector:\n %s" % ' '.join(list(filter(lambda x: x.strip() !='\n',open("Result.txt", "r").readlines()[:-1]))))
    print("Custom simplex time: %d ms" % ((time.time_ns()-t)/1000000))
    print("GAMS time: %s ms" % open("Result.txt", "r").readlines()[-1][:-1])
    # print(obj)


