SELECT p.name,
  m.pizza_name,
  m.price,
  (m.price - (m.price * pd.discount / 100)) AS discount_price,
  pz.name AS pizzeria_name
FROM person_order po
  JOIN person p ON po.person_id = p.id
  JOIN menu m ON m.id = po.menu_id
  JOIN person_discounts pd ON po.person_id = pd.person_id
  AND m.pizzeria_id = pd.pizzeria_id
  JOIN pizzeria pz ON pz.id = m.pizzeria_id
ORDER BY 1,
  2;