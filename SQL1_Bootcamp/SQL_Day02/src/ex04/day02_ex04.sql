SELECT m.pizza_name,
  pz.name AS pizzaria_name,
  m.price
FROM menu m
  JOIN pizzeria pz ON m.pizzeria_id = pz.id
WHERE m.pizza_name = 'mushroom pizza'
  OR m.pizza_name = 'pepperoni pizza'
ORDER BY 1,
  2;