program p1238;
const MaxN=100+1;
var
  map:array[0..MaxN,0..MaxN]of longint;
  f:array[0..MaxN*2,0..MaxN,0..MaxN]of int64;
  N:longint;

  function GetMax(const a,b,c,d:int64):int64;
  var
    tmp:int64;
  begin
    tmp:=a;
    if b>tmp then tmp:=b;
    if c>tmp then tmp:=c;
    if d>tmp then tmp:=d;
    exit(tmp);
  end;

  function GetMax(const a,b:longint):longint;
  begin
    if a>b then exit(a) else exit(b);
  end;

  function GetMin(const a,b:longint):longint;
  begin
    if a<b then exit(a) else exit(b);
  end;

  procedure dp;
  var
    i,x1,x2:longint;
  begin
    for i:=1 to 2*N do
    begin
      for x1:=GetMax(1,i-n) to GetMin(n,i-1) do
        for x2:=GetMax(1,i-n) to GetMin(n,i-1)do
        begin
          f[i,x1,x2]:=GetMax(f[i-1,x1,x2],f[i-1,x1-1,x2],
                            f[i-1,x1,x2-1],f[i-1,x1-1,x2-1]);
          if x1<>x2 then
            inc(f[i,x1,x2],map[x1,i-x1]+map[x2,i-x2])
          else
            inc(f[i,x1,x2],map[x1,i-x1]);
        end;
    end;
  end;

  procedure ReadData;
  var
    x,y,v:longint;
  begin
    readln(n);
    readln(x,y,v);
    while (x<>0) do
    begin
      map[x,y]:=v;
      readln(x,y,v);
    end;
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  assign(input,'oj1238.in');
  assign(output,'oj1238.out');
  reset(input);
  rewrite(output);
  {$ENDIF}
  ReadData;
  Dp;
  writeln(f[n*2,n,n]);

end.
