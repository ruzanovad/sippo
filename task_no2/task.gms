Sets
    i /C1*C4/;
alias(i, j);
Parameters
    a(i, j)
    d(i, j);
Scalar z;

a(i, j) = round(uniform(1, 150));
d(i, j) = round(uniform(2, 60));
z = round(uniform(1, 100));

file probl /Problem.txt/;
put probl;
put /"Матрица стоимостей"/;
loop(i,
    loop(j,
        put a(i, j):4:0 " ";
        );
    put ""/;
);
put /"Матрица пропускных способностей"/;
loop(i,
    loop(j,
        put d(i, j):4:0 " ";
        );
    put ""/;
);

put /"Количество МБайт"/;
put z ""/;

putclose probl;
Variables
    x(i, j)
    f;
Positive Variable x;
Equations
    cost
    supply
    legit(i, j)
    balance(i)
    noloop(i);
cost ..     f =e= sum((i, j), a(i, j)*x(i, j));
supply ..   z =e= sum(j, x('C1', j));
*demand ..   z =e= sum(i, x(i, 'C10'));
legit(i, j) ..    x(i, j) =l= d(i, j);
balance(i) ..  sum(j, x(j, i)) =e= sum(j, x(i, j));
noloop(i) ..   x(i, i) =e= 0



Model stream /all/;
Solve stream using LP minimizing f;

file out /Result.txt/;
put out;
loop(i,
        loop(j, put x.l(i,j):4:0 " ";
        );
         put ""/;
    );
putclose out;