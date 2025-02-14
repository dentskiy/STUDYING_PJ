WITH mens AS (
  SELECT *
  FROM person
  WHERE address IN('Moscow', 'Samara')
    AND gender = 'male'
)
SELECT DISTINCT mens.name
FROM mens
  JOIN person_order po ON mens.id = po.person_id
  JOIN menu m ON po.menu_id = m.id
WHERE m.pizza_name IN('pepperoni pizza', 'mushroom pizza')
ORDER BY 1 DESC;