program p1615;

const
  MaxN = 100000 + 1;
var
  m1, m2, f1, f2: array[0..MaxN] of longint;
  num: array[0..MaxN] of longint;
  n:   longint;

  function getmax(const a, b: longint): longint;
  begin
    if a > b then
      exit(a)
    else
      exit(b);
  end;

  procedure process;
  var
    i:   longint;
    ans: int64;
  begin

    f1[1] := num[1];
    m1[1] := f1[1];
    for i := 2 to N do
    begin
      if f1[i - 1] > 0 then
        f1[i] := f1[i - 1] + num[i]
      else
        f1[i] := num[i];
      m1[i] := getmax(m1[i - 1], f1[i]);

    end;

    f2[n] := num[n];
    m2[n] := f2[n];
    for i := n - 1 downto 1 do
    begin
      if f2[i + 1] > 0 then
        f2[i] := f2[i + 1] + num[i]
      else
        f2[i] := num[i];
      m2[i] := getMax(m2[i + 1], f2[i]);
    end;
    ans := -maxlongint;
    for  i := 1 to n - 1 do
      ans := getmax(ans, m1[i] + m2[i + 1]);
    writeln(ans);
  end;

  procedure ReadData;
  var
    i: longint;
  begin
    readln(n);
    for i := 1 to n do
      Read(num[i]);
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'OJ1615.in');
  reset(input);
  Assign(output, 'OJ1615.out');
  rewrite(output);
  {$ENDIF}
  ReadData;
  process;
  {$IFNDEF ONLINE_JUDGE}
  Close(output);
  Close(input);
  {$ENDIF}
end.

