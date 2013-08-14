program p1214;
const
  dx:array[1..8]of shortint=(-1,-1,-1,0,0,+1,+1,+1);
  dy:array[1..8]of shortint=(-1,0,+1,-1,+1,-1,0,+1);
var
  n:longint;
  map,cc:array[-5..1005,-5..1005]of longint;
  Q:array[0..1000005,0..1]of longint;
  c1,c2:longint;
  count:longint;

  function legal(const xx,yy:longint):boolean;
  begin
    if (xx>0)and(yy>0)and(xx<=n)and(yy<=n) then
      exit(true)
    else
      exit(false);
  end;

  procedure fill(const color,sx,sy:longint);
  var
    low,high:boolean;
    h,t,i,nowx,nowy,nx,ny:longint;
  begin
    low:=true;
    high:=true;
    h:=0;
    t:=1;
    Q[t,0]:=sx;
    Q[t,1]:=sy;
    cc[sx,sy]:=color;
    repeat
      inc(h);
      nowx:=Q[h,0];
      nowy:=Q[h,1];
      for i:=1 to 8 do
      begin
        nx:=nowx+dx[i];
        ny:=nowy+dy[i];
        if legal(nx,ny) then
        begin
          if (map[nx,ny]=map[nowx,nowy])and(cc[nx,ny]=0) then
          begin
            inc(t);
            cc[nx,ny]:=color;
            Q[t,0]:=nx;
            Q[t,1]:=ny;
          end
          else
          begin
            if map[nx,ny]<map[nowx,nowy] then
              low:=false;
            if map[nx,ny]>map[nowx,nowy] then
              high:=false;
          end;
        end;
      end;
    until h>=t;
    if low then
      inc(c2);
    if high then
      inc(c1);
  end;

  procedure readdata;
  var
    i,j:longint;
  begin
    readln(n);
    for i:=1 to n do
      for j:=1 to n do
        read(map[i,j]);
  end;

  procedure main;
  var
    i,j:longint;
  begin
    for i:=1 to n do
      for j:=1 to n do
        if cc[i,j]=0 then
        begin
          inc(count);
          fill(count,i,j);
        end;
    writeln(c1,' ',c2);
  end;


begin
  readdata;
  main;
end.