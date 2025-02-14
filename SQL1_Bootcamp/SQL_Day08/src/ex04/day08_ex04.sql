-- s1
begin transaction isolation level serializable;
-- s2
begin transaction isolation level serializable;
-- s1
select *
from pizzeria
where name = 'Pizza Hut';
-- s2
update pizzeria
set rating = 3.0
where name = 'Pizza Hut';
commit;
-- s1
select *
from pizzeria
where name = 'Pizza Hut';
commit;
select *
from pizzeria
where name = 'Pizza Hut';
-- s2
select *
from pizzeria
where name = 'Pizza Hut';