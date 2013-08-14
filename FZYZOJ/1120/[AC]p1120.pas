program p1120;
type
  ansistring=string;
const
  NUMSET = ['0'..'9'];
  BIGSET = ['A'..'Z'];
  SMLSET = ['a'..'z'];
  BLKSET = ['(', ')'];
  LETSET = BIGSET + SMLSET;
var
  left, right: ansistring;
  n:     longint;
  gd:    longint;
  names: array[0..1, 0..700] of longint;

  procedure PQuene(const a: ansistring; const time: longint); forward;

  procedure AddIn(const a: string; const sum: longint);
  var
    k: longint;
  begin
    if length(a) > 1 then
      k := (Ord(a[2]) - Ord('a')) * 26 + Ord(a[1]) - Ord('A')
    else
      k := Ord(a[1]) - Ord('A');
    Inc(names[gd, k], sum);
  end;

  procedure PLine(const a: ansistring; const time: longint);
  var
    alen: longint;
  begin
    alen := length(a);
    if (alen <= 2)and (a[1] in BIGSET)and((alen=1)or((alen>1)and(a[2] in SMLSET))) then
      AddIn(a, time)
    else
      PQuene(a, time);
  end;

  procedure PQuene(const a: ansistring; const time: longint);
  var
    tmp, num: ansistring;
    i:    longint;
    tt, code, high: longint;
    alen: longint;

    procedure QPOnce;
    begin
      num := '';
      while (i <= alen) and (a[i] in NUMSET) do
      begin
        num := num + a[i];
        Inc(i);
      end;
      tt := 1;
      if num <> '' then
        val(num, tt, code);
      PLine(tmp, tt * time);
    end;

  begin
    alen := length(a);
    tmp  := '';
    i    := 0;
    high := 0;
    repeat
      Inc(i);
      if (high = 0) and (length(tmp) > 0) and ((length(tmp) >= 2) or
        (a[i] in BIGSET) or (a[i] in NUMSET)) then
      begin
        QPOnce;
        tmp := '';
      end;
      if i <= alen then
        if not (((a[i] = '(') and (high = 0)) or ((a[i] = ')') and (high = 1))) then
          tmp := tmp + a[i];

      if a[i] = '(' then
        Inc(high)
      else
      if a[i] = ')' then
        Dec(high);

    until i >= alen;
    if tmp <> '' then
    begin
      QPOnce;
      tmp := '';
    end;
  end;


  procedure PMain(const a: ansistring);
  var
    i: longint;
    tmp, num: ansistring;
    tt, code: longint;

    procedure ProcessOnce;
    begin
      num := '';
      while (tmp[1] in NUMSET) do
      begin
        num := num + tmp[1];
        Delete(tmp, 1, 1);
      end;
      tt := 1;
      if num <> '' then
        val(num, tt, code);
      PQuene(tmp, tt);
    end;

  begin
    tmp := '';
    for i := 1 to length(a) do
      if a[i] = '+' then
      begin
        ProcessOnce;
        tmp := '';
      end
      else
      begin
        tmp := tmp + a[i];
      end;
    if tmp <> '' then
      ProcessOnce;
  end;

  function cmp(): boolean;
  var
    i: longint;
  begin
    for i := 0 to 700 do
      if names[0, i] <> names[1, i] then
        exit(False);
    exit(True);
  end;

  procedure ReadData;
  var
    i, j: longint;
  begin
    readln(left);
    gd := 0;
    PMain(left);
    gd := 1;
    readln(n);
    for i := 1 to n do
    begin
      for j := 0 to 700 do
        names[1, j] := 0;
      readln(right);
      PMain(right);
      if cmp then
        writeln(left, '==', right)
      else
        writeln(left, '!=', right);
    end;
  end;

begin
  {$IFnDEF ONLINE_JUDGE}
  Assign(input, 'p1120.in');
  reset(input);
  Assign(output, 'p1120.out');
  rewrite(output);
  {$ENDIF}
  ReadData;
end.

