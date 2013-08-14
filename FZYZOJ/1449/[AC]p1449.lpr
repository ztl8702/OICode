program p1449;

const
  MaxN = 100;
type
  TStatusArr = array[0..MaxN] of boolean;
var
  list, ans: array[0..20] of TStatusArr;
  key:   array[0..20] of longint;
  check: array[0..20] of boolean;
  tmp:   array[0..4] of boolean;
  pon, poff: array[0..MaxN] of boolean;
  pcount, AnsCount: longint;
  N, C:  longint;
  bool:  boolean;

  {G}
  procedure Genarate;
  var
    i: longint;
  begin
    check[pcount] := True;
    for i := 1 to n do
    begin
      if tmp[1] then
        list[pcount, i] := not list[pcount, i];
      if (tmp[2]) and (odd(i)) then
        list[pcount, i] := not list[pcount, i];
      if (tmp[3]) and (not odd(i)) then
        list[pcount, i] := not list[pcount, i];
      if (tmp[4]) and (((i - 1) mod 3) = 0) then
        list[pcount, i] := not list[pcount, i];
      if pon[i] and (not list[pcount, i]) then
        check[pcount] := False;
      if poff[i] and list[pcount, i] then
        check[pcount] := False;
    end;
  end;

  procedure search(const now, press: longint);
  begin
    if now > 4 then
    begin
      Inc(pcount);
      key[pcount] := press;
      Genarate;
      exit;
    end;
    tmp[now] := True;
    Search(now + 1, press + 1);
    tmp[now] := False;
    Search(now + 1, press);

  end;

  {M}
  function Big(ai, bi: TStatusArr): boolean;
  var
    i: longint;
  begin
    for i := 1 to n do
      if Ord(ai[i]) > Ord(bi[i]) then
        exit(True)
      else if Ord(ai[i]) < Ord(bi[i]) then
        exit(False);
    exit(False);

  end;

var
  tmparr: array[0..MaxN] of boolean;

  procedure SwapAns(const ai, bi: longint);

  begin
    fillchar(tmparr, sizeof(tmparr), False);
    move(ans[ai, 0], tmparr[0], (MaxN + 1) * sizeof(bool));
    move(ans[bi, 0], ans[ai, 0], (MaxN + 1) * sizeof(bool));
    move(tmparr[0], ans[bi, 0], (MaxN + 1) * sizeof(bool));
  end;

  procedure SortAns(const l, r: longint);
  var
    i, j: longint;
    mid:  TStatusArr;
  begin
    i := l;
    j := r;
    move(ans[(l + r) shr 1, 0], mid[0], (MaxN + 1) * sizeof(bool));
    repeat
      while Big(mid, ans[i]) do
        Inc(i);
      while Big(ans[j], mid) do
        Dec(j);
      if i <= j then
      begin
        swapAns(i, j);
        Inc(i);
        Dec(j);
      end;
    until i > j;
    if l < j then
      SortAns(l, j);
    if i < r then
      SortAns(i, r);
  end;

  procedure ReadData;
  var
    tmp: longint;
  begin
    readln(N);
    Readln(C);
    Read(tmp);
    while tmp <> -1 do
    begin
      pon[tmp] := True;
      Read(tmp);
    end;
    Read(tmp);
    while tmp <> -1 do
    begin
      poff[tmp] := True;
      Read(tmp);
    end;
  end;

  procedure Print(const x: longint);
  var
    i: longint;
  begin
    for i := 1 to n do
      if Ans[x, i] then
        Write('1')
      else
        Write('0');
    writeln;
  end;

  procedure Process;
  var
    CanPress: array[0..4] of boolean;
    i: longint;
  begin
    if C < 4 then
    begin
      case c of
        0:
        begin
          CanPress[0] := True;
          CanPress[1] := False;
          CanPress[2] := False;
          CanPress[3] := False;
          CanPress[4] := False;
        end;
        1:
        begin
          CanPress[0] := False;
          CanPress[1] := True;
          CanPress[2] := False;
          CanPress[3] := False;
          CanPress[4] := False;
        end;
        2:
        begin
          CanPress[0] := True;
          CanPress[1] := False;
          CanPress[2] := True;
          CanPress[3] := False;
          CanPress[4] := False;
        end;
        3:
        begin
          CanPress[0] := False;
          CanPress[1] := True;
          CanPress[2] := False;
          CanPress[3] := True;
          CanPress[4] := False;
        end;
      end;
    end
    else
    begin
      if odd(C) then
      begin
        CanPress[0] := False;
        CanPress[1] := True;
        CanPress[2] := False;
        CanPress[3] := True;
        CanPress[4] := False;
      end
      else
      begin
        CanPress[0] := True;
        CanPress[1] := False;
        CanPress[2] := True;
        CanPress[3] := False;
        CanPress[4] := True;
      end;
    end;
    AnsCount := 0;
    for i := 1 to pcount do
      if check[i] and CanPress[key[i]] then
      begin
        Inc(AnsCount);
        move(list[i, 0], ans[AnsCount, 0], (MaxN + 1) * sizeof(bool));
      end;
    SortAns(1, AnsCount);
    for i := 1 to AnsCount do
      Print(i);
  end;

begin
 {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'OJ1449.in');
  Reset(input);
  Assign(output, 'OJ1449.out');
  Rewrite(output);
  {$ENDIF}
  fillchar(list, sizeof(list), True);
  ReadData;
  Search(1, 0);
  Process;
end.

