function fac (i:integer):integer ;

  function const_func(l:boolean):boolean ;
   begin
   const_func:=l ;
   end;

  function test(i:integer):boolean ;
  begin
  test:=((i=0)or(i=1)) ;
  end;


var l:boolean ;
begin
l:=test(i) ;
while l do {if l=0 or l=1}
begin
fac:=1 ;
l:=false ;
end;

l:=not (test(i)) ;
{while l do begin}
while (const_func(l)) do begin
fac:=fac(i-1)*i ;
l:=false;
end;

end;

var a,b:integer ;
begin


b:=write(Factorial calculation. Enter number:) ;

a:=readln() ;

a:=fac(a) ;


b:=write(Factorial from this number:) ;
b:=writeln(a) ;

end.