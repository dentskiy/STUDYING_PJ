CREATE UNIQUE INDEX IF NOT EXISTS idx_person_discounts_unique ON person_discounts(person_id, pizzeria_id);
set enable_seqscan = off;
EXPLAIN ANALYZE
SELECT *
FROM person_discounts
WHERE person_id = 3;