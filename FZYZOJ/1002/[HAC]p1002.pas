program p1002;

const
  delta = 1e-9;
var
  N, M, X, Y: longint;
  res:     double;
  v, left: array[0..70] of double;
  Count:   longint;
  ims:     set of 0..70;

  procedure dfs(const now, last: longint; sum: double);
  var
    i: longint;
  begin
    if now > N then
    begin
      if abs(sum - res) < delta then
        Inc(Count);
      exit;
    end;
    for i := last + 1 to M - (N - now - 1) do
      if (not (i in ims)) then
        if (not (v[i] + sum + left[m - (n - now) + 1] > res + delta)) then
        begin
          if not (left[i] - left[i + n - now + 1] + sum < res - delta) then
            dfs(now + 1, i, sum + v[i])
          else
            break;
        end;
  end;

  procedure Init;
  var
    i: longint;
  begin
    left[m + 1] := 0;
    for i := m downto 1 do
    begin
      v[i]    := 1 / double(i);
      left[i] := left[i + 1] + v[i];
    end;
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'p1002.in');
  reset(input);
  Assign(output, 'p1002.out');
  rewrite(output);
  {$ENDIF}
  readln(N, M, X, Y);
  res := double(X) / Y;
  init;
  ims := [29, 31, 37, 41, 43, 47, 58, 59];
  dfs(1, 0, 0.0);
  writeln(Count);
  READLN;
end.

