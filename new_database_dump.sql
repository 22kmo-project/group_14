-- MySQL dump 10.13  Distrib 8.0.31, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: banksimul
-- ------------------------------------------------------
-- Server version	8.0.30

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `id_account` int NOT NULL AUTO_INCREMENT,
  `balance` float DEFAULT NULL,
  `id_customer` int DEFAULT NULL,
  `credit_limit` float DEFAULT NULL,
  PRIMARY KEY (`id_account`),
  UNIQUE KEY `id_account_UNIQUE` (`id_account`),
  KEY `fk_Account_Customer_idx` (`id_customer`),
  CONSTRAINT `customer_account` FOREIGN KEY (`id_customer`) REFERENCES `customer` (`id_customer`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=9001 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,999595,1,1000),(88,385,8,0),(200,50,2,0),(222,4000,1,1000),(300,0,3,0),(8000,182,9,1000),(8899,1570,8,1000),(9000,1910,9,0);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_card`
--

DROP TABLE IF EXISTS `account_card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_card` (
  `id_account` int NOT NULL,
  `id_card` int NOT NULL,
  PRIMARY KEY (`id_account`,`id_card`),
  KEY `fk_Account_has_Card_Card1_idx` (`id_card`),
  KEY `fk_Account_has_Card_Account1_idx` (`id_account`),
  CONSTRAINT `fk_Account_Card_Account` FOREIGN KEY (`id_account`) REFERENCES `account` (`id_account`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `fk_Account_Card_Card` FOREIGN KEY (`id_card`) REFERENCES `card` (`id_card`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_card`
--

LOCK TABLES `account_card` WRITE;
/*!40000 ALTER TABLE `account_card` DISABLE KEYS */;
INSERT INTO `account_card` VALUES (1,123456),(222,123456),(200,222222),(300,333333),(88,888888),(8899,888888),(8000,999999),(9000,999999);
/*!40000 ALTER TABLE `account_card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `id_card` int NOT NULL,
  `pin` varchar(255) DEFAULT NULL,
  `wrong_pin_counter` tinyint DEFAULT '0',
  `wrong_pin_time` datetime DEFAULT NULL,
  PRIMARY KEY (`id_card`),
  UNIQUE KEY `id_card_UNIQUE` (`id_card`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (1,'$2a$10$P8mNvK7Gsur11pRmaNTMluBEfTyQArxEx/yue24ga.ZTxkmvokFZq',1,NULL),(123456,'$2a$10$opiJG5NFIIPsA0NmmRj.auCywMR9SvIDD/mnmNlTurbdQYeeALGDu',1,'2022-12-10 21:42:21'),(222222,'$2a$10$an29LX4eWAQTCUio/RrxNOPBzKQY5UyBDO5rLSgN5M.HA7VYFhx/G',0,NULL),(333333,'$2a$10$D/CNW16hC56wk6HPacjLi.4n/MWZ2j4jKPhwnnpCyUnBX6KOXO9YG',0,NULL),(888888,'$2a$10$cDKnilAasSUAYObl3O3oWuwR6fMb87vZdS64ozKAm4CUvze87XdV.',1,NULL),(999999,'$2a$10$v0nRMJmvtM8NUmzPgcMuAOYG9LVxnWmsavcZFgjJUsg9SseY9fh7K',0,NULL),(1234567,'$2a$10$s/3pqMb6bj0pN66gkYXtE.k9fCiJu1B.LKbVRzX4mWQx5FNtXpjrW',1,NULL),(7654321,'$2a$10$tAz7LuIJ/KN4fc9/ARFv6.MW6NPpE884P8zMJz8fMALpYcUDBX4KS',0,NULL);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer` (
  `id_customer` int NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  `address` varchar(45) DEFAULT NULL,
  `phone_number` varchar(15) DEFAULT NULL,
  PRIMARY KEY (`id_customer`),
  UNIQUE KEY `id_customer_UNIQUE` (`id_customer`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (1,'Teppo Testi','Huhhuhkatu 123','123456789'),(2,'Stiina Stäkki','Ceekatu 10 C 1','0402354824'),(3,'Hilma Hiippi','Heappitie 1 A 4','0409876543'),(8,'Deanna Devaaja','Binäärikuja 101','0401010110'),(9,'Konsta Koodaaja','Koodikatu 14','123456789');
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transactions`
--

DROP TABLE IF EXISTS `transactions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transactions` (
  `id_transaction` int NOT NULL AUTO_INCREMENT,
  `id_account` int DEFAULT NULL,
  `id_card` int DEFAULT NULL,
  `date` datetime DEFAULT NULL,
  `event` varchar(45) DEFAULT NULL,
  `amount` float DEFAULT NULL,
  PRIMARY KEY (`id_transaction`),
  KEY `fk_Transactions_Account_idx` (`id_account`),
  CONSTRAINT `account_transactions` FOREIGN KEY (`id_account`) REFERENCES `account` (`id_account`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=50 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transactions`
--

LOCK TABLES `transactions` WRITE;
/*!40000 ALTER TABLE `transactions` DISABLE KEYS */;
INSERT INTO `transactions` VALUES (1,8000,NULL,'2022-12-09 13:23:08','Nosto',20),(2,8000,NULL,'2022-12-09 13:23:16','Nosto',60),(3,8000,NULL,'2022-12-09 13:23:20','Nosto',20),(4,8000,NULL,'2022-12-09 13:23:23','Nosto',50),(5,8000,NULL,'2022-12-09 13:23:26','Talletus',50),(6,8000,NULL,'2022-12-09 13:23:30','Lahjoitus',5),(7,8000,NULL,'2022-12-09 13:23:47','Nosto',120),(8,8000,NULL,'2022-12-10 13:23:50','Nosto',50),(9,8000,NULL,'2022-12-10 13:23:53','Nosto',100),(10,8000,NULL,'2022-12-10 13:24:04','Lahjoitus',13),(11,8000,NULL,'2022-12-10 13:24:12','Nosto',20),(12,8000,NULL,'2022-12-10 13:24:14','Nosto',40),(13,8000,NULL,'2022-12-10 13:24:18','Talletus',40),(14,8000,NULL,'2022-12-10 13:24:24','Lahjoitus',10),(15,8000,NULL,'2022-12-11 13:24:28','Nosto',40),(16,8000,NULL,'2022-12-11 13:24:33','Nosto',50),(17,8000,NULL,'2022-12-11 13:24:38','Nosto',20),(18,8000,NULL,'2022-12-12 13:24:40','Nosto',40),(19,8000,NULL,'2022-12-12 13:24:42','Nosto',20),(20,8000,NULL,'2022-12-12 13:24:46','Nosto',100),(21,8000,NULL,'2022-12-12 13:25:12','Nosto',20),(22,9000,NULL,'2022-12-10 13:25:37','Nosto',20),(23,9000,NULL,'2022-12-12 13:25:40','Nosto',40),(24,9000,NULL,'2022-12-12 13:25:51','Talletus',40),(25,9000,NULL,'2022-12-12 13:26:01','Lahjoitus',5),(26,9000,NULL,'2022-12-12 13:26:06','Nosto',20),(27,8899,NULL,'2022-12-08 13:26:41','Lahjoitus',2),(28,8899,NULL,'2022-12-10 13:26:49','Nosto',20),(29,8899,NULL,'2022-12-11 13:27:00','Nosto',100),(30,88,NULL,'2022-12-01 13:28:04','Nosto',100),(31,88,NULL,'2022-12-01 13:28:09','Lahjoitus',20),(32,88,NULL,'2022-12-01 13:28:18','Nosto',250),(33,88,NULL,'2022-12-03 13:28:25','Nosto',20),(34,88,NULL,'2022-12-04 13:28:31','Nosto',60),(35,88,NULL,'2022-12-06 13:28:37','Nosto',20),(36,88,NULL,'2022-12-07 13:28:41','Talletus',20),(37,88,NULL,'2022-12-08 13:28:46','Lahjoitus',5),(38,88,NULL,'2022-12-08 13:28:49','Nosto',50),(39,88,NULL,'2022-12-10 13:28:53','Nosto',20),(40,88,NULL,'2022-12-11 13:29:01','Nosto',100),(41,200,NULL,'2022-12-04 13:29:47','Nosto',20),(42,200,NULL,'2022-12-06 13:29:54','Nosto',50),(43,200,NULL,'2022-12-07 13:29:56','Nosto',40),(44,200,NULL,'2022-12-09 13:30:04','Nosto',100),(45,200,NULL,'2022-12-10 13:30:07','Talletus',100),(46,200,NULL,'2022-12-10 13:30:32','Nosto',20),(47,200,NULL,'2022-12-11 13:30:35','Lahjoitus',5),(48,200,NULL,'2022-12-12 13:30:46','Nosto',20),(49,200,NULL,'2022-12-12 13:31:01','Lahjoitus',5);
/*!40000 ALTER TABLE `transactions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'banksimul'
--
/*!50003 DROP PROCEDURE IF EXISTS `cash_withdraw` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `cash_withdraw`(IN id INT, IN amount DOUBLE)
BEGIN
  DECLARE t, c_limit INT DEFAULT 0;
  START TRANSACTION;
  SET c_limit = (SELECT credit_limit FROM account WHERE id_account = id);
  
  IF (c_limit > 0) THEN ## Käytössä on credit tili
	UPDATE account SET balance = balance-amount WHERE id_account=id AND balance-amount >= -(c_limit);
  ELSE					## Käytössä debit tili
	UPDATE account SET balance = balance-amount WHERE id_account=id AND balance-amount >= 0;
  END IF;
  
  SET t = ROW_COUNT();
    IF (t > 0) THEN
      COMMIT;
      INSERT INTO transactions(id_account, event, amount, date) VALUES(id, 'Nosto', amount, NOW());
      SELECT (SELECT balance FROM account WHERE id_account = id) AS balance, (SELECT credit_limit FROM account WHERE id_account = id) AS credit_limit, (true) AS success;
    ELSE
      ROLLBACK;
      SELECT (SELECT balance FROM account WHERE id_account = id) AS balance, (SELECT credit_limit FROM account WHERE id_account = id) AS credit_limit, (false) AS success;
  END IF;
  END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `check_card_status` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `check_card_status`(IN id INT)
BEGIN
  DECLARE t, attempts INT DEFAULT 0;
  SET t = (SELECT ABS((SELECT wrong_pin_time FROM card WHERE id_card=id) - NOW())); # Viimeisimmän väärän loginyrityksen aikaleima
  SET attempts = (SELECT wrong_pin_counter FROM card WHERE id_card=id); ## Väärät login yritykset
  
  IF (attempts < 3 AND t > 60) THEN ## t = aika joka odotetaan viimeisimmästä väärästä kirjautumisyrityksestä, jos yritetty max 2 väärää PIN-koodia ja X sekuntia mennyt, 
    UPDATE card SET wrong_pin_counter = 0, wrong_pin_time = null WHERE id_card = id; # voidaan nollata vääriä loginyrityksiä laskeva counter sekä aikaleima seuraavalla kirjautumisyrityksellä.
	SELECT (false) AS is_locked;
  ELSE
    IF (attempts >= 3) THEN
      SELECT (true) AS is_locked; # Palautetaan että kortti on lukittu, eli 3 väärää loginyritystä tapahtunut
	ELSE
      SELECT (false) AS is_locked;
	END IF;
  END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `deposit` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `deposit`(IN id INT, IN amount DOUBLE)
BEGIN
  DECLARE t INT DEFAULT 0;
  START TRANSACTION;
  UPDATE account SET balance = balance+amount WHERE id_account=id;
  SET t = ROW_COUNT();
    IF (t > 0) THEN
      COMMIT;
      INSERT INTO transactions(id_account, event, amount, date) VALUES(id, 'Talletus', amount, NOW());
    ELSE
      ROLLBACK;
  END IF;
  END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `donation` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `donation`(IN id INT, IN amount DOUBLE)
BEGIN
DECLARE t, c_limit INT DEFAULT 0;
  START TRANSACTION;
  SET c_limit = (SELECT credit_limit FROM account WHERE id_account = id);
  UPDATE account SET balance = balance-amount WHERE id_account=id AND balance+c_limit-amount >= 0;
  SET t = ROW_COUNT();
    IF (t > 0) THEN
      COMMIT;
      INSERT INTO transactions(id_account, event, amount, date) VALUES(id, 'Lahjoitus', amount, NOW());
    ELSE
      ROLLBACK;
  END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-12-11 13:33:22
