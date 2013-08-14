program p1498;
const
  DOWN=1;
  FRONT=2;
  LEFT=3;
  UP=-1;
  BACK=-2;
  RIGHT=-3;

var
  ff:array[0..10,0..10,-5..5,-5..5,-5..5]of longint;
  v:array[-5..5]of longint;

  x1,x2,y1,y2,ans:longint;

  function min(const a,b:longint):longint;
  begin
    if a<b then
      exit(a)
    else
      exit(b);
  end;

  procedure dfs(const x,y,d,f,l,sum:longint);
  begin
    if ff[x,y,d,f,l]<=sum then
      exit
    else
      ff[x,y,d,f,l]:=sum;
   // writeln(x,',',y);
    if sum>=ans then
      exit;
    if (x=x2)and(y=y2) then
    begin
      ans:=min(ans,sum);
      exit;
    end;
    //To Front;
    if y>1 then
      dfs(x,y-1,f,-d,l,sum+v[f]);
    //To Back;
    if y<8 then
      dfs(x,y+1,-f,d,l,sum+v[-f]);
    //To Left;
    if x>1 then
      dfs(x-1,y,l,f,-d,sum+v[l]);
    //To Right;
    if x<8 then
      dfs(x+1,y,-l,f,d,sum+v[-l]);
  end;

  const
   sord:array[1..6]of longint=(FRONT,BACK,UP,RIGHT,DOWN,LEFT);

  procedure readdata;
  var
    rd:string;
    tmp:string;
    code,I:longint;
  begin
    readln(rd);
    if rd[length(rd)]<>' ' then
      rd:=rd+' ';
    tmp:=copy(rd,1,pos(' ',rd)-1);
    delete(rd,1,pos(' ',rd));
    x1:=ord(tmp[1])-ord('a')+1;
    y1:=ord(tmp[2])-ord('0');
    tmp:=copy(rd,1,pos(' ',rd)-1);
    delete(rd,1,pos(' ',rd));
    x2:=ord(tmp[1])-ord('a')+1;
    y2:=ord(tmp[2])-ord('0');
    for i:=1 to 6 do
    begin
      tmp:=copy(rd,1,pos(' ',rd)-1);
      delete(rd,1,pos(' ',rd));
      val(tmp,v[sord[i]],code);
    end;

  end;

  procedure main;
  begin
    fillchar(ff,sizeof(ff),63);
    ans:=maxlongint;
    dfs(x1,y1,DOWN,FRONT,LEFT,v[DOWN]);
    writeln(ans);
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  assign(input,'p1498.in');
  reset(input);
  assign(output,'p1498.out');
  rewrite(output);
  {$ENDIF}
  readdata;
  main;

  close(output);
  close(input);
end.
