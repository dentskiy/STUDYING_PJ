SELECT pz.name,
  count(po.*) AS count_of_order,
  round(avg(m.price), 2) AS average_price,
  max(m.price) AS max_price,
  min(m.price) AS min_price
FROM menu m
  JOIN person_order po ON m.id = po.menu_id
  JOIN pizzeria pz ON m.pizzeria_id = pz.id
GROUP BY pz.name
ORDER BY 1;