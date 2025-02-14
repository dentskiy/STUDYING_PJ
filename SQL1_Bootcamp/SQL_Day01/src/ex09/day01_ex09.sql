/*
 using IN
 */
SELECT pz.name
FROM pizzeria pz
WHERE pz.id NOT IN (
    SELECT pv.pizzeria_id
    FROM person_visits pv
  );
/*
 using EXIST
 */
SELECT pz.name
FROM pizzeria pz
WHERE NOT EXISTS (
    SELECT pv.pizzeria_id
    FROM person_visits pv
    WHERE pv.pizzeria_id = pz.id
  );