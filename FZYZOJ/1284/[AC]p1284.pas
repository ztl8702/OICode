program p1284;

const
  MAXN = 1005;
type
  {$IFNDEF ONLINE_JUDGE}
  ansistring = string;
  {$ENDIF}
  TSon = record
    son, Next: longint;
  end;

var
  n:   longint;
  poi: array[0..100000] of TSon;
  son, father: array[0..50000] of longint;
  str: array[0..50000] of ansistring;
  tot, scount: longint;

  procedure add(const now: longint; path: ansistring);
  var
    dirname, subdir: ansistring;
    p:     longint;
    found: boolean;
  begin
    dirname := copy(path, 1, pos('/', path) - 1);
    subdir  := copy(path, pos('/', path) + 1, length(path) - length(dirname) - 1);
    if dirname <> '' then
    begin
      p     := son[now];
      found := False;
      while (p <> 0) do
      begin
        if str[poi[p].son] = dirname then
        begin
          found := True;
          break;
        end;
        p := poi[p].Next;
      end;
      if found then
        add(poi[p].son, subdir)
      else
      begin
        Inc(tot);
        str[tot]    := dirname;
        father[tot] := now;
        Inc(scount);
        poi[scount].son := tot;
        poi[scount].Next := son[now];
        son[now] := scount;
        add(poi[scount].son, subdir);
      end;
    end;
  end;

  procedure main;
  var
    tmp, i: longint;
    rd:     ansistring;
  begin
    readln(n);
    str[0] := '/';
    father[0] := 0;
    son[0] := 0;
    tot := 0;
    for i := 1 to n do
    begin
      readln(rd);
      rd := copy(rd, 2, length(rd) - 1) + '/';
      add(0, rd);
      writeln(tot);
    end;
  end;

begin
  main;
end.

