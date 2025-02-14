CREATE OR REPLACE FUNCTION fnc_trg_person_delete_audit() RETURNS trigger AS $$
BEGIN
INSERT INTO person_audit SELECT current_timestamp, 'D', OLD.*;
RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_delete_audit
AFTER DELETE ON person
FOR EACH ROW
EXECUTE FUNCTION fnc_trg_person_delete_audit();

DELETE FROM person WHERE id = 10;