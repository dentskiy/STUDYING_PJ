(
  SELECT pz.name AS name,
    count(pv.*) AS count,
    'visit' AS action_type
  FROM person_visits pv
    JOIN pizzeria pz ON pz.id = pv.pizzeria_id
  GROUP BY pz.name
  ORDER BY 2 DESC
  LIMIT 3
)
UNION
(
  SELECT pz.name,
    count(po.*),
    'order'
  FROM person_order po
    JOIN menu m ON m.id = po.menu_id
    JOIN pizzeria pz ON pz.id = m.pizzeria_id
  GROUP BY pz.name
  ORDER BY 2 DESC
  LIMIT 3
)
ORDER BY 3 ASC,
  2 DESC;