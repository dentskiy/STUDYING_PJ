WITH pre_t AS (
SELECT COALESCE(u.name, '<not defined>') AS name,
  COALESCE(u.lastname, '<not defined>') AS lastname,
  bl.type,
  bl.volume,
  COALESCE(cr.name, '<not defined>') AS currency_name,
  COALESCE(cr.rate_to_usd, 1) AS last_rate_to_usd
FROM "user" u 
  FULL JOIN (
    SELECT user_id,
      SUM(money) AS volume,
      type,
      currency_id
    FROM balance 
    GROUP BY 1, 3, 4 
  ) AS bl ON u.id = bl.user_id
  FULL JOIN currency cr ON  bl.currency_id = cr.id AND cr.updated = (
    SELECT MAX(cr2.updated)
    FROM currency cr2
    WHERE cr2.id = cr.id
  )
  WHERE bl.type IS NOT NULL
)
SELECT *,
  (volume * last_rate_to_usd) AS total_volume_in_usd
FROM pre_t
ORDER BY 1 DESC, 2 ASC, 3 ASC;
