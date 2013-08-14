program p1391;

const
  MaxN = 100000 + 1;
type
  TEg = record
    a, b, w, Next: longint;
  end;
var
  start:  array[0..MaxN] of longint;
  poi:    array[0..MaxN * 2] of TEg;
  dm:     array[0..MaxN] of longint;
  ECC:    array[0..MaxN] of int64;
  q:      array[0..MaxN * 2] of longint;
  QTail, QHead: longint;
  dcount: longint;
  ecount: longint;
  N, S:   longint;
  {SECTION SEARCH}
var
  vst: array[0..MaxN] of boolean;
  dst: array[0..MaxN, 0..1] of int64;
  maxlen, maxid: longint;

  function max(const a, b: int64): int64;
  begin
    if a > b then
      exit(a)
    else
      exit(b);
  end;

  function max(const a, b: longint): longint;
  begin
    if a > b then
      exit(a)
    else
      exit(b);
  end;

  function min(const a, b: int64): int64;
  begin
    if a < b then
      exit(a)
    else
      exit(b);
  end;

  procedure DFS(const now: longint);
  var
    p: longint;
  begin
    vst[now] := True;
    p := start[now];
    while p <> 0 do
    begin
      if not vst[poi[p].b] then
      begin
        DFS(poi[p].b);
        if dst[poi[p].b, 0] + poi[p].w > dst[now, 0] then
        begin
          ECC[now]    := dst[now, 0];
          dst[now, 0] := dst[poi[p].b, 0] + poi[p].w;
          dst[now, 1] := poi[p].b;
        end
        else
          ECC[now] := max(ECC[now], dst[poi[p].b, 0] + poi[p].w);
      end;
      p := poi[p].Next;
    end;
    vst[now] := False;
  end;

  procedure FindFarest(const now, len: longint);
  var
    p: longint;
  begin
    vst[now] := True;
    if len > maxlen then
    begin
      maxlen := len;
      maxid  := now;
    end;
    p := start[now];
    while p <> 0 do
    begin
      if not vst[poi[p].b] then
        FindFarest(poi[p].b, len + poi[p].w);
      p := poi[p].Next;
    end;
    vst[now] := False;
  end;

  {SECTION MAIN}
  procedure AddEdge(const u, v, w: longint);
  begin
    Inc(ecount);
    poi[ecount].a := u;
    poi[ecount].b := v;
    poi[ecount].w := w;
    poi[ecount].Next := start[u];
    start[u] := ecount;
  end;

  procedure ReadData;
  var
    t1, t2, t3: longint;
    i: longint;
  begin
    ecount := 0;
    readln(N, S);
    for i := 1 to n do
    begin
      readln(t1, t2, t3);
      AddEdge(t1, t2, t3);
      AddEdge(t2, t1, t3);
    end;
  end;

  procedure Main;
  var
    da, db, i, j: longint;
    ans: int64;
  begin
    //Finding Diameter
    maxlen := -1;
    fillchar(vst, sizeof(vst), False);
    FindFarest(1, 0);
    da := maxid;
    fillchar(vst, sizeof(vst), False);
    fillchar(dst, sizeof(dst), 0);
    DFS(da);
    i      := da;
    dcount := 0;
    while i <> 0 do
    begin
      Inc(dcount);
      dm[dcount] := i;
      i := dst[i, 1];
    end;
    //Get Answer
    ans   := 9000000000000000000;
    i     := 1;
    QTail := 0;
    QHead := 0;
    for j := 1 to dcount do
    begin
      while (dst[dm[i], 0] - dst[dm[j], 0] > S) do
        Inc(i);

      while (QHead < QTail) and (ECC[dm[Q[QTail]]] < ECC[dm[j]]) do
        Dec(QTail);
      Inc(QTail);
      Q[QTail] := j;
      while (QHead < QTail) and (Q[QHead+1] < i) do
        Inc(QHead);
      ans := min(ans, max(ECC[dm[Q[QHead+1]]],
        max(dst[dm[j], 0], dst[dm[1], 0] - dst[dm[i], 0])));

    end;
    writeln(ans);
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'OJ1391.in');
  Assign(output, 'OJ1391.out');
  reset(input);
  rewrite(output);
  {$ENDIF}
  ReadData;
  Main;

end.

