CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS WITH dima AS (
  SELECT *
  FROM person
  WHERE name = 'Dmitriy'
)
SELECT pz.name as pizzaria_name
FROM dima
  JOIN person_visits pv ON dima.id = pv.person_id
  JOIN pizzeria pz ON pv.pizzeria_id = pz.id
  JOIN menu m ON pz.id = m.pizzeria_id
WHERE pv.visit_date = '2022-01-08'
  AND m.price < 800;