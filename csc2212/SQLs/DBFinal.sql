-- phpMyAdmin SQL Dump
-- version 4.4.15.10
-- https://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 03, 2019 at 01:07 PM
-- Server version: 5.5.60-MariaDB
-- PHP Version: 5.4.16

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;


-- --------------------------------------------------------

--
-- Table structure for table `class`
--

CREATE TABLE IF NOT EXISTS `class` (
  `classCode` int NOT NULL,
  `courseCode` varchar(10) DEFAULT NULL,
  `classSection` char(1) DEFAULT NULL,
  `classTime` varchar(45) DEFAULT NULL,
  `classRoom` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `class`
--

INSERT INTO `class` (`classCode`, `courseCode`, `classSection`, `classTime`, `classRoom`) VALUES
(10012, 'ACCT-211', '1', 'MWF 8:00-8:50 a.m.', 'KLR 225'),
(10013, 'ACCT-211', '2', 'MWF 9:00-9:50 a.m.', 'KLR 225'),
(10014, 'ACCT-211', '3', 'TTh 2:30-3:45 p.m.', 'KLR 225'),
(10015, 'ACCT-212', '1', 'MWF 10:00-10:50 a.m.', 'KLR 240'),
(10016, 'ACCT-212', '2', 'Th 6:00-8:40 p.m.', 'KLR 240'),
(10017, 'ACCT-311', '1', 'TTh 3:30-4:45 p.m.', 'KLR 240'),
(12001, 'ART-210', '1', 'MWF 8:00-8:50 a.m.', 'BBG 120'),
(12002, 'ART-340', '1', 'MWF 10:00-10:50 a.m.', 'BBG 143'),
(15020, 'BIOL-120', '1', 'TTh 12:30-1:45 p.m.', 'AAK 166'),
(15021, 'BIOL-120', '2', 'Tue 6:00-8:40 p.m.', 'AAK 156'),
(15022, 'BIOL-120', '3', 'MWF 1:00-1:50 p.m.', 'AAK 156'),
(15030, 'BIOL-220', '1', 'MWF 2:00-2:50 p.m.', 'AAK 172'),
(20017, 'CIS-220', '1', 'MWF 9:00-9:50 a.m.', 'KLR 209'),
(20018, 'CIS-220', '2', 'MWF 9:00-9:50 a.m.', 'KLR 211'),
(20019, 'CIS-220', '3', 'MWF 10:00-10:50 a.m.', 'KLR 209'),
(20025, 'CIS-320', '1', 'MWF 10:00-10:50 a.m.', 'KLR 211'),
(20030, 'CIS-370', '1', 'MWF 11:00-11:50 a.m.', 'KLR 209'),
(20031, 'CIS-370', '2', 'Tue 6:00-8:40 p.m.', 'KLR 211'),
(20040, 'CIS-420', '1', 'Wed 6:00-8:40 p.m.', 'KLR 209'),
(22010, 'ECON-240', '1', 'MWF 8:00-8:50 a.m.', 'KLR 290'),
(22011, 'ECON-240', '2', 'TTh 3:30-4:45 p.m.', 'KLR 290'),
(22020, 'ECON-250', '1', 'Wed 6:00-8:40 p.m.', 'KLR 290'),
(23110, 'MGT-340', '1', 'TTh 8:00-9:15 a.m.', 'KLR 152'),
(23111, 'MGT-340', '2', 'Mon 6:00-8:40 p.m.', 'KLR 152'),
(23120, 'MKT-360', '1', 'MWF 10:00-10:50 a.m.', 'KLR 152'),
(23121, 'MKT-360', '2', 'Th 6:00-8:40 p.m.', 'KLR 152'),
(25000, 'ENG-210', '1', 'MWF 1:00-1:50 p.m.', 'DRE 257'),
(25001, 'ENG-210', '2', 'MWF 2:00-2:50 p.m.', 'DRE 257'),
(25002, 'ENG-210', '3', 'TTH 12:30-1:45 p.m.', 'DRE 257'),
(25010, 'SPCH-240', '1', 'MWF 8:00-8:50 a.m.', 'DRE 242'),
(25011, 'SPCH-240', '2', 'TTh 3:30-4:45 p.m.', 'DRE 242'),
(30010, 'PSYCH-200', '1', 'MWF 11:00-11:50 a.m.', 'AAK 244'),
(30110, 'SOC-200', '1', 'TTH 8:00-9:15 a.m.', 'BBG 258'),
(32000, 'HIST-210', '1', 'MWF 10:00-10:50 a.m.', 'DRE 144'),
(32001, 'HIST-210', '2', 'MWF 1:00-1:50 p.m.', 'DRE 144'),
(32002, 'HIST-210', '3', 'TTH 2:00-3:15 p.m.', 'DRE 144'),
(32011, 'HIST-220', '1', 'MWF 11:00-11:50 a.m.', 'DRE 144'),
(40010, 'MATH-120', '1', 'TTh 8:00-9:15 a.m.', 'AAK 200'),
(40011, 'MATH-120', '2', 'MWF 11:00-11:50 a.m.', 'AAK 200'),
(40101, 'MATH-243', '1', 'MWF 3:00-3:50 p.m.', 'AAK 202'),
(50021, 'QM-261', '1', 'MWF 8:00-8:50 a.m.', 'KLR 200'),
(50022, 'QM-261', '2', 'TTh 1:00-2:15 p.m.', 'KLR 200'),
(50023, 'QM-362', '1', 'MWF 11:00-11:50 a.m.', 'KLR 200'),
(50024, 'QM-362', '2', 'TTh 2:30-3:45 p.m.', 'KLR 200');

-- --------------------------------------------------------

--
-- Table structure for table `course`
--

CREATE TABLE IF NOT EXISTS `course` (
  `courseCode` varchar(10) NOT NULL,
  `courseDescription` varchar(50) DEFAULT NULL,
  `courseCredit` int DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `course`
--

INSERT INTO `course` (`courseCode`, `courseDescription`, `courseCredit`) VALUES
('ACCT-211', 'Accounting I', 3),
('ACCT-212', 'Accounting II', 3),
('ACCT-311', 'Managerial Accounting', 3),
('ART-210', 'Intro. to Art', 3),
('ART-340', 'Jewelry Design', 3),
('BIOL-120', 'Intro. to Biology', 4),
('BIOL-220', 'Biology and the Environment', 4),
('CIS-220', 'Intro. to Microcomputing', 3),
('CIS-320', 'Spreadsheet Applications', 3),
('CIS-370', 'Intro. to Systems Analysis', 3),
('CIS-420', 'Database Design and Implementation', 4),
('ECON-240', 'Microeconomics', 3),
('ECON-250', 'Macroeconomics', 3),
('ENG-210', 'Writing', 3),
('ENG-220', 'Literature', 3),
('FIN-300', 'Money and Banking', 3),
('HIST-210', 'U.S. History Through the 1800s', 3),
('HIST-220', 'U.S. History Through the 1900s', 3),
('MATH-120', 'College Algebra I', 3),
('MATH-240', 'Intro. to Calculus', 4),
('MATH-243', 'Mathematics for Managers', 3),
('MGT-340', 'Intro. to Management', 3),
('MKT-360', 'Intro. to Marketing', 3),
('PSYCH-200', 'Intro. to Psychology', 3),
('QM-261', 'Intro. to Statistics', 3),
('QM-362', 'Statistical Applications', 4),
('SOC-200', 'Intro. to Sociology', 3),
('SPCH-240', 'Public Speaking', 3);

-- --------------------------------------------------------

--
-- Table structure for table `enroll`
--

CREATE TABLE IF NOT EXISTS `enroll` (
  `classCode` int NOT NULL,
  `studentID` int NOT NULL,
  `enrollYear` year DEFAULT NULL,
  `enrollSemester` char(1) DEFAULT NULL,
  `enrollGrade` varchar(2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `enroll`
--

INSERT INTO `enroll` (`classCode`, `studentID`, `enrollYear`, `enrollSemester`, `enrollGrade`) VALUES
(10012, 311198, 2018, '1', 'A'),
(10012, 311357, 2018, '1', 'A'),
(10012, 322345, 2018, '1', 'A'),
(10012, 324274, 2018, '1', 'A'),
(10012, 343749, 2018, '1', 'C'),
(10013, 324258, 2018, '1', 'A'),
(10013, 325563, 2018, '1', 'A'),
(10014, 319989, 2018, '1', 'A'),
(10014, 321452, 2018, '1', 'A'),
(10014, 324257, 2018, '1', 'D'),
(10016, 320367, 2018, '1', 'A'),
(10016, 327689, 2018, '1', 'A'),
(10016, 342721, 2018, '1', 'A'),
(10016, 345758, 2018, '1', 'A'),
(10017, 324269, 2018, '1', 'A'),
(10017, 328934, 2018, '1', 'B'),
(10017, 328993, 2018, '1', 'B'),
(12001, 321452, 2018, '1', 'B'),
(12001, 342721, 2018, '1', 'A'),
(12001, 345783, 2018, '1', 'F'),
(12002, 320367, 2018, '1', 'A'),
(12002, 328934, 2018, '1', 'A'),
(15020, 345783, 2018, '2', NULL),
(15021, 320367, 2018, '2', NULL),
(15021, 321452, 2018, '2', NULL),
(15021, 324274, 2018, '2', NULL),
(15021, 330021, 2018, '2', NULL),
(15022, 322345, 2018, '2', NULL),
(15022, 327689, 2018, '2', NULL),
(20017, 342721, 2018, '1', 'A'),
(20017, 343749, 2018, '1', 'A'),
(20018, 311357, 2018, '1', 'F'),
(20018, 322345, 2018, '1', 'A'),
(20019, 321452, 2018, '1', 'D'),
(20019, 324258, 2018, '1', 'A'),
(20019, 325563, 2018, '1', 'B'),
(20025, 345758, 2018, '1', 'A'),
(20030, 311198, 2018, '1', 'A'),
(20030, 324257, 2018, '1', 'C'),
(20030, 328934, 2018, '1', 'C'),
(20030, 345758, 2018, '1', 'C'),
(20040, 324269, 2018, '2', NULL),
(20040, 328993, 2018, '2', NULL),
(22011, 327689, 2018, '1', 'A'),
(22011, 342721, 2018, '1', 'A'),
(22020, 321452, 2018, '1', 'A'),
(22020, 324274, 2018, '1', 'A'),
(22020, 343749, 2018, '1', 'D'),
(23110, 311198, 2018, '1', 'A'),
(23110, 311357, 2018, '1', 'A'),
(23110, 324257, 2018, '1', 'B'),
(23110, 345758, 2018, '1', 'A'),
(23111, 324269, 2018, '1', 'A'),
(23111, 328993, 2018, '1', 'A'),
(23120, 327689, 2018, '1', 'F'),
(23121, 311198, 2018, '1', 'A'),
(23121, 328934, 2018, '1', 'A'),
(23121, 328993, 2018, '1', 'B'),
(25000, 320367, 2018, '1', 'A'),
(25000, 345783, 2018, '1', 'A'),
(25001, 330021, 2018, '1', 'A'),
(25002, 311357, 2018, '1', 'A'),
(25002, 322345, 2018, '1', 'B'),
(25002, 324258, 2018, '1', 'A'),
(25002, 343749, 2018, '1', 'A'),
(25010, 325563, 2018, '1', 'A'),
(25011, 345783, 2018, '1', 'A'),
(30010, 320367, 2018, '1', 'A'),
(30010, 324258, 2018, '1', 'A'),
(30110, 322345, 2018, '1', 'A'),
(30110, 324274, 2018, '1', 'A'),
(30110, 330021, 2018, '1', 'A'),
(32000, 342721, 2018, '1', 'A'),
(32000, 345783, 2018, '1', 'A'),
(32001, 343749, 2018, '1', 'A'),
(32002, 325563, 2018, '1', 'A'),
(32002, 330021, 2018, '1', 'A'),
(40010, 324258, 2018, '1', 'A'),
(40010, 342721, 2018, '1', 'D'),
(40010, 345783, 2018, '1', 'A'),
(40011, 322345, 2018, '1', 'A'),
(40011, 325563, 2018, '1', 'A'),
(40011, 330021, 2018, '1', 'A'),
(40101, 311198, 2018, '1', 'A'),
(40101, 311357, 2018, '1', 'B'),
(40101, 324257, 2018, '1', 'B'),
(40101, 324269, 2018, '1', 'B'),
(40101, 324274, 2018, '1', 'A'),
(50021, 324258, 2018, '1', 'A'),
(50022, 311198, 2018, '1', 'A'),
(50022, 327689, 2018, '1', 'A'),
(50022, 342721, 2018, '1', 'A'),
(50022, 343749, 2018, '1', 'A'),
(50023, 324257, 2018, '2', NULL),
(50023, 324269, 2018, '2', NULL),
(50024, 311357, 2018, '2', NULL),
(50024, 324274, 2018, '2', NULL),
(50024, 328934, 2018, '2', NULL),
(50024, 345758, 2018, '2', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `student`
--

CREATE TABLE IF NOT EXISTS `student` (
  `studentid` int NOT NULL,
  `lastName` varchar(45) DEFAULT NULL,
  `firstName` varchar(45) DEFAULT NULL,
  `DOB` date DEFAULT NULL,
  `GPA` float DEFAULT NULL,
  `transfer` char(1) DEFAULT NULL,
  `major` varchar(25) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `student`
--

INSERT INTO `student` (`studentid`, `lastName`, `firstName`, `DOB`, `GPA`, `transfer`, `major`) VALUES
(300245, 'Peppard', 'Randy', '1975-06-21', 2.61, 'N', 'BIO'),
(311198, 'Robertson', 'Anne', '1970-11-15', 3.04, 'N', 'CS'),
(311357, 'Huizinga', 'Jan', '1973-04-04', 2.02, 'N', 'PHYS'),
(319989, 'Schloss', 'Heinz', '1960-02-25', 3.45, 'N', 'PHYS'),
(320367, 'Grafton', 'Suzanna', '1976-10-18', 2.81, 'N', 'HIST'),
(321452, 'Bowser', 'William', '1972-02-12', 1.55, 'N', 'BIO'),
(322345, 'Wesson', 'Sidney', '1956-12-14', 3.91, 'N', 'ACCT'),
(323119, 'Papar', 'George', '1970-04-04', 2.78, 'N', 'PHYS'),
(324257, 'Smithson', 'Anne', '1973-11-18', 2.02, 'Y', 'CS'),
(324258, 'Brewer', 'Juliette', '1966-08-23', 3.48, 'Y', 'ACCT'),
(324269, 'Oblonski', 'Walter', '1973-09-16', 2.17, 'N', 'CS'),
(324273, 'Smith', 'John', '1955-12-30', 2.72, 'Y', 'MATH'),
(324274, 'Katinga', 'Raphael', '1968-10-25', 2.91, 'N', 'ACCT'),
(324291, 'Robertson', 'Gerald', '1970-04-04', 2.45, 'N', 'BIO'),
(324299, 'Smith', 'John', '1975-11-30', 1.75, 'N', 'ACCT'),
(324567, 'Willow', 'Samuel', '1979-07-12', NULL, 'N', 'BIO'),
(325563, 'Warren', 'Marie', '1971-08-22', 2.42, 'N', 'ACCT'),
(326578, 'Weston', 'George', '1978-02-01', 2.09, 'N', 'MKT'),
(327689, 'Olenga', 'Leontine', '1976-10-15', 3.12, 'N', 'MKT'),
(328799, 'Smith', 'Robert', '1950-04-08', 3.51, 'N', 'BIO'),
(328934, 'Innugado', 'Carlos', '1976-11-30', 2.38, 'Y', 'CS'),
(328993, 'Jubilar', 'Anton', '1958-10-29', 2.95, 'N', 'ACCT'),
(330010, 'Schlumberg', 'Georgette', '1949-02-25', 3.21, 'N', 'CS'),
(330021, 'Browning', 'William', '1972-12-30', 1.53, 'N', 'HIST'),
(332345, 'Paulus', 'Annelise', '1974-01-05', 3.92, 'N', 'MATH'),
(341101, 'Richter', 'Ronald', '1960-11-30', NULL, 'N', 'ART'),
(341108, 'Smith', 'Darren', '1988-08-18', 2.45, 'Y', 'ENG'),
(342715, 'Alvarez', 'Marie', '1987-04-19', 2.98, 'N', 'ENG'),
(342721, 'Rutan', 'Robert', '1981-02-02', 3.01, 'N', 'ECON'),
(342722, 'Browning', 'Louise', '1984-10-12', 3.72, 'N', 'SOC'),
(342745, 'Ularen', 'Warren', '1975-09-23', 2.51, 'Y', 'PSYCH'),
(342748, 'Perdurax', 'George', '1970-05-27', 2.78, 'N', 'ACCT'),
(343749, 'Brewton', 'John', '1966-05-01', 1.65, 'N', 'CS'),
(345755, 'Washington', 'Jeanine', '1978-12-25', 2.87, 'Y', 'MKT'),
(345758, 'Johnson', 'Antoinette', '1975-06-16', 3.45, 'N', 'CS'),
(345767, 'Jones', 'Rupert', '1975-03-19', 3.33, 'Y', 'ENG'),
(345779, 'Hernando', 'Kenna', '1971-07-12', 3.88, 'N', 'HIST'),
(345783, 'Boisseaux', 'Siouxz', '1979-11-28', 3.02, 'N', 'ART');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `class`
--
ALTER TABLE `class`
  ADD PRIMARY KEY (`classCode`),
  ADD KEY `class_fk1` (`courseCode`);

--
-- Indexes for table `course`
--
ALTER TABLE `course`
  ADD PRIMARY KEY (`courseCode`);

--
-- Indexes for table `enroll`
--
ALTER TABLE `enroll`
  ADD PRIMARY KEY (`classCode`,`studentID`),
  ADD KEY `enroll_fk2` (`studentID`);

--
-- Indexes for table `student`
--
ALTER TABLE `student`
  ADD PRIMARY KEY (`studentid`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `class`
--
ALTER TABLE `class`
  ADD CONSTRAINT `class_fk1` FOREIGN KEY (`courseCode`) REFERENCES `course` (`courseCode`);

--
-- Constraints for table `enroll`
--
ALTER TABLE `enroll`
  ADD CONSTRAINT `enroll_fk1` FOREIGN KEY (`classCode`) REFERENCES `class` (`classCode`),
  ADD CONSTRAINT `enroll_fk2` FOREIGN KEY (`studentID`) REFERENCES `student` (`studentid`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
