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
  vst:   array[0..MaxN] of boolean;
  eg:    array[0..MaxM] of TEg;
  Start: array[0..MaxN] of longint;
  N, M:  longint;

  function dspfa(const now: longint): boolean;
  var
    i, tar: longint;
  begin
    i := sTart[now];
    while (i <> 0) do
    begin
      tar := eg[i].v;
      if dis[now] + eg[i].w < dis[tar] then
      begin
        if vst[tar] then
        begin
          exit(True);
        end
        else
        begin
          dis[tar] := dis[now] + eg[i].w;
          if dis[tar] < MinV then
            exit(True);
          vst[tar] := True;
          if dspfa(tar) then
            exit(True);
          vst[tar] := False;
        end;

      end;
      i := eg[i].Next;
    end;
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
  for i := 1 to N do
  begin
    vst[i] := True;
    if dspfa(i) then
    begin
      ans := True;
      break;
    end;
    vst[i] := False;
  end;
  if ans then
    writeln('Y')
  else
    writeln('N');
  {$IFNDEF ONLINE_JUDGE}
  Close(input);
  Close(output);
  {$ENDIF}
end.

