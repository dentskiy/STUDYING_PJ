WITH full_visits AS (
  SELECT pz.name AS pizzeria_name,
    ps.gender AS ps_g
  FROM person_visits pv
    JOIN person ps ON pv.person_id = ps.id
    JOIN pizzeria pz ON pv.pizzeria_id = pz.id
) (
  SELECT fv.pizzeria_name
  FROM full_visits fv
  WHERE fv.ps_g = 'female'
  EXCEPT ALL
  SELECT fv.pizzeria_name
  FROM full_visits fv
  WHERE fv.ps_g = 'male'
)
UNION ALL
(
  SELECT fv.pizzeria_name
  FROM full_visits fv
  WHERE fv.ps_g = 'male'
  EXCEPT ALL
  SELECT fv.pizzeria_name
  FROM full_visits fv
  WHERE fv.ps_g = 'female'
)
ORDER BY 1;