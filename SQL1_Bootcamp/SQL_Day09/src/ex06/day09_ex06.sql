CREATE OR REPLACE FUNCTION
fnc_person_visits_and_eats_on_date(
  pperson varchar default 'Dmitriy',  
  pprice numeric default 500,
  pdate date default '2022-01-08'
)
RETURNS TABLE(pizzeria_name varchar) AS $$
BEGIN
  RETURN QUERY SELECT pz.name as pizzeria_name
  FROM person_visits pv
    JOIN person p ON pv.person_id = p.id AND p.name IN(pperson)
    JOIN pizzeria pz ON pz.id = pv.pizzeria_id
    JOIN menu m ON pz.id = m.pizzeria_id AND m.price < pprice
  WHERE pv.visit_date IN(pdate)
  GROUP BY pz.name;
END;
$$ LANGUAGE plpgsql;

select *
from fnc_person_visits_and_eats_on_date(pprice := 800);

select *
from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');
