SELECT p.address,
  pz.name,
  count(po.*) as count_of_orders
FROM person_order po
  JOIN person p ON p.id = po.person_id
  JOIN menu m ON po.menu_id = m.id
  JOIN pizzeria pz ON pz.id = m.pizzeria_id
GROUP BY p.address,
  pz.name
ORDER BY 1,
  2;