program p1042;
const
  dx:array[1..4]of shortint=(0,0,-1,+1);
  dy:array[1..4]of shortint=(-1,+1,0,0);
type
  TMap=array[0..6,0..6]of boolean;
  PMap=^TMap;
var
  map:longint;
  Q:array[0..1000000]of longint;
  dep:array[0..1000000]of longint;
  vv:array[0..70000000]of boolean;
  tot:longint;
  vst:TMap;
  fx,fy,black:longint;


  procedure dfs(const ma:longint;const x,y:longint);
  var
    i,nx,ny:longint;
  begin
   // writeln(x,',',y);
    if vst[x,y] then
      exit
    else
    begin
      inc(tot);
      vst[x,y]:=true;
    end;
    for i:=1 to 4 do
    begin
      nx:=x+dx[i];
      ny:=y+dy[i];
      if (nx>0)and(ny>0)and(nx<=5)and(ny<=5) then
        if (ma and (1 shl (nx*5-5+ny)))=(1 shl (nx*5-5+ny)) then
          dfs(ma,nx,ny);
    end;
  end;

  function check(const m:longint;const sum:longint):boolean;
  begin
    tot:=0;
    fillchar(vst,sizeof(vst),false);
    dfs(m,fx,fy);
    if tot=sum then
      exit(True)
    else
      exit(false);
  end;

  procedure readdata;
  var
    i,j:longint;
    rd:string;
  begin
    map:=0;
    for i:=1 to 5 do
    begin
      readln(rd);
      for j:=1 to 5 do
      begin
        map:=map or (longint(rd[j]='1') shl (i*5-5+j));
        if (map and (1 shl (i*5-5+j)))=(1 shl (i*5-5+j)) then
        begin
          if (fx=0) then
          begin
            fx:=i;
            fy:=j;
          end;
          inc(black);
        end;
      end;
    end;
  end;

  procedure search;
  var
    i,j:longint;
    h,t:longint;
    now:longint;
    new:longint;
  begin
    h:=0;
    t:=1;
    Q[t]:=map;
    vv[Q[t]]:=true;
    dep[t]:=0;
    if check(map,black) then
    begin
      writeln(0);
      exit;
    end;
    repeat
      inc(h);
      now:=Q[h];
      //move(now^,new,sizeof(new));
      for i:=1 to 5 do
        for j:=1 to 5 do
          if (now and (1 shl (i*5-5+j)))=0 then
          begin
            new:=now or (1 shl (i*5-5+j));
            if not vv[new] then
            begin
              inc(t);
              Q[t]:=new;
              dep[t]:=dep[h]+1;
              vv[Q[t]]:=true;
              if check(new,black+dep[t]) then
              begin
                writeln(dep[t]);
                exit;
              end;
            end;
          end;
    until h>=t;
    writeln('ooops');
  end;

  procedure main;
  begin
    search;
  end;

begin
  readdata;
  main;

end.