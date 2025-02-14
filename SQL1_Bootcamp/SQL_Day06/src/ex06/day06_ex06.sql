CREATE SEQUENCE seq_person_discounts START 1;
ALTER TABLE person_discounts
ALTER COLUMN id
SET DEFAULT NEXTVAL('seq_person_discounts');
SELECT setval(
    'seq_person_discounts',
    (
      SELECT max(id) + 1
      FROM person_discounts
    )
  );