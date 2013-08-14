program p1637;

const
  MaxN = 50000 + 1;
type
  TEg = record
    a, b, Next: longint;
  end;
  TPoiData = array[0..MaxN * 2] of TEg;
  TETable  = array[0..MaxN] of longint;

var
  start, et: TETable;
  tmp, poi: TPoiData;
  f:      array[0..MaxN] of longint;
  Q:      array[0..MaxN] of longint;
  Vst:    array[0..MaxN] of boolean;
  tcount: longint;
  ecount: longint;
  n:      longint;

  {GRAPH SECTION}
  procedure AddEdge(var counter: longint; var Tar: TPoiData; var eta: TETable;
  const a, b: longint);
  begin
    Inc(counter);
    Tar[counter].a := a;
    Tar[counter].b := b;
    Tar[counter].Next := eta[a];
    eta[a] := counter;
  end;

  procedure Convert;
  var
    h, t, i, now: longint;
  begin
    h    := 0;
    t    := 1;
    Q[t] := 1;
    Vst[Q[t]] := True;
    repeat
      Inc(h);
      now := Q[h];
      i   := et[now];
      while i <> 0 do
      begin
        if not Vst[tmp[i].b] then
        begin
          Inc(t);
          Q[t]      := tmp[i].b;
          Vst[Q[t]] := True;
          AddEdge(ecount, poi, start, now, Q[t]);
        end;
        i := tmp[i].Next;
      end;
    until h >= t;
  end;

  {DP SECTION}

var
  swaparr: array[0..MaxN] of longint;

  function max(const a, b: longint): longint;
  begin
    if a > b then
      exit(a)
    else
      exit(b);
  end;

  procedure dp;
  var
    i, j, k, now, x, tot: longint;

  begin
    for k := n downto 1 do
    begin
      now := Q[k];
      tot := 0;
      i   := start[now];
      while i <> 0 do
      begin
        Inc(tot);
        swaparr[tot] := f[poi[i].b];
        i := poi[i].Next;
      end;
      for i := 2 to tot do
        for j := tot downto i do
          if swaparr[j] > swaparr[j - 1] then
          begin
            x := swaparr[j];
            swaparr[j] := swaparr[j - 1];
            swaparr[j - 1] := x;
          end;
      for i := 1 to tot do
        f[now] := max(f[now], swaparr[i] + i);
    end;
  end;

  {MAIN SECTION}
  procedure ReadData;
  var
    i, aa, bb: longint;
  begin
    readln(n);
    for i := 1 to n - 1 do
    begin
      readln(aa, bb);
      AddEdge(tcount, tmp, et, aa + 1, bb + 1);
      AddEdge(tcount, tmp, et, bb + 1, aa + 1);
    end;
  end;

  procedure Main;
  begin
    fillchar(vst, sizeof(vst), False);
    fillchar(f, sizeof(f), 0);
    dp();
    writeln(f[1]);
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'oj1637.in');
  reset(input);
  Assign(output, 'oj1637.out');
  rewrite(output);
  {$ENDIF}
  ReadData;
  Convert;
  Main;
end.

