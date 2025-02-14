WITH pz_actions AS (
  (
    SELECT pz.name AS name
    FROM person_visits pv
      JOIN pizzeria pz ON pz.id = pv.pizzeria_id
  )
  UNION ALL
  (
    SELECT pz.name
    FROM person_order po
      JOIN menu m ON m.id = po.menu_id
      JOIN pizzeria pz ON pz.id = m.pizzeria_id
  )
)
SELECT name,
  count(*) AS total_count
FROM pz_actions
GROUP BY name
ORDER BY 2 DESC,
  1 ASC;