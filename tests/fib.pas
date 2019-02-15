var l:boolean;
a,b:integer;

function fib(n: integer):integer;
var temp:integer;
begin

    temp := n;
    while (temp = 1) or (temp = 0) do
    begin
	fib := 1;
	temp := -1;
    end;

    while (temp > 1) do
    begin

	fib:=fib(temp - 1) + fib (temp - 2);

    temp := -1;
    end;

end;

begin
b:=write(Vvedite a:);
a:=readln();

a:=fib(a);

b:=write(Result:);
b:=writeln(a);

end.