program project1;

var
  num:   array[0..1000] of longint;
  Count: longint;
  n:     longint;

  procedure swap(var a, b: longint);
  var
    x: longint;

  begin

    x := a;
    a := b;
    b := x;
  end;

  function check(): boolean;
  var
    i: longint;
  begin
    for i := 1 to n do
      if num[i] > i then
        exit(False);
    exit(True);
  end;

  procedure Once;
  var
    i, j, k: longint;

    rd: ansistring;
  begin
    readln(n);
    fillchar(num, sizeof(num), 0);
    for i := 1 to n do
    begin
      readln(Rd);
      for j := n downto 1 do
        if rd[j] = '1' then
        begin
          num[i] := j;
          break;
        end;
    end;

    Count := 0;
    for i := 1 to n do
      if num[i] > i then
        for j := i + 1 to n do
          if num[j] <= i then
          begin
            Inc(Count, j - i);
            for k := j downto i + 1 do
            begin
              num[k] := num[k - 1];
            end;
            break;
          end;
  end;

var
  T, i: longint;
begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'OJ1133.in');
  reset(input);
  Assign(output, 'OJ1133.out');
  rewrite(output);
  {$ENDIF}
  Readln(T);
  for i := 1 to T do
  begin
    ONCE();
    writeln('Case #', i, ': ', Count);
  end;
  readln;
end.

