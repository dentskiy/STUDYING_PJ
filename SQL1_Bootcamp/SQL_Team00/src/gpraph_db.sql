DROP TABLE graph;
CREATE TABLE graph (
  point1 varchar not NULL,
  point2 varchar not NULL,
  cost integer not NULL
);
INSERT INTO graph
VALUES ('a', 'b', 10),
  ('a', 'c', 15),
  ('a', 'd', 20),
  ('b', 'a', 10),
  ('b', 'c', 35),
  ('b', 'd', 25),
  ('c', 'a', 15),
  ('c', 'b', 35),
  ('c', 'd', 30),
  ('d', 'a', 20),
  ('d', 'c', 30),
  ('d', 'b', 25);