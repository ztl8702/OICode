program food;  //OJ_1330
const
  inputFile = 'OJ1330.in';
  outputFile = 'OJ1330.out';
  maxN = 100000 + 1;
var
  q: array[0..MaxN] of longint;
  sum: array[0..MaxN] of int64;
  ans: int64;
  n, min, max: longint;

  procedure Process;
  var
    h, t, i: longint;
  begin
    ans := -maxlongint;
    h := 1;
    t := 1;
    q[1] := 0;
    for i := 1 to n - min + 1 do
    begin
      Inc(t);
      q[t] := i;
      while (h < t) and (sum[q[t]] < sum[q[t - 1]]) do
      begin
        Dec(t);
        q[t] := q[t + 1];
      end;
      if i + min - q[h] - 1 > max then
        Inc(h);
      if (i+min-q[h]-1>=min)and(sum[i + min-1] - sum[q[h]] > ans) then
      begin

        ans := sum[i + min-1] - sum[q[h]];
       // writeln('Ans Update:',q[h]+1,'->',i+min-1,'=',ans);
      end;
    end;
  end;

  procedure ReadData;
  var
    i: longint;
    tmp: longint;
  begin
    readln(n, min, max);
    sum[0] := 0;
    for i := 1 to n do
    begin
      readln(tmp);
      sum[i] := sum[i - 1] + tmp;
    end;
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(Input, inputFile);
  Assign(Output, outputFile);
  Reset(input);
  Rewrite(Output);
  {$ENDIF}
  ReadData;
  Process;
  writeln(ans);
  {$IFNDEF ONLINE_JUDGE}
  Close(input);
  Close(Output);
  {$ENDIF}
end.

