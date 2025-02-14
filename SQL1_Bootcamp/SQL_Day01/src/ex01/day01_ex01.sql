SELECT nm.object_name
FROM (
    SELECT pizza_name AS object_name,
      2 as srt
    FROM menu
    UNION ALL
    SELECT name,
      1 as srt
    FROM person
    ORDER BY srt,
      object_name
  ) AS nm