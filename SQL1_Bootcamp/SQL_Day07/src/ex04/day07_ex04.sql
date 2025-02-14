WITH t AS (
  SELECT person_id,
    count(*) AS count_of_visits
  FROM person_visits
  GROUP BY person_id
)
SELECT p.name,
  t.count_of_visits
FROM t
  JOIN person p ON p.id = t.person_id
  AND t.count_of_visits > 3