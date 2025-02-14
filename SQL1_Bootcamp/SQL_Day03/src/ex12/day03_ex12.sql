INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT g + (
    SELECT MAX(id)
    FROM person_order
  ) as id,
  ps.id AS person_id,
  (
    SELECT id
    FROM menu
    WHERE pizza_name = 'greek pizza'
  ) AS menu_id,
  '2022-02-25'
FROM person ps
  JOIN generate_series(
    1,
    (
      SELECT count(id)
      FROM person
    )
  ) AS g ON g = id;