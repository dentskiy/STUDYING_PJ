WITH recursive r AS (
  SELECT *,
    1 as level,
    point1 as tour,
    0 as sum_cost
  FROM graph
  WHERE point1 = 'a'
  union
  SELECT g.*,
    r.level + 1,
    concat(r.tour, ',', g.point1),
    r.sum_cost + r.cost
  FROM r
    JOIN graph g ON g.point1 = r.point2
  WHERE r.level < 5
    and case
      WHEN r.level < 4 THEN g.point1 != 'a'
      AND g.point2 != r.point1
      ELSE g.point1 = 'a'
    end
),
full_tour AS(
  SELECT DISTINCT tour,
    sum_cost as total_cost
  FROM r
  WHERE r.level = 5
)
SELECT total_cost,
  concat('{', tour, '}') AS tour
FROM full_tour
WHERE total_cost = (
    SELECT MIN(total_cost)
    FROM full_tour
  )
ORDER BY 1,
  2;