SELECT po.order_date,
  concat(p.name, ' (age:', p.age, ')') AS person_information
FROM person_order po
  NATURAL JOIN (
    SELECT id AS person_id,
      name,
      age
    FROM person
  ) as p
ORDER BY 1 ASC,
  2 ASC;