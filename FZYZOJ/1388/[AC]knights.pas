program knights;  //OJ_1388;

const
  MaxN      = 100000 + 1;
  MaxM      = 100000 + 1;
  {$IFNDEF ONLINE_JUDGE}
  inputFile = 'OJ1388.in';
  outputFile = 'OJ1388.out';
  {$ELSE}
  inputFile = nil;
  outputFile = nil;
  {$ENDIF}

var
  father: array[0..MaxN] of longint;
  N, M:   longint;
  ed:     array[0..MaxM, 1..3] of longint; //1 startnode; 2 endnode; 3 value
  selected: array[0..MaxM] of boolean;
  c:      array[0..MaxN] of longint;
  minp:    longint;
  {P1}

  function getFather(const ANode: longint): longint;
  begin
    if Father[Anode] <> Anode then
      Father[Anode] := GetFather(Father[ANode]);
    GetFather := Father[ANode];
  end;

  function Same(const ANode, BNode: longint): boolean;
  begin
    Same := (GetFather(Anode) = GetFather(BNode));
  end;

  procedure Union(const ANode, BNode: longint);
  var
    fa, fb: longint;
  begin
    fa := GetFather(ANode);
    fb := GetFather(BNode);
    father[fa] := fb;
  end;

  {P2}
  procedure sortEdge(const l, r: longint);
 var
    i, j, x, t: longint;
  begin
    i := l;
    j := r;
    x := ed[(l + r) shr 1, 3];
    repeat
      while ed[i, 3] < x do
        Inc(i);
      while ed[j, 3] > x do
        Dec(j);
      if i <= j then
      begin
        t := ed[i, 1];
        ed[i, 1] := ed[j, 1];
        ed[j, 1] := t;

        t := ed[i, 2];
        ed[i, 2] := ed[j, 2];
        ed[j, 2] := t;

        t := ed[i, 3];
        ed[i, 3] := ed[j, 3];
        ed[j, 3] := t;

        Inc(i);
        Dec(j);
      end;
    until i > j;
    if l < j then
      sortEdge(l, j);
    if i < r then
      sortEdge(i, r);
  end;

  {P3}
  procedure MST;
  var
    Count, j: longint;
    sum:      longint;
  begin
    sum := 0;
    fillchar(selected, sizeof(selected), False);
    j     := 1;
    Count := 0;
    repeat
      while (Same(ed[j, 1], ed[j, 2])) and (j < m) do
        Inc(j);
      if j <= m then
      begin
        Selected[j] := True;

        Union(ed[j, 1], ed[j, 2]);
        sum := sum + ed[j, 3];
        Inc(j);
        inc(Count);
      end;
    until (Count >= N - 1) or (j > m);

    writeln(Sum+minp);
  end;


  {P0}
  procedure ReadData;
  var
    i:  longint;

  begin
    readln(N, M);   minp := maxlongint;
    for i := 1 to N do  begin
      readln(C[i]);          if c[i]<minp then minp:=c[i]; end;

    for i := 1 to M do
    begin
      readln(ed[i, 1], ed[i, 2], ed[i, 3]);

    end;

    for i := 1 to M do
    begin
     father[i] := i;
     ed[i,3]:=ed[i,3]*2+c[ed[i,1]]+c[ed[i,2]];
    end;

  end;

begin
  Assign(input, inputFile);
  Assign(output, outputFile);
  Reset(input);
  Rewrite(output);
  ReadData;
  SortEdge(1,M);
  MST;
  Close(input);
  Close(output);
end.

