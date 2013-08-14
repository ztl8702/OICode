program p1387;
const
  MaxN=200+1;
type
  TEg=record
    a,b,next:longint;
  end;

var
  f:array[0..MaxN,0..MaxN]of longint;
  vst:array[0..MaxN,0..MaxN]of boolean;
  start:array[0..MaxN]of longint;
  poi:array[0..MaxN*2]of TEg;
  map:array[0..MaxN,0..MaxN]of boolean;
  n,m:longint;
  ecount:longint;
  s1,s2,t1,t2:longint;

  function dp(const x,y:longint):longint;
  var
    i:longint;
  begin
    if vst[x,y] then
      exit(f[x,y]);
    if x<>y then
    begin
      for i:=1 to n do
        if (i<>x) and (i<>y) then
        if not (map[i,x] and map[i,y]) then
        begin
          if map[i,x] then
            inc(f[x,y],dp(i,y));
          if map[i,y] then
            inc(f[x,y],dp(x,i));
        end;
    {    i:=start[x];
      while i<>0 do
      begin
        inc(f[x,y],dp(poi[i].b,y));
        i:=poi[i].next;
      end;
      i:=start[y];
      while i<>0 do
      begin
        inc(f[x,y],dp(x,poi[i].b));
        i:=poi[i].next;
      end;    }
    end;
    vst[x,y]:=true;
    exit(f[x,y]);
  end;

  procedure AddEdge(const u,v:longint);
  begin
    inc(ecount);
    with poi[ecount] do
    begin
      a:=u;
      b:=v;
      next:=start[u];
    end;
    start[u]:=ecount;
  end;

  procedure ReadData;
  var
    i:longint;
    x,y:longint;
  begin
    readln(N,M);
    for i:=1 to M do
    begin
      readln(x,y);
      map[x,y]:=true;
      AddEdge(y,x);
    end;
    readln(s1,t1,s2,t2);
  end;
var aa,bb:longint;
begin
  ReadData;
  vst[s1,s2]:=true;
  f[s1,s2]:=1;
  writeln(dp(t1,t2));
  while true do
  begin
    write('Q: ');
    readln(aa,bb);
    writeln('A: ',dp(aa,bb));
  end;
  readln;
end.
