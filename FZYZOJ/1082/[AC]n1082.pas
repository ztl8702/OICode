program p1082;
var
  n,i:longint;
  countx,county:array[0..100000]of longint;
  p:array[1..100000,0..1]of longint;
  ans:qword;
begin
  readln(n);
  for i:=1 to n do
  begin
    readln(p[i,0],p[i,1]);
    inc(countx[p[i,0]]);
    inc(county[p[i,1]]);

  end;
  ans:=0;
  for i:=1 to n do
    ans:=ans+qword((countx[p[i,0]]-1)*(county[p[i,1]]-1));
  writeln(ans);
end.