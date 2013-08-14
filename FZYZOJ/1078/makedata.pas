program makedata;
var
  i,j,n:longint;
begin
  Assign(output,'OJ1078.in');
  rewrite(output);
  readln(n);
  writeln(n);
  for i:=n downto 1  do
  begin
    for j:=1 to n-i do write(' ');
    for j:=1 to 2*i-1 do write('-');
    writeln;
  end;
  writeln(0);
  close(output);

  end.