CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop int default 10)
  RETURNS SETOF int AS $$
  WITH RECURSIVE r AS ( 
    SELECT 1 AS L, 1 AS R
    UNION 
    (
      SELECT R AS L,
        L + R AS R
      FROM r
      WHERE R < pstop
    )
  )
  SELECT L
  FROM r;
$$ LANGUAGE SQL;

select * from fnc_fibonacci(100);
select * from fnc_fibonacci();


