INSERT INTO person_visits
VALUES (
    (
      SELECT max(id) + 1
      FROM person_visits
    ),
    (
      SELECT id
      FROM person
      WHERE name = 'Dmitriy'
    ),
    (
      SELECT pz.id
      FROM pizzeria pz
        JOIN menu m ON m.pizzeria_id = pz.id
        AND m.price < 800
      WHERE pz.name != 'Papa Johns'
      limit 1
    ), '2022-01-08'
  );
REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;