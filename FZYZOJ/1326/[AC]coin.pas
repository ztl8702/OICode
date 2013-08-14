program coin;  //OJ_1326
{$DEFINE ONLINE_JUDGE}
const
  {$IFNDEF ONLINE_JUDGE}
  inputFile  = 'OJ1326.in';
  outputFile = 'OJ1326.out';
  {$ELSE}
  inputFile  = nil;
  outputFile = nil;
  {$ENDIF}//  L,0,1,2,3,4
  ERRMSG     = 'Impossible';
  drt: array[1..16, 0..4] of word =
    ((2, 2, 5, 0, 0),       //1
    (3, 1, 3, 6, 0),        //2
    (3, 2, 7, 4, 0),        //3
    (2, 3, 8, 0, 0),        //4
    (3, 1, 6, 9, 0),        //5
    (4, 2, 5, 7, 10),       //6
    (4, 3, 6, 8, 11),       //7
    (3, 4, 7, 12, 0),       //8
    (3, 5, 10, 13, 0),      //9
    (4, 6, 9, 11, 14),      //10
    (4, 7, 10, 12, 15),     //11
    (3, 8, 11, 16, 0),      //12
    (2, 9, 14, 0, 0),       //13
    (3, 10, 13, 15, 0),     //14
    (3, 11, 14, 16, 0),     //15
    (2, 12, 15, 0, 0));     //16

var
  Open:  array[0..700000] of longword;
  time:  array[0..70000] of longint;
  vst:   array[0..70000] of boolean;
  start: longword;

 { function hash(const st:TBlock): longint;
  begin
    hash:=st[1,1]*1+st[1,2]*2+st[1,3]*4+st[1,5

  end;   }
  {xor}



  function change(const st: longword; po: word): longword;
  var
    i:   longword;
    nst: longword;
  begin
    nst := st;
    nst := nst xor (1 shl (po - 1));
    for i := 1 to drt[po, 0] do
    begin
      nst := nst xor (1 shl (drt[po, i] - 1));
    end;
    change := nst;
  end;

  procedure print(const a: longword);
  var
    i: longint;
  begin
    for i := 1 to 16 do
    begin
      Write((a and (1 shl (i - 1))) shr (i - 1));
      if (i mod 4 = 0) then
        writeln;
    end;
  end;

  procedure bfs();
  var
    h, t: longint;
    i:    longint;
    tmp:  longword;
  begin
    fillchar(vst, sizeof(vst), False);
    h := 0;
    t := 1;
    Open[1] := start; //?
    time[1] := 0;
    vst[start] := True;
    repeat
      Inc(h);
      for i := 1 to 16 do
      begin
        tmp := change(Open[h], i);
        if not vst[tmp] then
        begin
          Inc(t);
          Open[t]  := tmp;
          vst[tmp] := True;
          time[t]  := time[h] + 1;
          if (tmp = 65535) or (tmp = 0) then
          begin
            writeln(time[t]);
            exit;
          end;
        end;
      end;
    until h >= t;
    writeln(ERRMSG);
  end;



  procedure ReadData();
  var
    rd:   string;
    tt:   longword;
    move: word;
    i, j: longint;
  begin
    move := 0;
    tt   := 0;
    for i := 1 to 4 do
    begin
      readln(rd);
      for j := 1 to 4 do
      begin
        tt   := tt or (Ord(rd[j] = 'b') shl move);
        move := move + 1;
      end;
    end;
    start := tt;
  end;

begin
  Assign(input, inputFile);
  Assign(output, outputFile);
  Reset(input);
  Rewrite(output);
  ReadData;
  bfs;
  readln;
  Close(input);
  Close(output);
end.

