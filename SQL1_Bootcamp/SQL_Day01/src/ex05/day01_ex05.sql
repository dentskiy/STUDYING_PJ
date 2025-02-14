SELECT pr.*,
  pz.*
FROM person pr
  CROSS JOIN pizzeria pz
ORDER BY pr.id,
  pz.id;