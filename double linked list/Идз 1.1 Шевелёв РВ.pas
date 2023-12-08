type
  List_Elem = ^Elem;
  Elem = record
    prev: List_Elem;
    data: integer;
    count: integer;
    next: List_Elem;
  end;

var
  head1, head2, head3: List_Elem;

procedure printList(var head: List_Elem);
var
  elem: List_Elem;
begin
  if head <> nil then begin
    write('...⟷');
    write('[', head^.data, ']', '(', head^.count, ')', head, '⟷');
    elem := head;
    while (elem^.next <> head) do
    begin
      elem := elem^.next;
      write('[', elem^.data, ']', '(', elem^.count, ')', elem, '⟷');
    end;
    writeln('...');
  end;
end;

procedure Free(var head: List_Elem);
var
  current, Del: List_Elem;
begin
  if head <> nil then begin
    current := head;
    while (current^.next <> head) do
    begin
      Del := current;
      current := current^.next;
      dispose(Del);
      head^.prev^.next := current;
      current^.prev := head^.prev;
      head := current;
      printlist(head);
    end;
    dispose(head);
  end;
end;

procedure Delete_Element(var head: List_Elem; data: integer);
var
  current: List_Elem;
begin
  if head <> nil then begin
    current := head;
    while (current^.data <> data) and (current^.next <> head) do current := current^.next;
    if current^.data = data then begin
      if current^.count > 1 then begin
        current^.count -= 1;
      end
      else begin
        if current = head then head := head^.next;  
        current^.next^.prev := current^.prev;
        current^.prev^.next := current^.next;
        dispose(current);
      end;
    end;
  end;  
end;

procedure Union(var head1: List_Elem; var head2: List_Elem; var head: List_Elem);
var
  insert, cur1, cur2: List_Elem;
begin
  if (head1 <> nil) and (head2 <> nil) then begin
    cur1 := head1;
    cur2 := head2;
    while (cur1^.next <> head1) and (cur2^.next <> head2) do
    begin
      new(insert);
      insert^.data := min(cur1^.data, cur2^.data);
      if head = nil then begin
        head := insert;
        head^.next := head;
        head^.prev := head;
      end;
      if (cur1^.data < cur2^.data) then begin
        insert^.count += cur1^.count;
        cur1 := cur1^.next;
      end
      else begin
        if (cur1^.data = cur2^.data) then begin
          insert^.count += cur1^.count + cur2^.count;
          cur1 := cur1^.next;
          cur2 := cur2^.next;
        end
        else begin
          if (cur1^.data > cur2^.data) then begin
            insert^.count += cur2^.count;
            cur2 := cur2^.next;
          end;
        end;
      end;
      if head <> insert then begin
        insert^.next := head;
        insert^.prev := head^.prev;
        head^.prev^.next := insert;
        head^.prev := insert;
      end;
    end;
    new(insert);
    insert^.data := min(cur1^.data, cur2^.data);
    if (cur1^.data < cur2^.data) then insert^.count += cur1^.count
    else begin
      if (cur1^.data = cur2^.data) then insert^.count += cur1^.count + cur2^.count
      else if (cur1^.data > cur2^.data) then insert^.count += cur2^.count
    end;
    insert^.next := head;
    insert^.prev := head^.prev;
    head^.prev^.next := insert;
    head^.prev := insert;
  end;
end;

procedure Add(var head: List_Elem; data: integer);
var
  current, insert: List_Elem;
begin
  new(insert);
  insert^.data := data;
  insert^.count += 1;
  if (head = nil) then begin
    head := insert;
    head^.next := head;
    head^.prev := head;
  end
  else begin
    current := head;
    if (head^.prev^.data < data) or (head^.data > data) then begin
      insert^.next := head;
      insert^.prev := head^.prev;
      head^.prev^.next := insert;
      head^.prev := insert;
      if (head^.data > data) then head := insert;
    end
    else begin
      while (current^.next <> head) and (current^.data < data) do current := current^.next;
      if current^.data = data then current^.count += 1
      else begin
        insert^.next := current;
        insert^.prev := current^.prev;
        current^.prev^.next := insert;
        current^.prev := insert;
      end;
    end;
  end;
end;

function Find_Element(var head: List_Elem; data: integer): boolean;
var
  elem: List_Elem;
begin
  if head <> nil then begin
    elem := head;
    while (elem^.next <> head) do
    begin
      if (elem^.data = data) then Find_Element := True;
      elem := elem^.next;
    end;
    if (elem^.data = data) then Find_Element := True;
  end;
end;

begin
  for var i := 1 to 20 do
  begin
    add(head1, i);
    add(head1, i);
    add(head2, i);
    Add(head2, -100);
    Add(head2, -100);
  end;
  print(Find_Element(head1, -49));
  print(Find_Element(head1, -4));
  print(Find_Element(head1, 1));
  writeln;
  Add(head1, -100);
  Add(head1, -100);
  Add(head1, -100);
  Add(head1, -100);
  printlist(head1);
  writeln;
  printlist(head2);
  writeln;
  Union(head1, head2, head3);
  writeln;
  PrintList(head3);
end.