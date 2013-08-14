program task;   //RQ651
var
  v:array[0..100005]of longint;
  n,m,tot,mm:longint;

  function max(const a,b:longint):longint;
  begin
    if a>b then
      exit(a)
    else
      exit(b);
  end;

  function min(const a,b:longint):longint;
  begin
    if a<b then
      exit(a)
    else
      exit(b);
  end;

  function check(const limit:longint):boolean;
  var
    i:longint;
    count,sum:longint;
  begin
    count:=1;
    sum:=0;
    for i:=1 to n do
    begin
      inc(sum,v[i]);
      if sum>limit then
      begin
        sum:=v[i];
        inc(count);
      end;
      if count>m then
        exit(false);
    end;
    if sum>limit then
      inc(count);
    if count<=m then
      exit(true)
    else
      exit(false);
  end;

  procedure search;
  var
    l,r,mid:longint;
    temp:boolean;
  begin
    l:=mm;
    r:=tot;
    repeat
      mid:=(l+r)shr 1;
      temp:=check(mid);
      if temp then
        r:=mid
      else
        l:=mid+1;
    until r=l;
    writeln(r);
  end;
var
  ii:longint;
begin
  readln(n,m);
  tot:=0;
  mm:=-maxlongint;
  for ii:=1 to n do
  begin
    read(v[ii]);
    inc(tot,v[ii]);
    mm:=max(mm,v[ii]);
  end;
  search;
end.