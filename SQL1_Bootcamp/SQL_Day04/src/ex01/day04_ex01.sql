SELECT name
FROM v_person_female
UNION ALL
SELECT name
FROM v_person_male
ORDER BY 1;