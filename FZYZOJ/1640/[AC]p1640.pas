program p1640;

var
  n:    longint;
  map:  array[0..60, 0..60] of integer;
  v, right: array[0..60] of longint;
  f, g: array[0..60, 0..60] of longint;
  nn:   array[0..60, 0..600] of longint;
  vst:  array[0..60, 0..600] of boolean;

  function nextn(const s, ss: longint): longint;
  var
    tmp, i: longint;
  begin
    if vst[s, ss] then
      exit(nn[s, ss]);
    tmp := s;
    for i := 1 to ss do
      tmp      := right[tmp];
    nn[s, ss]  := tmp;
    vst[s, ss] := True;
    exit(tmp);
  end;

  function max(const a, b: longint): longint;
  begin
    if a > b then
      exit(a)
    else
      exit(b);
  end;

  function min(const a, b: longint): longint;
  begin
    if a < b then
      exit(a)
    else
      exit(b);
  end;

  procedure ndp;
  var
    i, l, len: longint;
  begin
    for i := 1 to n do
    begin
      g[i, 1] := v[i];
      f[i, 1] := v[i];
    end;
    for len := 2 to n do
      for l := 1 to n do
      begin
        f[l, len] := -maxlongint;
        g[l, len] := maxlongint;
        for i := 1 to len - 1 do
        begin
          if map[nextn(l, i - 1), nextn(l, i)] = 1 then
          begin
            f[l, len] := max(f[l, len], f[l, i] + f[nextn(l, i), len - i]);
            g[l, len] := min(g[l, len], g[l, i] + f[nextn(l, i), len - i]);
          end
          else
          begin
            f[l, len] := max(f[l, len], f[l, i] * f[nextn(l, i), len - i]);
            f[l, len] := max(f[l, len], g[l, i] * g[nextn(l, i), len - i]);
            g[l, len] := min(g[l, len], g[l, i] * f[nextn(l, i), len - i]);
            g[l, len] := min(g[l, len], f[l, i] * g[nextn(l, i), len - i]);
            g[l, len] := min(g[l, len], g[l, i] * g[nextn(l, i), len - i]);
            g[l, len] := min(g[l, len], f[l, i] * f[nextn(l, i), len - i]);
          end;
        end;
      end;

  end;

  procedure ReadData;
  var
    i, j: longint;
    cr: char;
  begin
    readln(n);
    for i := 1 to n do
    begin
      Read(cr);
      Read(v[i]);
      j := i - 1;
      if j <= 0 then
        j      := j + n;
      right[i] := (i mod n) + 1;
      if cr = 't' then
        map[i, j] := 1
      else
        map[i, j] := 2;
      map[j, i] := map[i, j];
      Read(cr);
    end;
  end;

  procedure Main;
  var
    i:   longint;
    ans: longint;
  begin
    ndp;
    ans := -maxlongint;
    for i := 1 to n do
      ans := max(ans, f[i, n]);
    writeln(ans);
  end;

begin
  ReadData;
  Main;

end.

