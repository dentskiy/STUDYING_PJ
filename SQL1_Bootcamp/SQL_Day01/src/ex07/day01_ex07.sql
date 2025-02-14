SELECT po.order_date,
  concat(p.name, ' (age:', p.age, ')') AS person_information
FROM person_order po
  JOIN person p ON p.id = po.person_id
ORDER BY 1 ASC,
  2 ASC;