program PRIME1;
const
  MaxS=31630;
var
  isp:array[0..100000]of boolean;
  ps:array[0..100000]of longint;
  n,m:longint;
  pcount:longint;

  procedure getPrimes;
  var
    i,j,k:longint;
  begin
    pcount:=0;
    for i:=2 to MaxS do
    begin
      if not isp[i] then
      begin
        inc(pcount);
        ps[pcount]:=i;
      end;
      j:=1;
      while (j<=pcount)and(i*ps[j]<=MaxS) do
      begin
        isp[i*ps[j]]:=true;
        if (i mod ps[j])=0 then
          break;
        inc(j);
      end;
    end;

  end;

  procedure processonce;
  var
    i,j:longint;
    delta:longint;
  begin
    readln(n,m);
    fillchar(isp,sizeof(isp),false);
    delta:=n-1;
    if 1>=n then
      isp[1-delta]:=true;
    for i:=1 to pcount do
    begin
      j:=ps[i]*(n div ps[i]);
      while j<=m do
      begin
        if (j>=n)and(j>ps[i]) then
          isp[j-delta]:=true;
        inc(j,ps[i]);
      end;
    end;
    for i:=n to m do
      if not isp[i-delta] then
        writeln(i);
  end;
var
  t,ii:longint;
begin
  getPrimes;
  readln(t);
  for ii:=1 to t-1 do
  begin
    processOnce;
    writeln;
  end;
  processonce;
end.