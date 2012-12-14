-- ������ ���������� ������, ���� �����, ��������� ��� ���������� ����������� �� ����������
CREATE TRIGGER newCutterInsertRegistration BEFORE INSERT ON Registration 
BEGIN
	INSERT OR IGNORE INTO Cutter (cutter_name) VALUES (new.cutter_name);
END;

-- ������ ���������� ��������� ����� ��� ���������� �����
CREATE TRIGGER insertShoalVisit AFTER INSERT ON Catch 
BEGIN

INSERT INTO ShoalVisit (Catch_id) VALUES (new.id_catch);

END

-- ������ ���������� ����� ���� ��� ���������� �����
CREATE TRIGGER insertSort BEFORE INSERT ON Catch 
BEGIN

INSERT OR IGNORE INTO Sort (sort_name) VALUES (new.sort_name);

END
