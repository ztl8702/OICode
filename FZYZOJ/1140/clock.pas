program clock;

const
  {$IFDEF ONLINE_JUDGE}
  inputFile=nil;
  outputFile=nil;
  {$ELSE}
  inputFile = 'OJ1140.in';
  outputFile = 'OJ1140.out';
  {$ENDIF}
  maxN = 500000;
type
  PQuene = ^TQuene;

  TQuene = record
    flow: PQuene;
    h, t, len, limit: longint;
    q: array[0..maxN] of longint;
  end;

var
  one: TQuene;
  five, hour: TQuene;
  bottom: TQuene;
  n: longint;
  change: array[0..MaxN] of longint;
  tmp: array[0..MaxN, 0..1] of longint;
  ans: QWord;

  procedure init;
  var
    i: longint;
  begin
    with bottom do
    begin
      flow := nil;
      limit := n;
      h := 0;
      t := n - 1;
      len := n;
      for i := 1 to n do
        q[i - 1] := i;
    end;
    with one do
    begin
      flow := @five;
      limit := 4;
      len := 0;
      h := 0;
      t := -1;
    end;
    with five do
    begin
      flow := @hour;
      limit := 11;
      len := 0;
      h := 0;
      t := -1;
    end;
    with hour do
    begin
      flow := @bottom;
      limit := 11;
      len := 0;
      h := 0;
      t := -1;
    end;
  end;


  function DeleteItem(var Target: TQuene): longint;
  var
    res: longint;
  begin
    res := Target.q[Target.h];
    Dec(Target.len);
    Target.h := (Target.h + 1) mod MaxN;
    DeleteItem := res;
  end;

  procedure AddItem(var Target: TQuene; const item: longint);
  begin
    Inc(Target.len);
    Target.t := (Target.t + 1) mod MaxN;
    Target.q[Target.t] := item;
  end;

  procedure MoveItem(const Source, Target: PQuene);
  var
    tmp: array[0..20] of longint;
    i, tt: longint;
  begin
    if Source^.len > 0 then
    begin
      AddItem(Target^, DeleteItem(Source^));
      if Target^.len > Target^.limit then
      begin
        tt := Target^.len - 1;
        for i := 1 to tt do
          tmp[i] := DeleteItem(Target^);
        for i := tt downto 1 do
          AddItem(bottom, tmp[i]);
        if Target^.flow <> nil then
          MoveItem(Target, Target^.flow);
      end;
    end;
  end;

  procedure SimulateOnce();
  begin
    repeat
      moveItem(@bottom, @one);
    until bottom.len = n;
  end;

  procedure GetChange();
  var
    i: longint;
  begin
    for i := 1 to n do
      Change[i] := DeleteItem(bottom);
  end;

  function Check(const sw: shortint): boolean;
  var
    i: longint;
  begin
    for i := 1 to n do
      if tmp[i, sw] <> i then
        exit(False);
    exit(True);

  end;

  procedure Simulate;
  var
    i: longint;
    switch: boolean;
  begin
    switch := False;
    for i := 1 to n do
      tmp[i, 0] := i;
    ans := 0;
    repeat
      Inc(ans);
      for i := 1 to n do
        tmp[i, Ord(not switch)] := tmp[change[i], Ord(switch)];
      switch := not switch;
      if Check(Ord(switch)) then
        break;

    until False;
    writeln(ans div 2);
  end;

begin

  Assign(input,inputFile);
  Assign(output,outputFile);
  Reset(input);
  Rewrite(output);
  readln(n);
  init;
  SimulateOnce;
  Writeln('Done');
  GetChange;
  Simulate;
  Close(input);
  Close(output);
end.

