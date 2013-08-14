program p1582;
var
  n,m:longint;
  h:array[0..1005,0..1005]of longint;
  ans:longint;

  procedure process;
  var i,j,k:longint;
  begin
    ans:=0;
    for i:=1 to n do
      for j:=1 to m do
        for k:=1 to h[i,j] do
        begin
          inc(ans,ord(k>h[i-1,j])+ord(k>h[i,j-1])+ord(k>h[i+1,j])+ord(k>h[i,j+1])
              +ord(k=h[i,j])+ord(k=1));
        end;
  end;

  procedure ReadData;
  var
    i,j,code:longint;
    rd:string;
  begin
    fillchar(h,sizeof(h),0);
    readln(n,m);
    for i:=1 to n do
    begin
      readln(rd);
      for j:=1 to m do
        val(rd[j],h[i,j],code);
    end;
  end;

begin
  {$IFDEF ONLINE_JUDGE}
  assign(input,'p1582.in');
  reset(input);
  assign(output,'p1582.out');
  rewrite(output);
  {$ENDIF}
  readdata;
  process;
  writeln(ans);

end.