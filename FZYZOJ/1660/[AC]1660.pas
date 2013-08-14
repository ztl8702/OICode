program p1660;
var
  F:array[-20000..20050]of longint;
  P,Q,R:array[0..305]of longint;
  N,T:longint;

  function max(const a,b:longint):longint;
  begin
    if a>b then
      exit(a)
    else
      exit(b);
  end;

  procedure sort(const l,rr:longint);
  var i,j,x,m:longint;
  begin
    i:=l;
    j:=rr;
    m:=Q[(l+rr) shr 1];
    repeat
      while (Q[i]>m) do inc(i);
      while (Q[j]<m) do dec(j);
      if i<=j then
      begin
        x:=Q[i]; Q[i]:=Q[j]; Q[j]:=x;
        x:=P[i]; P[i]:=P[j]; P[j]:=x;
        x:=R[i]; R[i]:=R[j]; R[j]:=x;
        inc(i); dec(j);
      end;
    until i>j;
    if l<j then sort(l,j);
    if i<rr then sort(i,rr);
  end;

  procedure work;
  var
    i,j,ans:longint;
  begin
    fillchar(f,sizeof(f),-1);
    f[0]:=0;
    for i:=1 to n do
      for j:=T downto p[i] do
        if j+Q[i]<=T then
          if f[j-p[i]]>=0 then
            f[j]:=max(f[j],f[j-P[i]]+R[i]);
    ans:=-maxlongint;
    for i:=0 to T do
      ans:=max(ans,f[i]);
    writeln(ans);
  end;

  procedure readdata;
  var
    i:longint;
  begin
    readln(N,T);
    for i:=1 to n do
      readln(P[i],Q[i],R[i]);
    sort(1,N);
  end;

begin
  readdata;
  work;
end.


