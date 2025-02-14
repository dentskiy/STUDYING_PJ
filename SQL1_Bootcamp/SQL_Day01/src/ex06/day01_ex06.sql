SELECT ad.action_date,
  p.name AS person_name
FROM(
    SELECT order_date as action_date,
      person_id
    FROM person_order
    INTERSECT ALL
    SELECT visit_date,
      person_id
    FROM person_visits
  ) AS ad
  JOIN person p ON p.id = ad.person_id
ORDER BY 1 ASC,
  2 DESC;