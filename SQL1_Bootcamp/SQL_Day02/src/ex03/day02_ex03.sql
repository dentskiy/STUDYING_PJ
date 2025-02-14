WITH g AS (
  SELECT g::date
  FROM generate_series('2022-01-01', '2022-01-10', interval '1 day') AS g
),
pv AS (
  SELECT *
  FROM person_visits
  WHERE person_id = 1
    OR person_id = 2
)
SELECT g::date AS missing_date
FROM g
  LEFT JOIN pv ON pv.visit_date = g
WHERE pv.id is NULL
ORDER BY 1;