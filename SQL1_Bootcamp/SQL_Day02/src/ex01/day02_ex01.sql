SELECT g::date AS missing_date
FROM generate_series('2022-01-01', '2022-01-10', interval '1 day') AS g
  LEFT JOIN (
    SELECT *
    FROM person_visits
    WHERE person_id = 1
      OR person_id = 2
  ) AS pv ON pv.visit_date = g
WHERE pv.id is NULL
ORDER BY 1;