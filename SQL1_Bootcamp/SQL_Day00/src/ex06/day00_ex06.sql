SELECT (
    SELECT name
    FROM person
    WHERE id = po.person_id
  ) AS NAME,
  (
    SELECT name
    FROM person
    WHERE id = po.person_id
  ) = 'Denis' AS check_name
FROM person_order AS po
WHERE order_date = '2022-01-07'
  AND (
    menu_id = 13
    OR menu_id = 14
    OR menu_id = 18
  );