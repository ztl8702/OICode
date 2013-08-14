program thunder;

var
  v, p:  array[0..6] of longint;
  h:     array[0..105, 0..6] of longint;
  money: array[0..105] of longint;
  f:     array[0..1000000] of int64;
  n, m:  longint;

  function max(const a, b: int64): int64; begin if a > b then  exit(a) else exit(b);  end;

  procedure main;
  var
    k, i0, i1, i2, i3, i4: longint;
    hash1, hash2: longint;
  begin
    for k := 1 to n do
    begin
      hash1 := 0;
      hash2 := 0;
      for i0 := v[0] downto h[k, 0] do
      begin
        Inc(hash1, i0);
        Inc(hash2, i0 - h[k, 0]);

        for i1 := v[1] downto h[k, 1] do
        begin
          Inc(hash1, i1 * p[1]);
          Inc(hash2, (i1 - h[k, 1]) * p[1]);
          for i2 := v[2] downto h[k, 2] do
          begin
            Inc(hash1, i2 * p[2]);
            Inc(hash2, (i2 - h[k, 2]) * p[2]);
            for i3 := v[3] downto h[k, 3] do
            begin
              Inc(hash1, i3 * p[3]);
              Inc(hash2, (i3 - h[k, 3]) * p[3]);
              for i4 := v[4] downto h[k, 4] do
              begin
                Inc(hash1, i4 * p[4]);
                Inc(hash2, (i4 - h[k, 4]) * p[4]);

                if hash2 >= 0 then
                  f[hash1]:=max(f[hash1],f[hash2] + money[k]);

                Dec(hash1, i4 * p[4]);
                Dec(hash2, (i4 - h[k, 4]) * p[4]);
              end;
              Dec(hash1, i3 * p[3]);
              Dec(hash2, (i3 - h[k, 3]) * p[3]);
            end;
            Dec(hash1, i2 * p[2]);
            Dec(hash2, (i2 - h[k, 2]) * p[2]);
          end;
          Dec(hash1, i1 * p[1]);
          Dec(hash2, (i1 - h[k, 1]) * p[1]);
        end;
        Dec(hash1, i0);
        Dec(hash2, i0 - h[k, 0]);
      end;
    end;
  end;

  procedure readdata;
  var
    i, j: longint;
  begin
    readln(n, m);
    fillchar(v, sizeof(v), 0);
    p[0] := 1;
    read(v[0]);
    for i := 1 to m - 1 do
    begin
      Read(v[i]);
      p[i] := p[i - 1] *( v[i-1]+1);
    end;
    readln;
    for i := 1 to n do
    begin
      Read(money[i]);
      for j:= 0 to m - 1 do
        Read(h[i, j]);
      readln;
    end;

  end;

begin
{  Assign(input, 'thunder.in');
  Assign(output, 'thunder.out');
  reset(input);
  rewrite(output);     }
  ReadData;
  main;
  writeln(f[v[0] * p[0] + v[1] * p[1] + v[2] * p[2] + v[3] * p[3] + v[4] * p[4]]);
{  Close(output);
  Close(input);      }
end.



