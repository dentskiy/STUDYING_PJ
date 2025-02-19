CREATE OR REPLACE FUNCTION fnc_persons_female() RETURNS TABLE(LIKE person) AS $$
  SELECT * FROM person WHERE gender = 'female'
$$ LANGUAGE SQL;
CREATE OR REPLACE FUNCTION fnc_persons_male() RETURNS TABLE(LIKE person) AS $$
  SELECT * FROM person WHERE gender = 'male'
$$ LANGUAGE SQL;

SELECT *
FROM fnc_persons_male();

SELECT *
FROM fnc_persons_female();
