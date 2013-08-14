program sale;

  {DEFINE ONLINE_JUDGE}
const
  inputFile = 'OJ1152.in';
  outputFile = 'OJ1152.out';
  High = 10;   {000}
  MaxL = 1000000 * High;
  MaxN = 100000 + 1;
  MaxM = 100000 + 1;
var
  f:    array[0..MaxL, 0..30] of int64;
  vst:  array[0..MaxL, 0..30] of boolean;
  n, m: longint;
  p, v: array[0..MaxN] of longint;
  psum: array[0..MaxN] of longint;
  powerTwo: array[0..30] of longint;

  {TOOL}
  function GetMax(const a, b: int64): int64;
  begin
    if a > b then
      exit(a)
    else
      exit(b);
  end;

  function FindInV(const w: longint): longint;
  var
    l, r, mid: longint;
  begin
    l := 1;
    r := n;
    repeat
      mid := (l + r) shr 1;
      if v[mid] = w then
        exit(mid);
      if v[mid] > w then
        l := mid + 1;
      if v[mid] < w then
        r := mid - 1;
    until l >= r;
    if v[l] > w then
      exit(l)
    else
      exit(l - 1);
  end;

  {SORT}
  procedure sort(const l, r: longint);
  var
    i, j, x, t: longint;
  begin
    i := l;
    j := r;
    x := v[(l + r) shr 1];
    repeat
      while v[i] > x do
        Inc(i);
      while x > v[j] do
        Dec(j);
      if i <= j then
      begin
        t    := v[i];
        v[i] := v[j];
        v[j] := t;

        t    := p[i];
        p[i] := p[j];
        p[j] := t;

        Inc(i);
        Dec(j);
      end;
    until i > j;
    if l < j then
      sort(l, j);
    if i < r then
      sort(i, r);
  end;

  {DP}
  function dp(const l, r: longint): int64;
  var
    tt: longint;
  begin
    if l > MaxL then
      exit(0);
    if vst[l, r] then
      exit(f[l, r]);
    if r = 0 then
    begin
      tt      := FindInV(l);
      f[l, r] := psum[tt] * l;
      vst[l, r] := True;
      exit(f[l, r]);
    end
    else
    begin
      f[l, r]   := GetMax(dp(l, r - 1), dp(l + PowerTwo[r - 1], r - 1));
      vst[l, r] := True;
      exit(f[l, r]);
    end;
  end;

  {MAIN}
  procedure Init;
  var
    i: longint;
  begin

    PowerTwo[0] := 1;
    for i := 1 to 30 do
      PowerTwo[i] := 2 * PowerTwo[i - 1];
  end;

  procedure ReadData;
  var
    i:  longint;
    rd: double;
  begin
    readln(n, m);
    for i := 1 to n do
    begin
      readln(p[i], rd);
      v[i] := trunc(rd * High);
    end;
  end;

  procedure Answer;
  var
    l, r:   double;
    nl, nr: longint;
    i:      longint;
    k:      longint;
  begin
    for i := 1 to m do
    begin
      readln(l, r);
      nl := trunc(l * High);
      nr := trunc(r * High);
      k  := trunc(ln(nr - nl + 1) / ln(2));
      writeln((GetMax(dp(nl, k), dp(nr - powerTwo[k] + 1, k)) / High): 0: 1);
    end;
  end;

  procedure Main;
  var
    i: longint;
  begin
    ReadData;
    Sort(1, n);
    psum[0] := 0;
    for i := 1 to n do
      psum[i] := psum[i - 1] + p[i];
    Answer;
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, inputFile);
  Reset(input);
  Assign(output, outputFile);
  Rewrite(output);
  {$ENDIF}
  Init;
  Main;
  {$IFNDEF ONLINE_JUDGE}
  Close(input);
  Close(output);
  {$ENDIF}
end.

