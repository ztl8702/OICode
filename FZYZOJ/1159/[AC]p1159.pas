program p1159;
const
  MaxN=1000+5;
  MaxM=1000+5;
  dx:array[1..4]of shortint=(+1,0,-1,0);
  dy:array[1..4]of shortint=(0,+1,0,-1);

var
  map:array[0..MaxN,0..MaxM]of boolean;
  cc:array[0..MaxN,0..MaxM]of longint;
  count:array[0..100000]of longint;
  ccount:longint;
  Q:array[0..MaxN*MaxM,0..1]of longint;
  n,m,k:longint;

  procedure fill(const sx,sy,color:longint);
  var
    h,t,i:longint;
    nowx,nowy,nx,ny:longint;
  begin
    h:=0;
    t:=1;
    Q[t,0]:=sx;
    Q[t,1]:=sy;
    cc[sx,sy]:=color;
    count[color]:=1;
    repeat
      inc(h);
      nowx:=Q[h,0];
      nowy:=Q[h,1];
      for i:=1 to 4 do
      begin
        nx:=nowx+dx[i];
        ny:=nowy+dy[i];
        if (nx<=n)and(ny<=m)and(nx>0)and(ny>0) then
          if (not map[nx,ny]) and(cc[nx,ny]=0) then
          begin
            cc[nx,ny]:=color;
            inc(count[color]);
            inc(t);
            Q[t,0]:=nx;
            Q[t,1]:=ny;
          end;
      end;
    until h>=t;
  end;

  function check(const lx,ly:longint):longint;
  var
    sum:longint;
    i:longint;
    nx,ny:longint;
    tot:longint;
    arr:array[0..5]of longint;
    function notexist(const cl:longint):boolean;
    var
      j:longint;
    begin
      for j:=1 to tot do
        if arr[j]=cl then
          exit(false);
      exit(true);
    end;

  begin
    sum:=1;
    tot:=0;
    for i:=1 to 4 do
    begin
      nx:=lx+dx[i];
      ny:=ly+dy[i];
      if (nx<=n)and(ny<=m)and(nx>0)and(ny>0) then
        if notexist(cc[nx,ny]) and (cc[nx,ny]<>0) then
        begin
          inc(tot);
          arr[tot]:=cc[nx,ny];
          inc(sum,count[cc[nx,ny]]);
        end;
    end;
    if notexist(1) then
      exit(0)
    else
      exit(sum);
  end;

  procedure readdata;
  var
    i,j:longint;
    rd:ansistring;
  begin
    readln(n,m,k);
    for i:=1 to n do
    begin
      readln(rd);
      for j:=1 to m do
        map[i,j]:=boolean(rd[j]='1');
    end;
  end;

  procedure main;
  var
    i,j:longint;
    ans,tmp:longint;
  begin
    ccount:=1;
    fill(1,1,1);
    if k=0 then
      writeln(count[1])
    else
    begin
      for i:=1 to n do
        for j:=1 to m do
          if (not map[i,j])and(cc[i,j]=0) then
          begin
            inc(ccount);
            fill(i,j,ccount);
          end;
      ans:=0;
      for i:=1 to n do
        for j:=1 to m do
          if map[i,j] then
          begin
            tmp:=check(i,j);
            if tmp>ans then
              ans:=tmp;
          end;
      writeln(ans);
    end;
  end;

begin
  readdata;
  main;

end.

