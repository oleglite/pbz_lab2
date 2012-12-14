CREATE TABLE Person (
	id_person INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	name TEXT,
	address TEXT
);




CREATE TABLE Position (
	position_name TEXT PRIMARY KEY NOT NULL
);




CREATE TABLE PersonCrew (
	id_person_crew INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	Position_id TEXT NOT NULL REFERENCES Position,
	Person_id INTEGER NOT NULL REFERENCES Person,
	crew_number INTEGER NOT NULL REFERENCES Crew
);




CREATE TABLE Registration (
	id_registration INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	from_date DATE,
	to_date DATE,
	crew_number INTEGER NOT NULL REFERENCES Crew,
	cutter_name TEXT NOT NULL REFERENCES Cutter
);




CREATE TABLE Cutter (
	cutter_name TEXT PRIMARY KEY NOT NULL,
	cutter_type TEXT,
	displacement INTEGER,
	buiding_date DATE
);




CREATE TABLE Catch (
	id_catch INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	weight INTEGER,
	quality INTEGER,
	sort_name TEXT NOT NULL REFERENCES Sort
);




CREATE TABLE Shoal (
	id_shoal INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	shoal_info TEXT
);




CREATE TABLE Crew (
	crew_number INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL
);




CREATE TABLE ShoalVisit (
	id_shoal_visit INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	arrive_date DATE,
	leave_date DATE,
	Shoal_id INTEGER NOT NULL REFERENCES Shoal,
	Registration_id INTEGER NOT NULL REFERENCES Registration,
	Catch_id INTEGER NOT NULL REFERENCES Catch
);




CREATE TABLE Sort (
	sort_name TEXT PRIMARY KEY NOT NULL
);

