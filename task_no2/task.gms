Sets
    i /C1*C7/;
alias(i, j);
*alias(i, intermediate);
Parameters
    a(i, j)
    d(i, j);
Scalar z;

a(i, j) = round(uniform(1, 150));
d(i, j) = round(uniform(1, 50));
z = round(uniform(50, 60));

loop(i, d(i, i) = 0;);
loop(i, a(i, i) = 0;);

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
    source
    legit(i, j)
    balance(i)
    sink;
*    noloop(i);
cost ..     f =e= sum((i, j), a(i, j)*x(i, j));
* целевая функция, умножаем поток на дугах на коэффициент стоимостей
source ..   z =e= sum((i, j)$i.first, x(i, j));
* из источника вышло z
sink ..   z =e= sum((i, j)$j.last, x(i, j));
* в сток зашло z
legit(i, j) ..    x(i, j) =l= d(i, j);
* допустимость, неотрицательность дуги уже проверена, так как разрешены только неотрицательные переменные
balance(i)$(not i.last and not i.first) ..  sum(j, x(j, i)) =e= sum(j, x(i, j) );
* баланс для остальных дуг 
*noloop(i) ..   x(i, i) =e= 0;

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