-- s1
begin;
-- s2
begin;
-- s1
update pizzeria
set rating = 1
where id = 1;
-- s2
update pizzeria
set rating = 2
where id = 2;
-- s1
update pizzeria
set rating = 1
where id = 2;
-- s2
update pizzeria
set rating = 2
where id = 1;
-- s1
commit;
-- s2
commit;
-- s1
select rating
from pizzeria;
-- s2
select rating
from pizzeria;