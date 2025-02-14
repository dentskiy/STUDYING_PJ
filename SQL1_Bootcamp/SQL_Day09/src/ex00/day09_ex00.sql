CREATE TABLE IF NOT EXISTS person_audit (
  created timestamp with time zone not null default current_timestamp,
  type_event char(1) not null default 'I',
  LIKE person,
  constraint ch_type_event check (type_event in ('I', 'D', 'U'))
);

alter table person_audit rename column id to row_id;

CREATE OR REPLACE FUNCTION fnc_trg_person_insert_audit() RETURNS trigger AS $$
BEGIN
INSERT INTO person_audit SELECT current_timestamp, 'I', NEW.*;
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_insert_audit
AFTER INSERT ON person
FOR EACH ROW
EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk');
