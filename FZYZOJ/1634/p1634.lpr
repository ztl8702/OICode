program p1634;

const
  oo = 2000000000000000000;
var
  i, j: longint;
  ans:  array[0..40] of boolean;
  f:    array[0..1, 0..40] of int64;
  abool:    boolean;
  n:    longint;
  sizebool: longint;
  min:  int64;

  function abs(const a: int64): int64;
  begin
    if a > 0 then
      exit(a)
    else
      exit(-a);
  end;

var
  group: array[0..40] of boolean;

  procedure dfs(const now: longint; L, R: int64);
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
  end;

  procedure Print;
  var
    i: longint;
  begin
    for i := 1 to n do
      Write(chr(Ord('A') + Ord(ans[i]=true)));
    writeln;
  end;

  procedure ReadData;
  var
    i: longint;
  begin
    readln(n);
    n:=n+n;
    for i := 1 to n do
      Read(f[0, i]);
    for i := 1 to n do
      Read(f[1, i]);

  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'oj1634.in');
  reset(input);
  Assign(output, 'oj1634.out');
  rewrite(output);
  {$ENDIF}
  sizebool:=sizeof(abool);
  ReadData;
  min := oo;
  Dfs(1, 0, 0);
  Print;

end.

