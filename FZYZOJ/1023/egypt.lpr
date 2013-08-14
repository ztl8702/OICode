program egypt;
var
  limit:longint;

  function gcd(m,n:longint):longint;
  var
   r:longint;
  begin
    repeat
      r:=m mod n;
      m:=n; n:=r;
    until r=0;
    gcd:=m;
  end;

  procedure dfs(const upper,lower,d:longint);
  var
    lUp,lDown:longint;
    i:longint;
  begin
    lUp:=trunc(lower/upper)+1;
    lDown:=lUp*(limit-d+1);
    for i:=lUp to lDown do
      dfs(upper);
  end;

begin
end.

