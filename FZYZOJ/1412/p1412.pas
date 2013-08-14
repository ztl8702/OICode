program p1412;
var
  L1,L2,L3,D:longint;
  f:array[0..50,0..2]of longint;   //( 0 [ 1 { 2
  vst:array[0..50,0..2]of longint;

  function dp(const x,t:longint):longint;
  var
    i,j:longint;
  begin
    if vst[x,t] then
      exit(f[x,t]);
    case t of
      0:
      begin

      end;
      1:
      begin

      end;
      2:
      begin

      end;
    end;
  end;

  procedure Main;
  var

  begin

  end;

begin
  Readln(L1,L2,L3,D);

end.