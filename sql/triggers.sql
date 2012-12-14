-- Тригер добавления катера, если катер, указанный при добавлении регистрации не существует
CREATE TRIGGER newCutterInsertRegistration BEFORE INSERT ON Registration 
BEGIN
	INSERT OR IGNORE INTO Cutter (cutter_name) VALUES (new.cutter_name);
END;

-- Тригер добавления посещения банки при добавлении улова
CREATE TRIGGER insertShoalVisit AFTER INSERT ON Catch 
BEGIN

INSERT INTO ShoalVisit (Catch_id) VALUES (new.id_catch);

END

-- Тригер добавления сорта рыбы при добавлении улова
CREATE TRIGGER insertSort BEFORE INSERT ON Catch 
BEGIN

INSERT OR IGNORE INTO Sort (sort_name) VALUES (new.sort_name);

END
