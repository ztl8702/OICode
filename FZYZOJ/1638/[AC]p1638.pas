program p1638;

const
  MaxN = 100 + 1;
  MaxM = 100 + 1;
  MaxConsCount = 500 + 1;
  MaxStarCount = 160 + 1;
  dx: array[0..7] of shortint = (-1, -1, +0, +1, +1, +1, +0, -1);
  dy: array[0..7] of shortint = (+0, +1, +1, +1, +0, -1, -1, -1);
type
  TStar = record
    x, y: longint;
  end;

  TCons = record
    Count: longint;
    order: longint;
    s:     array[0..MaxStarCount] of TStar;
    p:     TStar;
    maxx, maxy, minx, miny: longint;
  end;

var
  n, m: longint;
  map, cmp: array[0..MaxN, 0..MaxM] of boolean;
  Q:    array[0..MaxStarCount] of TStar;
  cs:   array[0..MaxConsCount] of TCons;
  ctot: longint;
  same: array[0..MaxConsCount, 0..MaxConsCount] of boolean;
  o:    array[0..MaxConsCount] of longint;
  ans:  array[0..MaxN, 0..MaxM] of longint;

  {SECTION GP}

  procedure SortCons(const l, r: longint);
  var
    i, j: longint;
    mid:  TStar;
    x:    longint;
  begin
    i   := l;
    j   := r;
    mid := cs[o[(l + r) shr 1]].p;
    repeat
      while (cs[o[i]].p.x < mid.x) or ((cs[o[i]].p.x = mid.x) and
          (cs[o[i]].p.y < mid.y)) do
        Inc(i);
      while (cs[o[j]].p.x > mid.x) or ((cs[o[j]].p.x = mid.x) and
          (cs[o[j]].p.y > mid.y)) do
        Dec(j);
      if i <= j then
      begin
        x    := o[i];
        o[i] := o[j];
        o[j] := x;
        Inc(i);
        Dec(j);
      end;
    until i > j;
    if l < j then
      SortCons(l, j);
    if i < r then
      SortCons(i, r);
  end;

  function min(const a, b: TStar): TStar;
  begin
    if (a.x < b.x) or ((a.x = b.x) and (a.y < b.y)) then
      exit(a)
    else
      exit(b);
  end;

  function min(const a, b: longint): longint;
  begin
    if a < b then
      exit(a)
    else
      exit(b);
  end;

  function max(const a, b: longint): longint;
  begin
    if a > b then
      exit(A)
    else
      exit(b);
  end;

  procedure GetCons(const cid: longint; sx, sy: longint);
  var
    h, t, i, nx, ny: longint;
    now: TStar;
  begin
    h      := 0;
    t      := 1;
    Q[t].x := sx;
    Q[t].y := sy;
    map[sx, sy] := False;
    with cs[cid] do
    begin
      Count := 1;
      s[Count].x := sx;
      s[Count].y := sy;
      p    := s[Count];
      p.x  := sx;
      p.y  := sy;
      minx := sx;
      miny := sy;
      maxx := sx;
      maxy := sy;
    end;
    repeat
      Inc(h);
      now := Q[h];
      for i := 0 to 7 do
      begin
        nx := now.x + dx[i];
        ny := now.y + dy[i];
        if (nx > 0) and (nx <= n) and (ny > 0) and (ny <= m) then
          if map[nx, ny] then
          begin
            Inc(t);
            Q[t].x      := nx;
            Q[t].y      := ny;
            map[nx, ny] := False;
            with cs[cid] do
            begin
              Inc(Count);
              s[Count].x := nx;
              s[Count].y := ny;
              p    := Min(p, s[Count]);
              maxx := max(maxx, nx);
              maxy := max(maxy, ny);
              minx := min(minx, nx);
              miny := min(miny, ny);
            end;
          end;
      end;
    until h >= t;
    with cs[cid] do
    begin
      Dec(maxx, minx);
      Dec(maxy, miny);
      for i := 1 to Count do
      begin
        Dec(s[i].x, minx);
        Dec(s[i].y, miny);
      end;
    end;
  end;

  function issame(const a, b: longint): boolean;
  var
    i:     longint;
    found: boolean;
  begin
    if cs[a].Count <> cs[b].Count then
      exit(False);
    fillchar(cmp, sizeof(cmp), 0);
    for i := 1 to cs[a].Count do
      cmp[cs[a].s[i].x, cs[a].s[i].y] := True;

    with cs[b] do
    begin
      //0
      found := True;
      for i := 1 to Count do
        if not cmp[s[i].x, s[i].y] then
        begin
          found := False;
          break;
        end;
      if found then
        exit(True);
      //1  x
      found := True;
      for i := 1 to Count do
        if not cmp[maxx - s[i].x, s[i].y] then
        begin
          found := False;
          break;
        end;
      if found then
        exit(True);
      //2 y
      found := True;
      for i := 1 to Count do
        if not cmp[s[i].x, maxy - s[i].y] then
        begin
          found := False;
          break;
        end;
      if found then
        exit(True);
      //3 xy
      found := True;
      for i := 1 to Count do
        if not cmp[maxx - s[i].x, maxy - s[i].y] then
        begin
          found := False;
          break;
        end;
      if found then
        exit(True);
      //4 +90
      found := True;
      for i := 1 to Count do
        if not cmp[s[i].y, maxx - s[i].x] then
        begin
          found := False;
          break;
        end;
      if found then
        exit(True);
      //5 +90 x
      found := True;
      for i := 1 to Count do
        if not cmp[maxy - s[i].y, maxx - s[i].x] then
        begin
          found := False;
          break;
        end;
      if found then
        exit(True);
      //6 +90 y
      found := True;
      for i := 1 to Count do
        if not cmp[s[i].y, s[i].x] then
        begin
          found := False;
          break;
        end;
      if found then
        exit(True);
      //7 +90 xy
      found := True;
      for i := 1 to Count do
        if not cmp[maxy - s[i].y, s[i].x] then
        begin
          found := False;
          break;
        end;
      if found then
        exit(True);
    end;
    exit(False);
  end;

  {MAIN SECTION}
  procedure ReadData;
  var
    rd:   ansistring;
    i, j: longint;
  begin
    readln(n, m);
    for i := 1 to n do
    begin
      readln(rd);
      for j := 1 to m do
        map[i, j] := boolean(rd[j] = '1');
    end;
  end;

  procedure Main;
  var
    i, j:   longint;
    markid: longint;
  begin
    ctot := 0;
    for i := 1 to n do
      for j := 1 to m do
        if map[i, j] then
        begin
          Inc(ctot);
          o[ctot] := ctot;
          GetCons(ctot, i, j);
        end;
    // writeln('found');
    for i := 1 to ctot - 1 do
    begin
      same[i, i] := True;
      for j := i + 1 to ctot do
      begin
        same[i, j] := issame(i, j);
        same[j, i] := same[i, j];
      end;
    end;
    same[ctot, ctot] := True;
    SortCons(1, ctot);
    //  writeln('Sorted');
    markid := 1;
    for i := 1 to ctot do
    begin
      if cs[o[i]].order = 0 then
      begin
        cs[o[i]].order := markid;
        for j := 1 to ctot do
          if same[o[i], o[j]] then
            cs[o[j]].order := markid;
        Inc(markid);
      end;
      with cs[o[i]] do
        for j := 1 to Count do
        begin
          ans[s[j].x + minx, s[j].y + miny] := order;
          {if o[i]=3 then writeln(s[j].x + minx, ',',s[j].y + miny);} end;
    end;
  end;

  procedure Print;
  var
    i, j: longint;
  begin
    for i := 1 to n do
    begin
      for j := 1 to m do
        if ans[i, j] <> 0 then
          Write(chr(Ord('a') + ans[i, j] - 1))
        else
          Write('0');
      writeln;
    end;
  end;

begin
  {$IFNDEF ONLINE_JUDGE}
  Assign(input, 'oj1638.in');
  reset(input);
  Assign(output, 'oj1638.out');
  rewrite(output);
  {$ENDIF}
  ReadData;
  Main;
  Print;
end.

