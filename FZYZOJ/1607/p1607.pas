program p1607;
const
  MaxN=500+1;
  MaxK=100+1;
  Jiao=0;
  Zhu=1;

var
  n,k:longint;
  f:array[0..MaxN,0..MaxK,0..MaxK]of longint;
  Q:array[0..MaxN]of shortint;

  function max(const a:array of longint):longint;
  var
    i:longint;
    mm:longint;
  begin
    mm:=a[0];
    for i:=0 to length(a)-1 do
      if a[i]>mm then
        mm:=a[i];
    exit(mm);
  end;

  function dp(const i,a,b:longint):longint;
  begin
    if f[i,a,b]>=0 then
      exit(f[i,a,b]);
    if (i<=1)or(a<0)or(b<0) then
      exit(-maxlongint);
    f[i,a,b]:=0;//max([dp(i,a-1,b-1)]);
    if Q[i]=Jiao then
    begin
      if Q[i-1]=Jiao then
        f[i,a,b]:=max([dp(i-1,a,b),dp(i-2,a-1,b)+1]);
      if Q[i-1]=Zhu then
        f[i,a,b]:=max([dp(i-1,a,b),dp(i-2,a-1,b-1)+1]);
    end;
    if Q[i]=Zhu then
    begin
      if Q[i-1]=Jiao then
        f[i,a,b]:=max([dp(i-1,a,b),dp(i-2,a,b)+1]);
      if Q[i-1]=Zhu then
        f[i,a,b]:=max([dp(i-1,a,b),dp(i-2,a,b-1)+1]);
    end;
    exit(f[i,a,b]);
  end;

  procedure Main;
  var
    i:longint;
    aa,bb,cc:longint;
    ch:char;
    ans:longint;
  begin
    readln(n,k);
    fillchar(f,sizeof(f),-1);
    Q[0]:=-1;
    for i:=1 to n do
    begin
      read(ch);
      Q[i]:=ord(ch='z'); //j:0;z:1;
    end;
    ans:=-maxlongint;
    for i:=0 to k do
    begin
      ans:=max([ans,dp(n,i,i)]);
    end;
    writeln(ans);
  end;

begin
  {assign(input,'p1607.in');
  reset(input);
  assign(output,'p1607.out');
  rewrite(output);
  }
  Main;
  {close(output);
  close(input);
  }
end.