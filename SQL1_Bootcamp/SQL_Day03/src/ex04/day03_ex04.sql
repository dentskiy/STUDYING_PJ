WITH full_orders AS (
  SELECT pz.name AS pizzeria_name,
    ps.gender AS ps_g
  FROM person_order po
    JOIN person ps ON po.person_id = ps.id
    JOIN menu m ON m.id = po.menu_id
    JOIN pizzeria pz ON m.pizzeria_id = pz.id
) (
  SELECT fo.pizzeria_name
  FROM full_orders fo
  WHERE fo.ps_g = 'female'
  EXCEPT
  SELECT fo.pizzeria_name
  FROM full_orders fo
  WHERE fo.ps_g = 'male'
)
UNION
(
  SELECT fo.pizzeria_name
  FROM full_orders fo
  WHERE fo.ps_g = 'male'
  EXCEPT
  SELECT fo.pizzeria_name
  FROM full_orders fo
  WHERE fo.ps_g = 'female'
)
ORDER BY 1;