COMMENT ON TABLE person_discounts IS 'Table of discounts for person';
COMMENT ON COLUMN person_discounts.id IS 'Primary key';
COMMENT ON COLUMN person_discounts.person_id IS 'person ID';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'pizzeria ID';
COMMENT ON COLUMN person_discounts.discount IS 'Value of discount';