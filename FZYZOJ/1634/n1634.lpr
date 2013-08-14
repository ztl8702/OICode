program p1634;

const
  oo = 2000000000000000000;
var

  ans:  array[0..40] of boolean;
  f:    array[0..1, 0..40] of int64;
  abool:    boolean;
  n:    longint;
  sizebool: longint;
  function abs(const a: int64): int64;
  begin
    if a > 0 then
      exit(a)
    else
      exit(-a);
  end;

var
  g: array[0..1,0..40] of longint;

  {procedure dfs(const now: longint; L, R: int64);
  begin
    if now > n then
    begin
      if abs(L - R) < min then
      begin
        min := abs(L - R);
        move(group[0], ans[0], sizeof(group));
      end;
      exit;
    end;
    group[now] := False;
    dfs(now + 1, L + f[0, now], R);
    group[now] := True;
    dfs(now + 1, L, R + f[1, now]);
  end;    }

  procedure swap(var a,b:longint);
  var
     c:longint;
  begin
    c:=a;
    a:=b;
    b:=c;
  end;

  procedure swap(var a,b:int64);
  var
    c:int64;
  begin
    c:=a;
    a:=b;
    b:=c;
  end;

  procedure Solve;
  var
    i,j,l,r:longint;
    sum1,sum2:int64;
    min,tmp:int64;
    found:boolean;
  begin
    sum1:=0;
    sum2:=0;
    for i:=1 to n do
    begin
      inc(sum1,f[0,i]);
      inc(sum2,f[1,i+n]);
      ans[i]:=false;
      ans[i+n]:=true;
      g[0,i]:=i;
      g[1,i]:=i+n;
    end;
    while true do
    begin
      min:=abs(sum1-sum2);
      found:=false;
      for i:=1 to n do
        for j:=1 to n do
        begin
          tmp:=abs((sum1-f[0,g[0,i]]+f[1,g[1,j]])-(sum2-f[1,g[1,j]]+f[0,g[0,i]]));
          if (tmp<min) then
          begin
            found:=true;
            min:=tmp;
            l:=i;
            r:=j;
          end;
        end;
      if not found then break;
      sum1:=sum1-f[0,g[0,l]]+f[1,g[1,r]];
      sum2:=sum2-f[1,g[1,r]]+f[0,g[0,l]];
      ans[g[0,l]]:=not ans[g[0,l]];
      ans[g[1,r]]:=not ans[g[1,r]];
      swap(g[1,r],g[0,l]);
    end;
  end;

  procedure Print;
  var
    i: longint;
  begin
    for i := 1 to 2*n do
      Write(chr(Ord('A') + Ord(ans[i]=true)));
    writeln;
  end;

  procedure ReadData;
  var
    i: longint;
  begin
    readln(n);
    for i := 1 to 2*n do
      Read(f[0, i]);
    for i := 1 to 2*n do
      Read(f[1, i]);
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'oj1634.in');
  reset(input);
  Assign(output, 'ojn1634.out');
  rewrite(output);
  {$ENDIF}
  sizebool:=sizeof(abool);
  ReadData;
  Solve;
  Print;

end.

