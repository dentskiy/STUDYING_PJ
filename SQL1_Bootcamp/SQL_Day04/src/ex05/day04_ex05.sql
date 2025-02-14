CREATE VIEW v_price_with_discount (name, pizza_name, price, discount_price) AS
SELECT ps.name,
  m.pizza_name,
  m.price,
  round(0.9 * price) AS discount_price
FROM person_order po
  JOIN person ps ON po.person_id = ps.id
  JOIN menu m ON po.menu_id = m.id
ORDER BY 1,
  2;