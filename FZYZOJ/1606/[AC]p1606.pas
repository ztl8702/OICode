program p1606;

const
  pre: array[1..6, 0..2] of shortint = ((2, 4, 6),
    (0, 0, 0),
    (1, 6, 0),
    (1, 1, 0),
    (0, 0, 0),
    (2, 1, 3));
  //1,2,3,4,5,6

  map: array[1..6, 1..6] of 0..1 = ((0, 0, 0, 1, 0, 1),
    (0, 0, 0, 0, 0, 0),
    (0, 0, 0, 0, 0, 1),
    (1, 0, 0, 0, 0, 0),
    (0, 0, 0, 0, 0, 0),
    (1, 0, 1, 0, 0, 0));
var
  n: longint;

  f:   array[0..100005, 0..6] of longint;
 //1:one low;2: NULL; 3:two low; 4:two high; 5:NULL; 6:three high;
  v:   array[0..100005, 1..3] of longint;

  function max(const arr: array of longint): longint;
  var
    i, tmp: longint;
  begin
    tmp := -maxlongint;
    for i := 0 to length(arr) - 1 do
      if arr[i] > tmp then
        tmp := arr[i];
    exit(tmp);
  end;

  procedure dp;
  var
    i, j, k, st, ans, tmp: longint;
  begin
    ans := -maxlongint;
    for st := 1 to 6 do
      if (st <> 2) and (st <> 5) then
      begin
        for i := 1 to 6 do
          if st = i then
            f[1, i] := v[1, (st + 1) shr 1]
          else
            f[1, i] := 0;
        for i := 2 to n - 1 do
          for j := 1 to 6 do
          begin
            tmp := -maxlongint;
            for k := 1 to pre[j, 0] do
              if f[i - 1, pre[j, k]] + v[i, (j + 1) shr 1] > tmp then
                tmp := f[i - 1, pre[j, k]] + v[i, (j + 1) shr 1];
            f[i, j] := tmp;
          end;

        for j := 1 to 6 do
        begin
          tmp := -maxlongint;
          for k := 1 to pre[j, 0] do
            if map[j, st] = 1 then
              if f[n - 1, pre[j, k]] + v[n, (j + 1) shr 1] > tmp then
                tmp := f[n - 1, pre[j, k]] + v[n, (j + 1) shr 1];
          f[n, j]   := tmp;
        end;
        ans := max([ans, f[n, 1], f[n, 3], f[n, 4], f[n, 6]]);
      end;
      writeln(ans);
  end;

  procedure readdata;
  var
    i: longint;
  begin
    readln(n);
    for i := 1 to n do
      readln(v[i, 1], v[i, 2], v[i, 3]);
  end;

begin
  readdata;
  dp;

end.

