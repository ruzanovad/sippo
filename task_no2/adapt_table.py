import simplex
with open("Problem.txt", "r") as file:
    n = int(file.readline().strip())
    A_ij = []
    for i in range(n):
        A_ij.append([simplex.Fraction(j) for j in file.readline().strip().split(" ")])
    D_ij = []
    for i in range(n):
        A_ij.append([simplex.Fraction(j) for j in file.readline().strip().split(" ")])
    
    Z = int(file.readline().strip())
    
    variables = [["x_{%d%d}" % (i+1, j+1)  for j in range(n)]for i in range(n)]
    function = []
    for i in range(n):
        function+=A_ij[i]
    function.insert(0, simplex.Fraction(0))
    function.append('min')
    func = simplex.Function(function)
    
    number_of_restrictions = n

    restrictions = [simplex.Restriction([0]+[1 for i in range(n-1)] + [0 for i in range(n*(n-1))] + ['=', Z])]
    for i in range(1, n):
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
    restrictions = []
    for i in range(n):
        for k in range(n):
            basematrix = [[0 for j in range(n)]for k in range(n)]
            basematrix[i][k] = 1
            matr+=['<=', D_ij[i][k]]
            restrictions.append(simplex.Restriction(
                matr
            ))
    problem = simplex.Problem(func, restrictions, soft_restrictions)
    problem.variables = variables

    assert not problem.check_canon()
    # print(problem)
    problem.make_canon(False)
    assert problem.check_canon()
    # print(problem)
    assert problem.check_reduced()
    print("Базис: %s" % (problem.get_basis()))
    x, y = simplex.SimplexTable.simplex_method(problem,'C',False, True,False)
    print(*x, y)


