program p1022;
type
  TMap=array[0..105,0..105]of boolean;
const
  dx:array[1..4]of shortint=(+1,0,-1,0);
  dy:array[1..4]of shortint=(0,+1,0,-1);

var
  map:TMap;
  minans:longint;
  m,n,p:longint;
  f:array[0..105,0..105,0..505]of longint;

  procedure dfs(const x,y,l,tot:longint);
  var
    i,nx,ny:longint;
  begin
    if f[x,y,l]<=tot then
      exit
    else
      f[x,y,l]:=tot;
    if tot>=minans then
      exit;
    if (X=m)and(y=n) then
    begin
      if tot<minans then
        minans:=tot;
      exit;
    end;
    for i:=1 to 4 do
    begin
      nx:=x+dx[i];
      ny:=y+dy[i];
      if (nx>0)and(ny>0)and(nx<=M)and(ny<=n) then
      begin
        if map[nx,ny] and (l>0) then
          dfs(nx,ny,l-1,tot+1);
        if not map[nx,ny] then
          dfs(nx,ny,l,tot+1);
      end;
    end;
  end;

  procedure readdata;
  var
    i,j,rd:longint;
  begin
    readln(m,n,p);
    for i:=1 to M do
    begin
      for j:=1 to N do
      begin
        read(rd);
        map[i,j]:=boolean(rd=1);
      end;
      readln;
    end;
  end;

begin
  readdata;
  fillchar(f,sizeof(f),127);
  minans:=maxlongint;
  dfs(1,1,P,0);
  if minans < maxlongint then
    writeln(minans)
  else
    writeln('LouZhu Will Be Dead.');

end.
