program p1078;

var
  map:  array[0..600, 0..1500] of char;
  f, g: array[0..600, 0..1500] of longint;
  Next: array[0..600, 0..1500] of longint;
  n:    longint;
  ans, ans2: longint;

  function GetMax(const a, b: longint): longint;
  begin
    if a > b then
      exit(a)
    else
      exit(b);
  end;

  function GetMin(const a, b: longint): longint;
  begin
    if a < b then
      exit(a)
    else
      exit(b);
  end;

  procedure Process;
  var
    i, j, k: longint;
    tmp:     longint;
  begin
    ans := 0;

    if map[1, 1] = '#' then
      f[1, 1] := 0
    else
      f[1, 1] := 1;

    for i := 2 to n do
    begin
      tmp := 2 * i;
      for j := 2 * i - 1 downto 1 do
        if map[i, j] = '#' then
        begin
          Next[i, j] := tmp;
          tmp := j;
        end
        else
          Next[i, j] := tmp;
      for j := 1 to 2 * i - 1 do
      begin
        if (map[i, j] = '#') or (not odd(j)) then
          f[i, j] := 0
        else
        begin
          f[i,j]:= (Next[i, j] - j + 1) shr 1;
          if Next[i, j] > j + f[i - 1, j] * 2 then
            f[i, j] := GetMin(f[i,j],f[i - 1, j] + 1 );
          if f[i, j] > ans then
          begin
            ans := f[i, j];
          end;
        end;
      end;
    end;

    ans2 := 0;
    for i := 1 to 2 * n - 1 do
      if (map[n, i] = '#') or (odd(i)) then
        g[n, i] := 0
      else
        g[n, i] := 1;

    for i := n - 1 downto 1 do
    begin
      tmp := 0;
      for j := 1 to 2 * i - 1 do
        if (map[i, j] = '#') then
        begin
          Next[i, j] := tmp;
          tmp := j;
        end
        else
          Next[i, j] := tmp;

      for j := 1 to 2 * i - 1 do
      begin
        if (map[i, j] = '#') or (odd(j)) then
          g[i, j] := 0
        else
        begin
          g[i, j] := (j - Next[i, j] + 1) shr 1;
          if (Next[i, j] < j - g[i + 1, j] * 2) then
            g[i, j] := GetMin(g[i, j],g[i + 1, j] + 1);
          if g[i, j] > ans2 then
          begin
            ans2 := g[i, j];
          end;
        end;
      end;
    end;
    if ans2 > ans then
      ans := ans2;
  end;

  procedure ReadDataOnce;
  var
    i, j: longint;
    st:   ansistring;
  begin
    for i := n downto 1 do
    begin
      readln(st);
      for j := 1 to 2 * i - 1 do
      begin
        map[i, j] := st[j + n - i];
      end;
    end;

  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'OJ1078.in');
  Assign(output, 'OJ1078.out');
  reset(input);
  Rewrite(output);
  {$ENDIF}
  readln(n);
  ReadDataOnce;
  Process;
  writeln(ans * ans);
  repeat
    readln(n);
    if n = 0 then
      halt;
    ReadDataOnce;
    Process;
    writeln(ans * ans);
  until False;
end.

