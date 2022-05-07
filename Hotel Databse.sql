DROP DATABASE IF EXISTS HotelCatalogue;
CREATE DATABASE IF NOT exists HotelCatalogue;
USE HotelCatalogue;

CREATE TABLE IF NOT exists Room
(
RoomID INT PRIMARY KEY not null,
RoomType varchar(10),
AmenityName varchar(100),
ADA char(5) NULL,
Jacuzzie char(5) NULL,
StandardOcc DECIMAL(1),
MaxOcc DECIMAL(1),
BasePrice DECIMAL(8,2)
);

CREATE TABLE if not exists Price
(
	PriceID varchar(10) Primary key not null,
	AddAdult DECIMAL(2) NULL,
    AddChild DECIMAL(2) NULL,
    JacuzziePrice DECIMAL(2) NULL
);

CREATE TABLE IF NOT exists RoomGuest
(
	RoomID INT not null,
	GuestID INT not null
);

CREATE TABLE IF NOT exists RoomPrice
(
	RoomID INT not null,
	PriceID varchar(10) not null
);

CREATE TABLE if not exists Guest
(
	GuestID INT auto_increment Primary key not null,
	`Name` varchar(100),
	Address varchar(100),
	City varchar(20),
    State char(20),
    ZIPCode char(5),
    Phone char(15)
);

CREATE TABLE if not exists Reservation
(
	ReservationID int auto_increment primary key not null,
    RoomID INT not null,
    GuestID INT not null,
    `Name` varchar(100),
	Adults INT,
	Child INT,
	StartDate DATE,
    EndDate DATE,
    NumberDays DECIMAL(3),
    PriceID varchar(10) not null,
    TotalPrice DECIMAL(8,2)
);
 

ALTER TABLE RoomGuest
 ADD CONSTRAINT fk_RoomGuest_Room FOREIGN KEY (RoomID) REFERENCES Room
(RoomID);
ALTER TABLE RoomGuest
 ADD CONSTRAINT fk_RoomGuest_Guest FOREIGN KEY (GuestID) REFERENCES Guest
(GuestID);
ALTER TABLE RoomPrice
 ADD CONSTRAINT fk_RoomPrice_Room FOREIGN KEY (RoomID) REFERENCES Room
(RoomID);
ALTER TABLE RoomPrice
 ADD CONSTRAINT fk_RoomPrice_Price FOREIGN KEY (PriceID) REFERENCES Price
(PriceID);
ALTER TABLE Reservation
 ADD CONSTRAINT fk_Reservation_Room FOREIGN KEY (RoomID) REFERENCES Room
(RoomID);
ALTER TABLE Reservation
 ADD CONSTRAINT fk_Reservation_Price FOREIGN KEY (PriceID) REFERENCES Price
(PriceID);

delimiter //
create trigger before_insert_Guest
	before insert on Guest
	for each row
    begin
		if new.GuestID is null then
			SET new.GuestID = NEWID(6);
		end if;
	end;//
delimiter ;

delimiter //
create trigger before_insert_Reservation
	before insert on Reservation
	for each row
    begin
		if new.ReservationID is null then
			SET new.ReservationID = NEWID(8);
		end if;
	end;//
delimiter ;


INSERT INTO Room (RoomID, RoomType, AmenityName, ADA, Jacuzzie, StandardOcc, MaxOcc, BasePrice)
VALUES (201, 'Double', 'Microwave', 'No', 'Yes', 2, 4, '199.99'),
(202, 'Double', 'Refrigerator',	'Yes', 'No', 2, 4, '174.99'),
(203, 'Double',	'Microwave', 'No', 'Yes', 2, 4, '199.99'),
(204, 'Double', 'Refrigerator', 'Yes', 'No', 2, 4, '174.99'),
(205, 'Single', 'Microwave, Refrigerator',	'No', 'Yes', 2, 2, '174.99'),
(206, 'Single', 'Microwave, Refrigerator', 'Yes', 'No',	2, 2, '149.99'),
(207, 'Single', 'Microwave, Refrigerator', 'No', 'Yes', 2, 2, '174.99'),
(208, 'Single', 'Microwave, Refrigerator', 'Yes', 'No', 2, 2, '149.99'),
(301, 'Double',	'Microwave', 'No', 'Yes', 2, 4, '199.99'),
(302, 'Double',	'Refrigerator',	'Yes', 'No', 2, 4, '174.99'),
(303, 'Double',	'Microwave', 'No', 'Yes', 2, 4, '199.99'),
(304, 'Double',	'Refrigerator',	'Yes', 'No', 2, 4, '174.99'),
(305, 'Single',	'Microwave, Refrigerator', 'No', 'Yes',	2, 2, '174.99'),
(306, 'Single',	'Microwave, Refrigerator',	'Yes', 'No', 2, 2, '149.99'),
(307, 'Single',	'Microwave, Refrigerator', 	'No', 'Yes', 2, 2, '174.99'),
(308, 'Single',	'Microwave, Refrigerator', 'Yes', 'No', 2, 2, '149.99'),
(401, 'Suite', 'Microwave, Refrigerator, Oven', 'Yes', 'No', 3, 8, '399.99'),
(402, 'Suite', 'Microwave, Refrigerator, Oven',	'Yes', 'No', 3, 8, '399.99');

INSERT INTO Guest (`Name`, Address, City, State, ZIPCode, Phone)
VALUES ('Your Name', 'Your Address', 'City', 'State', 'ZIP', 'Phone'),
('Mack Simmer', '379 Old Shore Street', 'Council Bluffs', 'IA', '51501', '(291) 553-0508'),
('Bettyann Seery', '750 Wintergreen Dr.', 'Wasilla', 'AK', '99654', '(478) 277-9632'),
('Duane Cullison', '9662 Foxrun Lane', 'Harlingen','TX', '78552', '(308) 494-0198'),
('Karie Yang', '9378 W. Augusta Ave.', 'West Deptford', 'NJ', '08096', '(214) 730-0298'),
('Aurore Lipton', '762 Wild Rose Street', 'Saginaw', 'MI', '48601', '(377) 507-0974'),
('Zachery Luechtefeld', '7 Poplar Dr.', 'Arvada', 'CO', '80003', '(814) 485-2615'),
('Jeremiah Pendergrass', '70 Oakwood St.', 'Zion', 'IL', '60099', '(279) 491-0960'),
('Walter Holaway', '7556 Arrowhead St.','Cumberland', 'RI', '02864', '(446) 396-6785'),
('Wilfred Vise', '77 West Surrey Street', 'Oswego', 'NY', '13126', '(834) 727-1001'),
('Maritza Tilton', '939 Linda Rd.',  'Burke', 'VA', '22015', '(446) 351-6860'),
('Joleen Tison', '87 Queen St.', 'Drexel Hill', 'PA', '19026', '(231) 893-2755');

INSERT INTO Price (PriceID, AddAdult, AddChild, JacuzziePrice)
VALUES ('DBL201', '10', 0, '25'),
('DBL202', '10', 0, NULL),
('DBL203', '10', 0, '25'),
('DBL204', '10', 0, NULL),
('SNG205', NULL, 0, '25'),
('SNG206', NULL, 0, NULL),
('SNG207', NULL, 0, '25'),
('SNG208', NULL, 0, NULL),
('DBL301', '10', 0, '25'),
('DBL302', '10', 0, NULL),
('DBL303', '10', 0, '25'),
('DBL304', '10', 0, NULL),
('SNG305', NULL, 0, '25'),
('SNG306', NULL, 0, NULL),
('SNG307', NULL, 0, '25'),
('SNG308', NULL, 0, NULL),
('SUT401', '20', 0, NULL),
('SUT402', '20', 0, NULL);

INSERT INTO RoomPrice (RoomID, PriceID)
VALUES (201, 'DBL201'),
(202, 'DBL202'),
(203, 'DBL203'),
(204, 'DBL204'),
(205, 'SNG205'),
(206, 'SNG206'),
(207, 'SNG207'),
(208, 'SNG208'),
(301, 'DBL301'),
(302, 'DBL302'),
(303, 'DBL303'),
(304, 'DBL304'),
(305, 'SNG305'),
(306, 'SNG306'),
(307, 'SNG307'),
(308, 'SNG308'),
(401, 'SUT401'),
(402, 'SUT402');


INSERT INTO Reservation (RoomID, GuestID, `Name`, Adults, Child, StartDate, EndDate, NumberDays, PriceID, TotalPrice)
VALUES ('308', 2, 'Mack Simmer', 1, 0, '2023/2/2', '2023/2/4', 2, 'SNG308', '299.98'),
(203, 3,  'Bettyann Seery', 2, 1, '2023/2/5', '2023/2/10', 5, 'DBL203', '999.95'),
(305, 4, 'Duane Cullison', 2, 0, '2023/2/22', '2023/2/24', 2, 'SNG305', '349.98'),
(201, 5, 'Karie Yang', 2, 2, '2023/3/6', '2023/3/7', 1, 'DBL201', '199.99'),
(307, 1, 'Your Name', 1, 1, '2023/3/17', '2023/3/20', 3, 'SNG307', '524.97'),
(302, 6, 'Aurore Lipton', 3, 0, '2023/3/18', '2023/3/23', 5, 'DBL302', '924.95'),
(202, 7, 'Zachery Luechtefeld', 2, 2, '2023/3/29', '2023/3/31', 2, 'DBL202', '349.98'),
(304, 8, 'Jeremiah Pendergrass', 2, 0, '2023/3/31', '2023/4/5', 6, 'DBL304', '874.95'),
(301, 9, 'Walter Holaway',	1, 0, '2023/4/9', '2023/4/13', 4, 'DBL301',	'799.96'),
(207, 10, 'Wilfred Vise', 1, 1, '2023/4/23', '2023/4/24', 1, 'SNG207', '174.99'),
(401, 11, 'Maritza Tilton', 2, 4, '2023/5/30', '2023/6/2', 4, 'SUT401', '1199.97'),
(206, 12, 'Joleen Tison', 2, 0, '2023/6/10', '2023/6/14', 4, 'SNG206', '599.96'),
(208, 12, 'Joleen Tison', 1, 0, '2023/6/10', '2023/6/14', 4, 'SNG208', '599.96'),
(304, 6, 'Aurore Lipton', 3, 0, '2023/6/17', '2023/6/18', 1, 'DBL304',	'184.99'),
(205, 1, 'Your Name', 2, 0, '2023/6/28', '2023/7/2', 5, 'SNG205', '699.96'),
(204, 9, 'Walter Holaway', 3, 1, '2023/7/13', '2023/7/14', 1, 'DBL204', '184.99'),
(401, 10, 'Wilfred Vise', 4, 2, '2023/7/18', '2023/7/21', 3, 'SUT401', '1259.97'),
(303, 3, 'Bettyann Seery',	2, 1, '2023/7/28', '2023/7/29', 1, 'DBL303', '199.99'),
(305, 3, 'Bettyann Seery', 1, 0, '2023/8/30', '2023/9/1', 3, 'SNG305', '349.98'),
(208, 2, 'Mack Simmer', 2, 0, '2023/9/16', '2023/9/17', 1, 'SNG208', '149.99'),
(203, 5, 'Karie Yang',	2, 2, '2023/9/13', '2023/9/15', 2, 'DBL203', '399.98'),
(401, 4, 'Duane Cullison', 2, 2, '2023/11/22', '2023/11/25', 3, 'SUT401', '1199.97'),
(206, 2, 'Mack Simmer', 2, 0, '2023/11/22', '2023/11/25', 3, 'SNG206',	'449.97'),
(301, 2, 'Mack Simmer', 2, 2, '2023/11/22', '2023/11/25', 3, 'DBL301', '599.97'),
(302, 11, 'Maritza Tilton',	2, 0, '2023/12/24', '2023/12/28', 4, 'DBL302', '699.96');

INSERT INTO RoomGuest (RoomID, GuestID)
VALUES ('308', 2),
(203, 3),
(305, 4),
(201, 5),
(307, 1),
(302, 6),
(202, 7),
(304, 8),
(301, 9),
(207, 10),
(401, 11),
(206, 12),
(208, 12),
(304, 6),
(205, 1),
(204, 9),
(401, 10),
(303, 3),
(305, 3),
(208, 2),
(203, 5),
(401, 4),
(206, 2),
(301, 2),
(302, 11);
