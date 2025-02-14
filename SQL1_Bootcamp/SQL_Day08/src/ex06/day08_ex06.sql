-- s1
begin transaction isolation level repeatable read;
-- s2
begin transaction isolation level repeatable read;
-- s1
select sum(rating)
from pizzeria;
-- s2
update pizzeria
set rating = 1
where name = 'Pizza Hut';
commit;
-- s1
select sum(rating)
from pizzeria;
commit;
select sum(rating)
from pizzeria;
-- s2
select sum(rating)
from pizzeria;