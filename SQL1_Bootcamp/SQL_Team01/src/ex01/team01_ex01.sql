insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

WITH only_cr AS(
  SELECT bl.user_id,
    bl.money,
    bl.updated AS balance_up,
    cr.name,
    cr.rate_to_usd,
    cr.updated AS currency_up
  FROM balance bl
  JOIN currency cr ON cr.id = bl.currency_id AND cr.updated IN (
  (
    SELECT MAX(cr1.updated)
    FROM currency cr1
    WHERE cr1.id = cr.id AND bl.updated > cr1.updated
  ) UNION ALL (
    SELECT MIN(cr2.updated)
    FROM currency cr2
    WHERE cr2.id = cr.id AND bl.updated <= cr2.updated
  )
  )
)
SELECT COALESCE(u.name, '<not defined>') AS name,
  COALESCE(u.lastname, '<not defined>') AS lastname,
  t.name AS currency_name,
  (t.money * t.rate_to_usd) AS currency_in_usd
FROM only_cr t
  LEFT JOIN "user" u ON u.id = t.user_id
WHERE t.currency_up = (
  SELECT MIN(t1.currency_up)
  FROM only_cr t1
  WHERE t.user_id = t1.user_id 
    AND t.balance_up = t1.balance_up
    AND t.name = t1.name
  GROUP BY t1.user_id, t1.balance_up, t1.name
)
ORDER BY 1 DESC, 2, 3;