program p1073;
var
  s1,s2:ansistring;
  f:array[0..3050,0..3050]of longint;
  i,j:longint;
  len1,len2:longint;

  function max(const a,b:longint):longint;
  begin
    if a>b then
      exit(a)
    else
      exit(b);
  end;

begin
  readln(s1);
  readln(s2);
  len1:=length(s1);
  len2:=length(s2);
  for i:=1 to len1 do
    for j:=1 to len2 do
    begin
      if s1[i]=s2[j] then
        f[i,j]:=f[i-1,j-1]+1
      else
        f[i,j]:=max(f[i-1,j],f[i,j-1]);
    end;
  writeln(len1+len2-f[len1,len2]);
end.