WITH andrey AS (
  SELECT *
  FROM person
  WHERE name = 'Andrey'
)
SELECT pz.name AS pizzeria_name
FROM andrey
  JOIN person_visits pv ON andrey.id = pv.person_id
  JOIN pizzeria pz ON pv.pizzeria_id = pz.id
EXCEPT
SELECT pz.name AS pizzeria_name
FROM andrey
  JOIN person_order po ON andrey.id = po.person_id
  JOIN menu m ON m.id = po.menu_id
  JOIN pizzeria pz ON m.pizzeria_id = pz.id
ORDER BY 1;