program p1395;

const
  MaxN = 100000 + 1;
  MaxM = 100000 + 1;
type
  TEg = record
    a, b, c: longint;
    one:     boolean;
  end;

var
  eg:     array[0..MaxM * 2] of TEg;
  Father: array[0..MaxN] of longint;
  vst:    array[0..MaxN * 2] of boolean;
  ecount: longint;
  N, M, L, ans: longint;

  procedure SortEdge(const l, r: longint);
  var
    i, j, mid: longint;
    x: TEg;
  begin
    i   := l;
    j   := r;
    mid := eg[(l + r) shr 1].c;
    repeat
      while (eg[i].c < mid) do
        Inc(i);
      while (eg[j].c > mid) do
        Dec(j);
      if i <= j then
      begin
        x     := eg[i];
        eg[i] := eg[j];
        eg[j] := x;
        Inc(i);
        Dec(j);
      end;
    until i > j;
    if l < j then
      SortEdge(l, j);
    if i < r then
      SortEdge(i, r);
  end;

  function GetFather(const a: longint): longint;
  begin
    if Father[a] <> a then
      Father[a] := GetFather(Father[a]);
    GetFather   := Father[a];
  end;

  procedure Union(const a, b: longint);
  var
    fa, fb: longint;
  begin
    fa := GetFather(a);
    fb := GetFather(b);
    Father[fa] := Father[fb];
  end;

  function isSame(const a, b: longint): boolean;
  begin
    exit(GetFather(a) = GetFather(b));
  end;

  function getmax(const a, b: longint): longint;
  begin
    if a > b then
      exit(a)
    else
      exit(b);
  end;


  procedure BuildTree();
  var
    i, j, RESt: longint;
  begin
    j := 1;
    for i := 1 to L do
    begin
      while (j < ecount) and ((vst[j]) or (not eg[j].one) or
          (isSame(eg[j].a, eg[j].b))) do
        Inc(j);
      Union(eg[j].a, eg[j].b);
      ans    := getmax(ans, eg[j].c);
      vst[j] := True;
    end;
    j    := 1;
    rest := N - 1 - L;
    for i := 1 to rest do
    begin
      while (j < ecount) and ((vst[j]) or (isSame(eg[j].a, eg[j].b))) do
        Inc(j);
      Union(eg[j].a, eg[j].b);
      ans    := getmax(ans, eg[j].c);
      vst[j] := True;
    end;
  end;

  procedure ReadData;
  var
    i: longint;
    r1, r2, r3, r4: longint;
  begin
    Read(N, L, M);
    for i := 1 to m do
    begin
      Read(r1, r2, r3, r4);
      Inc(ecount);
      with eg[ecount] do
      begin
        a   := r1;
        b   := r2;
        c   := r3;
        one := True;
      end;
      Inc(ecount);
      with eg[ecount] do
      begin
        a   := r1;
        b   := r2;
        c   := r4;
        one := False;
      end;
    end;
    for i := 1 to n do
      Father[i] := i;
  end;

  procedure Main;
  begin
    ReadData;
    SortEdge(1, ecount);
    fillchar(vst, sizeof(vst), False);
    ans := -maxlongint;
    BuildTree;
    Write(ans);
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'OJ1395.in');
  Reset(input);
  Assign(output, 'OJ1395.out');
  Rewrite(output);
  {$ENDIF}
  Main;
  {$IFNDEF ONLINE_JUDGE}
  Close(input);
  Close(output);
  {$ENDIF}
end.

