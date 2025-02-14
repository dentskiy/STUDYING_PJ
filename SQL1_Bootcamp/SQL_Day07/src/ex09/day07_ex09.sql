SELECT p.address,
  round(
    max(p.age::numeric) - (min(p.age::numeric) / max(p.age::numeric)),
    2
  ) AS formula,
  round(avg(p.age), 2) AS average,
  round(
    max(p.age::numeric) - (min(p.age::numeric) / max(p.age::numeric)),
    2
  ) > round(avg(p.age), 2) AS comparison
FROM person p
GROUP BY address
ORDER BY 1;