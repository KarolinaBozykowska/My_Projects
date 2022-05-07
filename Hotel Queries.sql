use HotelCatalogue;

-- Write a query that returns a list of reservations that end in July 2023, including the name of the guest, the room number(s), and the reservation dates.

SELECT `Name`, RoomID, StartDate, EndDate
FROM Reservation
WHERE EndDate < '2023-07-31'

-- Write a query that returns a list of all reservations for rooms with a jacuzzi, displaying the guest's name, the room number, and the dates of the reservation.

SELECT
	re.`Name`,
    re.StartDate,
    re.EndDate,
    rm.RoomID
FROM Room rm
LEFT OUTER JOIN Reservation re ON rm.RoomID = re.RoomID
WHERE rm.Jacuzzie = 'Yes';

-- Write a query that returns all the rooms reserved for a specific guest, including the guest's name, the room(s) reserved, the starting date of the reservation, and how many people were included in the reservation. (Choose a guest's name from the existing data.)

SELECT
	g.`Name`,
    re.StartDate,
    re.Adults,
    re.Child,
    re.RoomID
FROM Guest g
INNER JOIN Reservation re ON g.GuestID = re.GuestID
WHERE g.`Name` = 'Karie Yang';

-- Write a query that returns a list of rooms, reservation ID, and per-room cost for each reservation. The results should include all rooms, whether or not there is a reservation associated with the room.

SELECT
	rm.RoomID,
    re.TotalPrice,
    re.ReservationID
FROM Room rm
LEFT OUTER JOIN Reservation re ON rm.RoomID = re.RoomID

-- Write a query that returns all the rooms accommodating at least three guests and that are reserved on any date in April 2023.

SELECT RoomID, StartDate, EndDate, Adults + Child AS TotalGuest
FROM Reservation
WHERE (Adults + Child >= 3 AND EndDate BETWEEN '2023-07-01' AND '2023-07-31');

-- Write a query that returns a list of all guest names and the number of reservations per guest, sorted starting with the guest with the most reservations and then by the guest's last name.

SELECT 
g.GuestID,
g.`Name`,
count(*) AS TotalReservations
FROM Reservation re
RIGHT OUTER JOIN Guest g ON g.GuestID = re.GuestID
GROUP BY re.`Name`;

-- Write a query that displays the name, address, and phone number of a guest based on their phone number. (Choose a phone number from the existing data.)

SELECT `Name`, Address, Phone
FROM Guest
WHERE Phone = '(214) 730-0298'