
program monkeys;

const
  maxN = 200000+1;
  maxM = 400000+1;

var
  father, link_head, link_tail, link_next, left, right, falltime: array[0..maxN] of
  longint;
  TimeLine: array[0..maxM] of longint;
  boolLeft, boolRight: array[0..MaxN] of boolean;
  isRight:  array[0..maxM] of boolean;
  N, M:     longint;

  function GetFather(const a: longint): longint;
  begin
    if Father[a] <> a then
      Father[a] := GetFather(Father[a]);
    GetFather   := Father[a];
  end;

  function isSame(const a, b: longint): boolean;
  begin
    isSame := (GetFather(a) = GetFather(b));
  end;

  procedure Union(fa, fb: longint);
  var
    x: longint;
  begin
    if fa = 1 then
    begin
      x := fa;
      fa := fb;
      fb := x;
    end;
{    fa := GetFather(a);
    fb := GetFather(b);
 }
    father[fa]    := fb;
    link_next[link_tail[fb]] := link_head[fa];
    link_tail[fb] := link_tail[fa];
    link_head[fa]:=0;
    link_tail[fa]:=0;
  end;

  procedure Mark(const anode,now:longint);
  var
    p:longint;
  begin
    p:=anode;
    while p<>-1 do
    begin
      falltime[p]:=now;
      p:=link_next[p];
    end;
  end;

  procedure Process;
  var
    i, p: longint;
    monkeya, monkeyb: longint;
  begin
    for i := 1 to N do
    begin
      if (not boolLeft[i]) and (left[i] <> -1) then
      begin
        monkeya := getFather(i);
        monkeyb := getFather(left[i]);
        if monkeya <> monkeyb then
          union(monkeya, monkeyb);
      end;
      if (not boolRight[i]) and (Right[i] <> -1) then
      begin
        monkeya := getFather(i);
        monkeyb := getFather(right[i]);
        if monkeya <> monkeyb then
          union(monkeya, monkeyb);
      end;
    end;
    for i := M-1 downto 0 do
    begin
      monkeya := TimeLine[i];
      if isRight[i] then
        monkeyb := Right[monkeya]
      else
        monkeyb := Left[monkeya];
      monkeya:=getFather(monkeya);
      monkeyb:=getFather(monkeyb);
      if (monkeyb <> -1) and (monkeya <> monkeyb) then
      begin
        if (monkeya = 1) then
          Mark(monkeyb,i)
        else
        if (monkeyb = 1) then
          Mark(monkeya,i);
        union(monkeya,monkeyb);
      end;
    end;
  end;

  procedure ReadData();
  var
    i:   longint;
    tmp: longint;
  begin
    readln(N, M);
    for i := 1 to N do
      readln(left[i], right[i]);
    for i := 0 to M-1 do
    begin
      readln(timeline[i], tmp);
      isRight[i] := (tmp = 2);
      if not isRight[i] then
        boolLeft[TimeLine[i]]  := True
      else
        boolRight[TimeLine[i]] := True;
    end;
    for i := 1 to N do
    begin
      link_next[i] := -1;
      link_head[i] := i;
      link_tail[i] := i;
      father[i]    := i;
      falltime[i]  := -1;
    end;
  end;

  procedure PrintResult;
  var
    i: longint;
  begin
    for i := 1 to N do
      writeln(falltime[i]);

  end;

begin
  ReadData;
  Process;
  PrintResult;
  Readln;
end.

