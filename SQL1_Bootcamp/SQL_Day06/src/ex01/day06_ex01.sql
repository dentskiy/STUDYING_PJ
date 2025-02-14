INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
SELECT ROW_NUMBER() OVER(
    ORDER BY po.person_id
  ) as id,
  po.person_id,
  m.pizzeria_id,
  CASE
    WHEN count(*) = 1 then 10.5::numeric
    WHEN count(*) = 2 then 22::numeric
    ELSE 30::numeric
  end AS discount
FROM person_order po
  JOIN menu m ON m.id = po.menu_id
GROUP BY po.person_id,
  m.pizzeria_id