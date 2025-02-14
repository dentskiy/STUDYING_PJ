SELECT pn.name as person_name,
  mn.pizza_name,
  pz.name as pizzeria_name
FROM person_order po
  JOIN person pn ON po.person_id = pn.id
  JOIN menu mn ON po.menu_id = mn.id
  JOIN pizzeria pz ON mn.pizzeria_id = pz.id
ORDER BY 1,
  2,
  3;