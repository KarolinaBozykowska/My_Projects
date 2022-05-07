DROP DATABASE IF EXISTS MovieCatalogue;
CREATE DATABASE IF NOT exists MovieCatalogue;
USE MovieCatalogue;

CREATE TABLE IF NOT exists Movie
(
MovieID INT AUTO_INCREMENT PRIMARY KEY,
GenreID INT NOT NULL,
DirectorID INT NULL,
RatingID INT NULL,
Title VARCHAR(128) NOT NULL,
ReleaseDate DATE NULL
);

CREATE TABLE IF NOT exists Genre
(
	GenreID INT AUTO_INCREMENT PRIMARY KEY,
    GenreName VARCHAR(30) NOT NULL
);

CREATE TABLE IF NOT exists Director
(
	DirectorID INT AUTO_INCREMENT Primary key,
	FirstName VARCHAR(30) NOT NULL,
	LastName VARCHAR(30) NOT NULL,
	BirthDate DATE NULL
);

CREATE TABLE IF NOT exists Rating
(
	RatingID INT AUTO_INCREMENT Primary key, 
	RatingName CHAR(5) NOT NULL
);

CREATE TABLE Actor
(
	ActorID INT AUTO_INCREMENT Primary key,
	FirstName VARCHAR(30) NOT NULL,
	LastName VARCHAR(30) NOT NULL,
	BirthDate DATE NULL
);

CREATE TABLE IF NOT exists CastMembers
(
	CastMemberID INT AUTO_INCREMENT Primary key,
	ActorID INT NOT NULL,
	MovieID INT NOT NULL,
	`Role` VARCHAR(50) NOT NULL
);

ALTER TABLE Movie
    ADD CONSTRAINT fk_Movie_Genre
        FOREIGN KEY (GenreID) 
        REFERENCES Genre(GenreID);
ALTER TABLE Movie
    ADD CONSTRAINT FK_Movie_Director
        FOREIGN KEY (DirectorID) 
        REFERENCES Director(DirectorID);
ALTER TABLE Movie
    ADD CONSTRAINT FK_Movie_Rating
        FOREIGN KEY (RatingID) 
        REFERENCES Rating(RatingID);
ALTER TABLE CastMembers
    ADD CONSTRAINT FK_CastMembers_Movie
        FOREIGN KEY (MovieID) 
        REFERENCES Movie(MovieID);
ALTER TABLE CastMembers
	ADD CONSTRAINT FK_CastMember_Actor
		FOREIGN KEY (ActorID)
        REFERENCES Actor(ActorID);

INSERT INTO Actor (FirstName, LastName, BirthDate) VALUES 
('Bill', 'Murray', '1950/9/21'),
('Dan', 'Aykroyd', '1952/7/1'),
('John', 'Candy', '1950/10/31'),
('Steve', 'Martin', NULL),
('Sylvester', 'Stallone', NULL);

INSERT INTO Director (FirstName, LastName, BirthDate) VALUES 
('Ivan', 'Reitman', '1946/10/27'),
('Ted', 'Kotcheff', NULL);

INSERT INTO Rating (RatingName) VALUES ('G'), ('PG'), ('PG-13'), ('R');

INSERT INTO Genre (GenreName) VALUES ('Action'), ('Comedy'), ('Drama'), ('Horror');

INSERT INTO Movie (DirectorID, RatingID, GenreID, Title, ReleaseDate) VALUES 
('2', '4', '1', 'Rambo: First Blood', '1982/10/22'),
(NULL, '4', '2', 'Planes, Trains & Automobiles', '1987/11/25'),
('1', '2', '2', 'Ghostbusters', NULL),
(NULL, '2', '2', 'The Great Outdoors', '1988/6/17');

INSERT INTO CastMembers (ActorID, MovieID, `Role`) VALUES 
	('5', '1', 'John Rambo'),
	('4', '2', 'Neil Page'),
	('3', '2', 'Del Griffith'),
	('1', '3', 'Dr. Peter Venkman'),
	('2', '3', 'Dr. Raymond Stanz'),
	('2', '4', 'Roman Craig'),
	('3', '4', 'Chet Ripley');


UPDATE Movie SET
	Title = 'Ghostbuster (1984)',
    ReleaseDate = '1994/3/4'
WHERE Title = 'Ghostbusters';
    
UPDATE Genre SET
	GenreName = 'Action/Adventure'
WHERE GenreName = 'Action';

DELETE FROM CastMembers WHERE MovieID = 1;
DELETE FROM Movie WHERE MovieID = 1;
    
		