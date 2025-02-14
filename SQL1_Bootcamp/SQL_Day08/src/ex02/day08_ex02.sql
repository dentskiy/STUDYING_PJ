-- s1
begin transaction isolation level repeatable read;
-- s2
begin transaction isolation level repeatable read;
-- s1
select *
from pizzeria
where name = 'Pizza Hut';
-- s2
select *
from pizzeria
where name = 'Pizza Hut';
-- s1
update pizzeria
set rating = 4
where name = 'Pizza Hut';
-- s2
update pizzeria
set rating = 3.6
where name = 'Pizza Hut';
-- s1
commit;
-- s2
commit;
-- s1
select *
from pizzeria
where name = 'Pizza Hut';
-- s2
select *
from pizzeria
where name = 'Pizza Hut';