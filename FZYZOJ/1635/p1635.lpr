program p1635;
const
  MaxN=250000;
var
  n,L,R:longint;
  Q:array[0..MaxN]of longint;
  QHead,QTail:longint;
  ansp,ansq,maxans:longint;
  c:array[0..MaxN]of longint;
  sum:array[0..MaxN]of longint;
  function gcd(const a,b:longint):longint;
  begin

  end;

  procedure Solve;
  var
    i,j:longint;
    atmp:double;
  begin
    sum[0]:=0;
    readln(n);
    QHead:=0;
    QTail:=0;
    i:=1;
    for j:=1 to n do
    begin
      readln(c[j]);
      sum[j]:=sum[j-1]+c[j];
      while (j-i+1>R) do
        inc(i);
      atmp:=double(sum[j]-sum[i-1])/(j-i+1);
      while (QHead<QTail)and((double(sum[Q[QTail]]-sum[i-1])/(Q[QTail]-i+1))<(atmp)) do
        dec(QTail);
      inc(QTail);
      Q[QTail]:=j;
      while (QHead<QTail)and(Q[QHead+1]<i) do
        inc(QHead);
      if (Q[QTail]-Q[QHead+1]+1)>=L then
      begin
        tmp:=(double(sum[Q[QTail]]-sum[Q[QHead+1]-1])/(Q[QTail]-Q[QHead+1]+1));
        if  tmp>         maxans then
        begin
         maxans:=tmp;
         maxp:=sum[Q[QTail]]-sum[Q[QHead+1]-1];
         maxq:=Q[QTail]-Q[QHead+1]+1;
        end;
    end;
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  assign(input,'oj1635.in');
  reset(input);
  assign(output,'oj1635.out');
  rewrite(output);
  {$ENDIF}

end.

