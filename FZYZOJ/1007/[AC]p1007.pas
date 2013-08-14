program p1007;
const
  MaxN=2000+1;
  MaxLL:int64=int64(1000000000000000000);
type
  TInt=array[0..1]of int64;
var
  isp:array[0..MaxN]of boolean;
  plist:array[0..MaxN]of longint;
  pcount,n:longint;
  f:array[0..MaxN]of TInt;
  one:TInt;
  {Int}

  function plus(const a,b:TInt):TInt;
  var
    c:TInt;
  begin
    fillchar(c,sizeof(c),0);
    c[0]:=a[0]+b[0];
    if c[0]>=MaxLL then
    begin
      dec(c[0],MaxLL);
      inc(c[1]);
    end;
    c[1]:=a[1]+b[1]+c[1];
    exit(c);
  end;

  procedure PrintInt(const a:TInt);
  var
    i:longint;
    s:string;
  begin
    if a[1]>0 then
    begin
      write(a[1]);
      str(a[0],s);
      for i:=1 to 18-length(s) do
        write('0');
    end;
    writeln(a[0]);
  end;

  {PRIME}
  procedure getPrime(const limit:longint);
  var
    i,j,k:longint;
  begin
    fillchar(isp,sizeof(isp),true);
    pcount:=0;
    for i:=2 to Limit do
    begin
      if isp[i] then
      begin
        inc(pcount);
        plist[pcount]:=i;
      end;
      for k:=1 to pcount do
      begin
        j:=i*plist[k];
        if (j>limit) then
          break;
        isp[j]:=false;
        if  (i mod plist[k])=0 then
          break;
      end;
    end;
  end;

var
  i,j:longint;
begin {
  assign(input,'p1007.in');
  reset(input);
  assign(output,'p1007.out');
  rewrite(output);       }
  readln(n);
  GetPrime(n);
  one[0]:=1;
  f[0]:=one;
  for j:=1 to pcount do
    for i:=plist[j] to N do
        f[i]:=plus(f[i],f[i-plist[j]]);
  printint(f[n]);
                          {
  close(input);
  close(output);           }
end.
