program p1051;

const
  inputFile  = 'OJ1051.in';
  outputFile = 'OJ1051.out';
var
  t: longint;

  procedure ProcessOnce;
  var
    n, i:    longint;
    tmp, rd1,rd2: longint;
  begin
    readln(n);
    tmp := 89;
    for i := 1 to n do
    begin
      read(rd1,rd2);
      tmp := tmp xor rd1;
      tmp := tmp xor rd2;
    end;
    if tmp = 89 then
      writeln('Yes')
    else
      writeln('No');

  end;

var
  i: longint;
begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, inputFile);
  Assign(output, outputFile);
  Reset(input);
  Rewrite(output);
  {$ENDIF}
  Readln(t);
  for i := 1 to t do
    ProcessOnce;
  {$IFNDEF ONLINE_JUDGE}
  Close(output);
  Close(input);
  {$ENDIF}
end.

