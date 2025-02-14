CREATE UNIQUE INDEX IF NOT EXISTS idx_menu_unique ON menu(pizzeria_id, pizza_name);
set enable_seqscan = off;
EXPLAIN ANALYZE
SELECT pizzeria_id,
  pizza_name
FROM menu