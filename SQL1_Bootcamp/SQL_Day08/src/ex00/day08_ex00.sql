-- session 1
begin;
-- session 2
begin;
-- session 1
update pizzeria
set rating = 5
where name = 'Pizza Hut';
select *
from pizzeria
where name = 'Pizza Hut';
-- session 2
select *
from pizzeria
where name = 'Pizza Hut';
-- session 1
commit;
-- session 2
select *
from pizzeria
where name = 'Pizza Hut';
end;