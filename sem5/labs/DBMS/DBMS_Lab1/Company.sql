-- MySQL dump 10.13  Distrib 5.7.27, for Linux (x86_64)
--
-- Host: localhost    Database: Company
-- ------------------------------------------------------
-- Server version	5.7.27-0ubuntu0.18.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `DEPARTMENT`
--

DROP TABLE IF EXISTS `DEPARTMENT`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `DEPARTMENT` (
  `Dname` char(20) DEFAULT NULL,
  `Dnumber` int(11) NOT NULL,
  `Mgr_ssn` int(11) DEFAULT NULL,
  `Mgr_start_date` date DEFAULT NULL,
  PRIMARY KEY (`Dnumber`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `DEPARTMENT`
--

LOCK TABLES `DEPARTMENT` WRITE;
/*!40000 ALTER TABLE `DEPARTMENT` DISABLE KEYS */;
INSERT INTO `DEPARTMENT` VALUES ('Admin',4,987654321,'1995-01-01'),('Reasearch',5,333444,'1988-05-22'),('HQ',6,888666,'1981-01-01');
/*!40000 ALTER TABLE `DEPARTMENT` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `DEPENDENT`
--

DROP TABLE IF EXISTS `DEPENDENT`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `DEPENDENT` (
  `Essn` int(11) DEFAULT NULL,
  `Dependent_name` char(20) DEFAULT NULL,
  `Sex` char(1) DEFAULT NULL,
  `bdate` date DEFAULT NULL,
  `Relationship` char(20) DEFAULT NULL,
  KEY `Essn` (`Essn`),
  CONSTRAINT `DEPENDENT_ibfk_1` FOREIGN KEY (`Essn`) REFERENCES `EMPLOYEE` (`Ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `DEPENDENT`
--

LOCK TABLES `DEPENDENT` WRITE;
/*!40000 ALTER TABLE `DEPENDENT` DISABLE KEYS */;
INSERT INTO `DEPENDENT` VALUES (1234567,'Alice','F','1988-04-06','Daughter'),(6668844,'Theon','M','1983-05-06','Son'),(9765443,'Joy','F','1958-05-03','Spouse'),(33344455,'Abner','M','1988-01-04','Son'),(99988777,'Elizabeth','F','1988-12-30','Daughter'),(324776323,'Athena','F','1967-05-05','Spouse');
/*!40000 ALTER TABLE `DEPENDENT` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `DEPT_LOCATIONS`
--

DROP TABLE IF EXISTS `DEPT_LOCATIONS`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `DEPT_LOCATIONS` (
  `Dnumber` int(11) DEFAULT NULL,
  `DLOCATION` char(20) DEFAULT NULL,
  KEY `Dnumber` (`Dnumber`),
  CONSTRAINT `DEPT_LOCATIONS_ibfk_1` FOREIGN KEY (`Dnumber`) REFERENCES `DEPARTMENT` (`Dnumber`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `DEPT_LOCATIONS`
--

LOCK TABLES `DEPT_LOCATIONS` WRITE;
/*!40000 ALTER TABLE `DEPT_LOCATIONS` DISABLE KEYS */;
INSERT INTO `DEPT_LOCATIONS` VALUES (6,'Houston'),(4,'Stafford'),(5,'Boston'),(5,'Sugarland'),(5,'Houston');
/*!40000 ALTER TABLE `DEPT_LOCATIONS` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `EMPLOYEE`
--

DROP TABLE IF EXISTS `EMPLOYEE`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `EMPLOYEE` (
  `Fname` char(20) DEFAULT NULL,
  `Minit` char(1) DEFAULT NULL,
  `Lname` char(20) DEFAULT NULL,
  `Ssn` int(11) NOT NULL,
  `Bdate` date DEFAULT NULL,
  `Address` char(100) DEFAULT NULL,
  `Sex` char(1) DEFAULT NULL,
  `Salary` int(11) DEFAULT NULL,
  `Super_ssn` int(11) DEFAULT NULL,
  `Dno` int(11) DEFAULT NULL,
  PRIMARY KEY (`Ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `EMPLOYEE`
--

LOCK TABLES `EMPLOYEE` WRITE;
/*!40000 ALTER TABLE `EMPLOYEE` DISABLE KEYS */;
INSERT INTO `EMPLOYEE` VALUES ('John','B','Smith',1234567,'1965-03-08','731 Fondren, Houston','M',30000,3334455,5),('Ramesh','K','Narayan',6668844,'1962-02-07','221B Baker Street','M',38000,888866555,4),('Ankit','F','Raut',9765443,'1988-03-07','Park Avenue','M',45000,324634536,6),('Frank','T','Wong',33344455,'1955-04-08','638 Voss, Houston','M',40000,8886655,5),('Jenny','S','Wallace',99988777,'1968-04-08','3321 Castle, Spring','F',35000,7876755,4),('Anshul','F','Jain',324776323,'1985-05-12','3445 Doddanekkundi','M',25000,876348932,4);
/*!40000 ALTER TABLE `EMPLOYEE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PROJECT`
--

DROP TABLE IF EXISTS `PROJECT`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PROJECT` (
  `Pname` char(20) DEFAULT NULL,
  `Pnumber` int(11) NOT NULL,
  `Plocation` char(20) DEFAULT NULL,
  `Dnum` int(11) DEFAULT NULL,
  PRIMARY KEY (`Pnumber`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PROJECT`
--

LOCK TABLES `PROJECT` WRITE;
/*!40000 ALTER TABLE `PROJECT` DISABLE KEYS */;
INSERT INTO `PROJECT` VALUES ('ProductX',1,'Bellaire',5),('ProductY',2,'Sugarland',5),('ProductZ',3,'Houston',5),('Computerization',10,'Stafford',4),('Reorganisation',20,'Houston',1),('Newbenefits',30,'Stafford',4);
/*!40000 ALTER TABLE `PROJECT` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `WORKS_ON`
--

DROP TABLE IF EXISTS `WORKS_ON`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `WORKS_ON` (
  `Essn` int(11) DEFAULT NULL,
  `Pno` int(11) DEFAULT NULL,
  `Hours` double DEFAULT NULL,
  KEY `Essn` (`Essn`),
  KEY `Pno` (`Pno`),
  CONSTRAINT `WORKS_ON_ibfk_1` FOREIGN KEY (`Essn`) REFERENCES `EMPLOYEE` (`Ssn`),
  CONSTRAINT `WORKS_ON_ibfk_2` FOREIGN KEY (`Pno`) REFERENCES `PROJECT` (`Pnumber`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `WORKS_ON`
--

LOCK TABLES `WORKS_ON` WRITE;
/*!40000 ALTER TABLE `WORKS_ON` DISABLE KEYS */;
INSERT INTO `WORKS_ON` VALUES (1234567,10,32.5),(6668844,30,20),(9765443,20,17.5),(33344455,3,35),(99988777,1,10),(324776323,2,15);
/*!40000 ALTER TABLE `WORKS_ON` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-08-13 15:56:08
