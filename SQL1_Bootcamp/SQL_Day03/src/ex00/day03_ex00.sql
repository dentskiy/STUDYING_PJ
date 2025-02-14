WITH kate_visits AS (
  SELECT *
  FROM person_visits
  WHERE person_id IN(
      SELECT id
      FROM person
      WHERE name = 'Kate'
    )
)
SELECT m.pizza_name,
  m.price,
  pz.name as pizzaria_name,
  kv.visit_date
FROM kate_visits kv
  JOIN pizzeria pz ON kv.pizzeria_id = pz.id
  JOIN menu m ON m.pizzeria_id = pz.id
  AND m.price BETWEEN 800 AND 1000
ORDER BY 1,
  2,
  3;