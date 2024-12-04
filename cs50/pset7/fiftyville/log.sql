-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get a list of tables and the schemas
.schema

-- Get crime scene report
SELECT * FROM crime_scene_reports
WHERE year = 2023
AND month = 07
AND day = 28
AND street = "Humphrey Street";

-- id|year|month|day|street|description
-- 295|2023|7|28|Humphrey Street|Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

SELECT * FROM interviews
WHERE year = 2023
AND month = 07
AND day = 28
AND transcript LIKE "%bakery%";

-- 161|Ruth|2023|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162|Eugene|2023|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- 163|Raymond|2023|7|28|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT * FROM bakery_security_logs
WHERE year = 2023
AND month = 07
AND day = 28
AND hour = 10
AND minute > 15 
AND minute < 26;

-- id|year|month|day|hour|minute|activity|license_plate
-- 260|2023|7|28|10|16|exit|5P2BI95
-- 261|2023|7|28|10|18|exit|94KL13X **
-- 262|2023|7|28|10|18|exit|6P58WS2
-- 263|2023|7|28|10|19|exit|4328GD8 **
-- 264|2023|7|28|10|20|exit|G412CB7
-- 265|2023|7|28|10|21|exit|L93JTIZ **
-- 266|2023|7|28|10|23|exit|322W7JE
-- 267|2023|7|28|10|23|exit|0NTHK55

SELECT * 
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE atm_transactions.year = 2023
AND atm_transactions.month = 07
AND atm_transactions.day = 28
AND atm_transactions.atm_location = "Leggett Street";

-- id|account_number|year|month|day|atm_location|transaction_type|amount|account_number|person_id|creation_year|id|name|phone_number|passport_number|license_plate
-- 267|49610011|2023|7|28|Leggett Street|withdraw|50|49610011|686048|2010|686048|Bruce|(367) 555-5533|5773159633|94KL13X ***
-- 275|86363979|2023|7|28|Leggett Street|deposit|10|86363979|948985|2010|948985|Kaelyn|(098) 555-1164|8304650265|I449449
-- 336|26013199|2023|7|28|Leggett Street|withdraw|35|26013199|514354|2012|514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 269|16153065|2023|7|28|Leggett Street|withdraw|80|16153065|458378|2012|458378|Brooke|(122) 555-4581|4408372428|QX4YZN3
-- 264|28296815|2023|7|28|Leggett Street|withdraw|20|28296815|395717|2014|395717|Kenny|(826) 555-1652|9878712108|30G67EN
-- 288|25506511|2023|7|28|Leggett Street|withdraw|20|25506511|396669|2014|396669|Iman|(829) 555-5269|7049073643|L93JTIZ **
-- 246|28500762|2023|7|28|Leggett Street|withdraw|48|28500762|467400|2014|467400|Luca|(389) 555-5198|8496433585|4328GD8 **
-- 266|76054385|2023|7|28|Leggett Street|withdraw|60|76054385|449774|2015|449774|Taylor|(286) 555-6063|1988161715|1106N58
-- 313|81061156|2023|7|28|Leggett Street|withdraw|30|81061156|438727|2018|438727|Benista|(338) 555-6650|9586786673|8X428L0

SELECT * 
FROM phone_calls
WHERE year = 2023
AND month = 07
AND day = 28
AND (caller = "(367) 555-5533" OR caller = "(829) 555-5269" OR caller = "(389) 555-5198");

-- 233|(367) 555-5533|(375) 555-8161|2023|7|28|45 **
-- 236|(367) 555-5533|(344) 555-9601|2023|7|28|120
-- 245|(367) 555-5533|(022) 555-4052|2023|7|28|241
-- 285|(367) 555-5533|(704) 555-5790|2023|7|28|75


SELECT *
FROM people
WHERE (phone_number = "(375) 555-8161" OR phone_number = "(344) 555-9601" OR phone_number = "(022) 555-4052" OR phone_number = "(704) 555-5790");

-- id|name|phone_number|passport_number|license_plate
-- 315221|Gregory|(022) 555-4052|3355598951|V4C670D
-- 652398|Carl|(704) 555-5790|7771405611|81MZ921
-- 864400|Robin|(375) 555-8161||4V16VO0 **
-- 985497|Deborah|(344) 555-9601|8714200946|10I5658

SELECT *
FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
AND flights.year = 2023
AND flights.month = 07
AND flights.day = 29;

-- id|origin_airport_id|destination_airport_id|year|month|day|hour|minute
-- 18|8|6|2023|7|29|16|0
-- 23|8|11|2023|7|29|12|15
-- 36|8|4|2023|7|29|8|20 **
-- 43|8|1|2023|7|29|9|30
-- 53|8|9|2023|7|29|15|20

SELECT * FROM airports WHERE id = 4;

-- id|abbreviation|full_name|city
-- 4|LGA|LaGuardia Airport|New York City

SELECT * 
FROM passengers
WHERE flight_id = 36;

-- 36|7214083635|2A
-- 36|1695452385|3B
-- 36|5773159633|4A  **
-- 36|1540955065|5C
-- 36|8294398571|6C
-- 36|1988161715|6D
-- 36|9878712108|7A
-- 36|8496433585|7B