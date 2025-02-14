SELECT COALESCE(ps.name, '-') AS person_name,
  pv.visit_date,
  COALESCE(pz.name, '-') AS pizzaria_name
FROM person_visits pv
  RIGHT JOIN generate_series('2022-01-01', '2022-01-03', interval '1 day') AS gn ON gn = pv.visit_date
  FULL JOIN person ps ON ps.id = pv.person_id
  FULL JOIN pizzeria pz ON pz.id = pv.pizzeria_id
ORDER BY 1,
  2,
  3;