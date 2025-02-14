WITH females AS (
  SELECT *
  FROM person
  WHERE gender = 'female'
)
SELECT f.name
FROM females f
  JOIN person_order po ON f.id = po.person_id
  JOIN menu m ON po.menu_id = m.id
WHERE m.pizza_name = 'pepperoni pizza'
INTERSECT
SELECT f2.name
FROM females f2
  JOIN person_order po ON f2.id = po.person_id
  JOIN menu m ON po.menu_id = m.id
WHERE m.pizza_name = 'cheese pizza'
ORDER BY 1;