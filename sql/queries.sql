-- 1. Для каждого катера вывести даты выхода в море с указанием улова
SELECT Cutter.cutter_name, Registration.from_date, Catch.sort_name, Catch.weight, Catch.quality
	FROM Registration, Cutter, ShoalVisit, Catch
	WHERE Registration.cutter_name = Cutter.cutter_name
	AND ShoalVisit.Registration_id = Registration.id_registration
	AND ShoalVisit.Catch_id = Catch.id_catch;
	
-- 2. Предоставить возможность добавления выхода катера в море с указанием команды
INSERT INTO Registration ("from_date", "crew_number", "cutter_name") VALUES (:from_date, :crew_number, :cutter_name);

-- 3. Для указанного интервала дат вывести для каждого сорта рыбы список катеров с наибольшим уловом
DROP TABLE IF EXISTS q3_sum;
CREATE TEMPORARY TABLE q3_sum AS 
	SELECT Catch.sort_name AS sort_name, SUM(Catch.weight) AS weight_sum, Registration.cutter_name AS cutter_name
		FROM Catch, Registration, ShoalVisit
		WHERE ShoalVisit.Registration_id = Registration.id_registration
		AND ShoalVisit.Catch_id = Catch.id_catch
		AND ShoalVisit.arrive_date >= :arrive_date AND ShoalVisit.leave_date <= :leave_date
		GROUP BY Catch.sort_name, Registration.cutter_name;
SELECT sort_name, cutter_name
	FROM q3_sum outers
	WHERE outers.weight_sum = (
		SELECT MAX(weight_sum)
			FROM q3_sum inners
			WHERE inners.sort_name = outers.sort_name
	);
	
-- 4. Для указанного интервала дат вывести список банок, с указанием среднего улова за этот период
SELECT ShoalVisit.Shoal_id, AVG(Catch.weight) AS avg_weight
	FROM ShoalVisit, Catch
	WHERE ShoalVisit.Catch_id = Catch.id_catch
	AND ShoalVisit.arrive_date >= :arrive_date AND ShoalVisit.leave_date <= :leave_date
	GROUP BY ShoalVisit.Shoal_id;

-- 5. Предоставить возможность добавления новой банки с указанием данных о ней
INSERT INTO Shoal ( "id_shoal","shoal_info" ) VALUES ( :id_shoal, :shoal_info );

-- 6. Для заданной банки вывести список катеров, которые получили улов выше среднего
SELECT Registration.cutter_name, Catch.weight
	FROM ShoalVisit, Catch, Registration
	WHERE ShoalVisit.Shoal_id = :id_shoal
	AND ShoalVisit.Catch_id = Catch.id_catch
	AND ShoalVisit.Registration_id = Registration.id_registration
	AND Catch.weight > (
		SELECT AVG(Catch.weight)
			FROM Catch
	);

-- 7. Вывести список сортов рыбы и для каждого сорта список рейсов с указанием даты выхода и возвращения, количества улова
SELECT Catch.sort_name, Registration.id_registration, Registration.from_date, Registration.to_date, Catch.weight
	FROM ShoalVisit, Catch, Registration
	WHERE ShoalVisit.Catch_id = Catch.id_catch
	AND ShoalVisit.Registration_id = Registration.id_registration
	ORDER BY Catch.sort_name;

-- 8. Для выбранного пользователем рейса и банки добавить данные о сорте и количестве пойманной рыбы
INSERT INTO Catch (weight, sort_name) VALUES (:weight, :sort_name);
UPDATE ShoalVisit SET Shoal_id = :id_shoal, Registration_id = :id_registration
	WHERE ShoalVisit.Catch_id = (
		SELECT MAX(id_catch)
			FROM Catch
	);

-- 9. Предоставить возможность пользователю изменять характеристики выбранного катера
UPDATE Cutter SET cutter_type = :cutter_type, displacement = :displacement, building_date = :building_date
	WHERE cutter_name = :cutter_name;

-- 10. Предоставить возможность добавления нового катера
INSERT INTO Cutter ("cutter_name", "cutter_type", "displacement", "building_date") VALUES (:cutter_name, :cutter_type, :displacement, :building_date);

-- 11. Для указанного сорта рыбы и банки вывести список рейсов с указанием количества пойманной рыбы
SELECT Registration.id_Registration, Catch.weight
	FROM ShoalVisit, Catch, Registration
	WHERE Catch.sort_name = :sort_name
	AND ShoalVisit.Shoal_id = :id_shoal
	AND ShoalVisit.Registration_id = Registration.id_registration
	AND ShoalVisit.Catch_id = Catch.id_catch;

