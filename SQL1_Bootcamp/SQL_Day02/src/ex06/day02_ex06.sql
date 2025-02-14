SELECT m.pizza_name,
  pz.name AS pizzaria_name
FROM person_order po
  JOIN menu m ON m.id = po.menu_id
  JOIN person ps ON ps.id = po.person_id
  JOIN pizzeria pz ON pz.id = m.pizzeria_id
WHERE ps.name = 'Denis'
  OR ps.name = 'Anna'
ORDER BY 1,
  2;