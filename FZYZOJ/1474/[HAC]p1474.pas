program p1474;

const
  MaxN = 26 + 1;
  MaxM = 20 + 1;
var
  n, m: longint;
  frd, rev: ansistring;
  f: array[0..MaxN, 0..MaxN, 0..MaxN] of int64;

  function dp(const rc, l, l2, len: longint): int64;
  var
    tmp:    array['a'..'z'] of boolean;
    one, i: longint;
  begin
    if f[rc, l, len] >= 0 then
      exit(f[rc, l, len]);
    writeln(l:5,len:5,l2:5);
    f[rc, l, len] := 0;
    if rc > 1 then
    begin
      fillchar(tmp, sizeof(tmp), False);
      one := 0;
      for i := 0 to len - 1 do
      begin
        tmp[frd[l + i]] := not tmp[frd[l + i]];
        Inc(one, Ord(tmp[frd[l + i]]) - Ord(not (tmp[frd[l + i]])));
        tmp[rev[l2 + i]] := not tmp[rev[l2 + i]];
        Inc(one, Ord(tmp[rev[l2 + i]]) - Ord(not (tmp[rev[l2 + i]])));
        if one = 0 then
          Inc(f[rc, l, len], dp(1, l, l2, i + 1) * dp(rc - 1, l + i + 1, l2 + i + 1, len - i - 1));
      end;
      Inc(f[rc, l, len], dp(rc - 1, l, l2, len));
    end
    else
    if (frd[l] <> rev[l2 + len - 1]) then
      f[rc, l, len] := 0
    else
    if len = 1 then
      f[rc, l, len] := 1
    else
      f[rc, l, len] := dp(m, l + 1, l2, len - 1);
    exit(f[rc, l, len]);
  end;

  procedure ReadAndProcess;
  var
    i, j, code: longint;
    rd:  ansistring;
    num: ansistring;
  begin
    readln(rd);
    while rd <> '0' do
    begin
      num := copy(rd, 1, pos(' ', rd) - 1);
      val(num, m, code);
      Delete(rd, 1, pos(' ', rd));
      frd := copy(rd, 1, pos(' ', rd) - 1);
      Delete(rd, 1, pos(' ', rd));
      rev := rd;
      n   := length(frd);
      fillchar(f, sizeof(f), -1);
      for i := 1 to n do
        for j := i to n do
          f[0, i, j - i + 1] := 0;
      for i := 1 to n + 1 do
        for j := 1 to m do
          f[j, i, 0] := 1;
      writeln(dp(1, 1, 1, n));
      readln(rd);
    end;
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'p1474.in');
  reset(input);
  Assign(output, 'p1474.out');
  rewrite(output);
  {$ENDIF}
  ReadAndProcess;
  {$IFNDEF ONLINE_JUDGE}
  Close(output);
  Close(input);
  {$ENDIF}
end.

