program path;   //OJ_P1094
const
  MinV = int64(-19910917917);
  MaxM = 10000;
  MaxN = 10000;
type
  TEg = record
    u, v, Next: longint;
    w: int64;
  end;
var
  dis:   array[0..MaxN] of int64;
  eg:    array[0..MaxM] of TEg;
  Start: array[0..MaxN] of longint;
  q:     array[0..20000] of longint;
  v:     array[0..MaxN] of boolean;
  N, M:  longint;

  {function bf(const Source: longint): boolean;
  var
    i, j: longint;
  begin
    for i := 1 to N do
      dis[i]    := maxlongint;
    dis[Source] := 0;
    for i := 1 to N - 1 do
      for j := 1 to M do
        if dis[eg[j, 0]] + eg[j, 2] < dis[eg[j, 1]] then
        begin
          dis[eg[j, 1]] := dis[eg[j, 0]] + eg[j, 2];

        end;
    for i := 1 to M do
      if (dis[eg[i, 0]] + eg[i, 2] < dis[eg[i, 1]]) then
        exit(True);
    for i := 1 to N do
      if dis[i] < MinV then
        exit(True);
    exit(False);
  end;  }

  function spfa: boolean;
  var
    h, t, i, now: longint;
  begin
    h := 0;
    t := 0;
    //fillchar(dis, sizeof(dis), $7f);
    fillchar(v, sizeof(v), 0);
    for i := 1 to n do
    begin
      Inc(t);
      v[i] := True;
      q[t mod 20000] := i;
    end;

    repeat
      h      := (h + 1);
      now    := q[h mod 20000];
      v[now] := False;
      i      := sTart[now];
      while (i <> 0) do
      begin
        if dis[now] + eg[i].w < dis[eg[i].v] then
        begin
          dis[eg[i].v] := dis[now] + eg[i].w;
          if not v[eg[i].v] then
          begin
            v[eg[i].v] := True;
            t := (t + 1);
            q[t mod 20000] := eg[i].v;
          end;

        end;
        if (dis[eg[i].v] < MinV) or (h > 6 * m) then
          exit(True);
        i := eg[i].Next;
      end;
    until h >= t;
    exit(False);
  end;

  procedure ReadData;

  begin
    readln(N, M);
    M := 0;  //PREVENT ILLEGAL INPUT
    while not EOF do
    begin
      Inc(M);
      Readln(eg[m].u, eg[m].v, eg[m].w);
      eg[m].Next     := Start[eg[m].u];
      start[eg[m].u] := m;

    end;
  end;

var
  i:   longint;
  ans: boolean;
begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'OJ1094.in');
  reset(input);
  Assign(output, 'OJ1094.out');
  rewrite(output);
  {$ENDIF}
  ReadData;
  ans := spfa;

  if ans then
    writeln('Y')
  else
    writeln('N');
  {$IFNDEF ONLINE_JUDGE}
  Close(input);
  Close(output);
  {$ENDIF}
end.
