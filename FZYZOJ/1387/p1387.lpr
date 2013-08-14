program Project1;

const
  MaxN = 200 + 1;
  MaxM = 10000;
type
  TEg = record
    a, b, w, Next: longint;
  end;
  TStatus = array[0..MaxN] of boolean;

var
  start:  array[0..MaxN] of longint;
  eg:     array[0..MaxM] of TEg;
  N, M, a1, a2, b1, b2: longint;
  ecount: longint;
  vst:    TStatus;
  ways:   array[0..10000] of TStatus;
  waycount: longint;
  ans:    int64;

  procedure DfsA(const now: longint);
  var
    x: longint;
  begin
    if now = a2 then
    begin
      Inc(waycount);
      move(vst[0], ways[waycount, 0], sizeof(vst));
      exit;
    end;
    x := start[now];
    while x <> 0 do
    begin
      vst[eg[x].b] := True;
      DfsA(eg[x].b);
      vst[eg[x].b] := False;
      x := eg[x].Next;
    end;
  end;

  procedure checkans;
  var
    i, j: longint;
  begin
    for i := 1 to waycount do
    begin
      Inc(ans);
      for j := 1 to n do
        if vst[j] and ways[i, j] then
        begin
          Dec(ans);
          break;
        end;
    end;

  end;

  procedure DfsB(const now: longint);
  var
    x: longint;
  begin
    if now = b2 then
    begin
      checkans;
      exit;
    end;
    x := start[now];
    while x <> 0 do
    begin
      vst[eg[x].b] := True;
      DfsB(eg[x].b);
      vst[eg[x].b] := False;
      x := eg[x].Next;
    end;

  end;

  procedure AddEdge(const u, v: longint);
  begin
    Inc(ecount);
    eg[ecount].a := u;
    eg[ecount].b := v;
    eg[ecount].w := 1;
    eg[ecount].Next := start[u];
    start[u] := ecount;
  end;

  procedure ReadData;
  var
    i, x, y: longint;
  begin
    readln(N, M);
    for i := 1 to n do
    begin
      readln(x, y);
      AddEdge(x, y);
    end;
    readln(a1, a2, b1, b2);
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'OJ1387.in');
  Assign(output, 'OJ1387.out');
  Reset(input);
  Rewrite(output);
  {$ENDIF}
  ReadData;
  waycount := 0;
  ans      := 0;
  fillchar(vst, sizeof(vst), False);
  DfsA(a1);
  fillchar(vst, sizeof(vst), False);
  DfsB(b1);
  writeln(ans);
end.

