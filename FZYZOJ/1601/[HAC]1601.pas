program p1601;
const
  MaxN=200000+5;
var
  n:longint;
  v:array[0..MaxN,0..2]of longint;
  f:array[0..MaxN,0..2]of longint;

  function min(const arr:array of longint):longint;
  var
    i,tmp:longint;
  begin
    tmp:=maxlongint;
    for i:=0 to length(arr)-1 do
      if arr[i]<tmp then
        tmp:=arr[i];
    exit(tmp);
  end;

  procedure dp;
  var
    i,j:longint;
  begin
    f[1,0]:=v[1,0];
    f[1,1]:=v[1,1];
    f[1,2]:=v[1,2];
    for i:=2 to n do
      for j:=0 to 2 do
        case j of
          0:f[i,j]:=min([f[i-1,1] , f[i-1,2]]) + v[i,0];
          1:f[i,j]:=min([f[i-1,0] , f[i-1,2]]) + v[i,1];
          2:f[i,j]:=min([f[i-1,0] , f[i-1,1]]) + v[i,2];
        end;
  end;

  procedure init;
  var
    i,j:longint;
  begin
    readln(n);
    for i:=1 to n do
    begin
      for j:=0 to 2 do
        read(v[i,j]);
    end;
  end;

begin
  {$IFDEF LOCAL_JUDGE}
  assign(input,'p1601.in');
  assign(output,'p1601.out');
  reset(input);
  rewrite(output);
  {$ENDIF}
  init;
  dp;
  writeln(min([f[n,0],f[n,1],f[n,2]]));

  close(output);
  close(input);
end.