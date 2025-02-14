set enable_seqscan = off;
EXPLAIN ANALYZE
SELECT m.pizza_name,
  pz.name as pizzaria_name
FROM menu m
  JOIN pizzeria pz ON pz.id = m.pizzeria_id;