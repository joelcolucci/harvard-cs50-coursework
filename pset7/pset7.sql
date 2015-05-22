-- MySQL dump 10.14  Distrib 5.5.32-MariaDB, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32-MariaDB

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
-- Table structure for table `portfolio`
--

DROP TABLE IF EXISTS `portfolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolio` (
  `id` int(10) unsigned NOT NULL,
  `symbol` varchar(5) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolio`
--

LOCK TABLES `portfolio` WRITE;
/*!40000 ALTER TABLE `portfolio` DISABLE KEYS */;
INSERT INTO `portfolio` VALUES (6,'GOOG',5100),(26,'AMZN',5),(26,'FB',50),(26,'GOOG',5),(26,'RAX',10),(26,'TGT',10),(26,'TWTR',50),(27,'GOOG',10);
/*!40000 ALTER TABLE `portfolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transactions`
--

DROP TABLE IF EXISTS `transactions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `transactions` (
  `transaction_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `type` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `symbol` varchar(11) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(11) NOT NULL,
  `price` decimal(64,4) NOT NULL,
  PRIMARY KEY (`transaction_id`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transactions`
--

LOCK TABLES `transactions` WRITE;
/*!40000 ALTER TABLE `transactions` DISABLE KEYS */;
INSERT INTO `transactions` VALUES (1,6,'Buy','2014-04-24 12:12:56','GOOG',10,526.9400),(2,6,'Buy','2014-04-24 12:13:05','GOOG',10,526.9400),(4,6,'Buy','2014-04-24 12:50:11','SSNC',10,38.0000),(5,6,'Buy','2014-04-24 12:50:43','FB',500,61.3600),(6,6,'Sell','2014-04-24 13:12:00','FB',500,30680.0000),(7,6,'Deposit','2014-04-25 12:37:18','-',0,431787.4000),(8,6,'Deposit','2014-04-25 12:37:39','-',0,868569.8000),(9,6,'Deposit','2014-04-25 12:38:10','-',0,1737139.6000),(10,6,'Buy','2014-04-25 12:39:18','GOOG',5000,525.1600),(11,6,'Buy','2014-04-25 12:39:51','GOOG',1000,525.1600),(12,6,'Buy','2014-04-25 12:40:11','GOOG',500,525.1600),(13,6,'Buy','2014-04-25 12:40:25','GOOG',100,525.1600),(14,6,'Buy','2014-04-25 12:40:33','GOOG',6,525.1600),(15,6,'Buy','2014-04-25 12:40:52','SSNC',1,37.8500),(16,6,'Deposit','2014-04-25 12:41:17','-',0,84.3900),(17,6,'Deposit','2014-04-25 12:43:30','-',0,50.0000),(18,6,'Deposit','2014-04-25 12:43:41','-',0,50.0000),(19,6,'Deposit','2014-04-25 12:44:32','-',0,75.0000),(20,6,'Deposit','2014-04-25 12:46:03','NA',0,11.0000),(21,6,'Sell','2014-04-25 12:48:24','GOOG',8676,4556288.1600),(22,6,'Deposit','2014-04-26 09:44:20','NA',0,5.5500),(23,6,'Deposit','2014-04-26 09:44:29','NA',0,0.5100),(24,6,'Buy','2014-04-26 09:44:41','GOOG',5000,516.1800),(25,6,'Buy','2014-04-26 09:44:51','FB',5000,57.7100),(26,6,'Sell','2014-04-26 09:45:17','SSNC',511,19060.3000),(27,6,'Buy','2014-04-26 09:45:45','SSNC',5000,37.3000),(28,26,'Buy','2014-04-26 09:48:37','FB',50,57.7100),(29,26,'Buy','2014-04-26 09:48:47','TWTR',50,41.6100),(30,26,'Buy','2014-04-26 09:49:02','GOOG',5,516.1800),(31,26,'Buy','2014-04-26 09:51:20','AMZN',5,303.8300),(32,26,'Buy','2014-04-26 09:51:39','RAX',10,28.9500),(33,26,'Buy','2014-04-26 09:53:24','TGT',10,61.2600),(34,6,'Sell','2014-04-26 10:08:42','SSNC',5000,186500.0000),(35,6,'Buy','2014-04-26 10:08:50','SSNC',5000,37.3000),(36,6,'Sell','2014-04-26 10:12:26','SSNC',5000,186500.0000),(37,6,'Buy','2014-04-26 10:12:33','SSNC',5000,37.3000),(38,6,'Sell','2014-04-26 10:16:31','SSNC',5000,186500.0000),(39,6,'Buy','2014-04-26 10:16:39','SSNC',5000,37.3000),(40,6,'Sell','2014-04-26 10:18:54','SSNC',5000,186500.0000),(41,6,'Buy','2014-04-26 10:19:04','SSNC',12345,37.3000),(42,6,'Sell','2014-04-26 10:19:54','SSNC',12345,460468.5000),(43,27,'Buy','2014-04-26 10:27:00','GOOG',10,516.1800),(44,6,'Deposit','2014-05-04 16:09:59','NA',0,5000.0000),(45,6,'Buy','2014-05-04 16:27:10','GOOG',100,527.9300),(46,6,'Deposit','2014-05-04 16:30:38','NA',0,10000.0000),(47,6,'Deposit','2014-05-04 16:30:55','NA',0,10000.0000),(48,6,'Sell','2014-05-04 16:37:15','FB',5000,302300.0000),(49,6,'Buy','2014-05-04 16:37:30','TWTR',450,39.0200),(50,6,'Sell','2014-05-04 16:38:20','TWTR',1000,39020.0000);
/*!40000 ALTER TABLE `transactions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000),(2,'hirschhorn','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000),(4,'malan','$1$HA$azTGIMVlmPi9W9Y12cYSj/',10000.0000),(5,'milo','$1$HA$6DHumQaK4GhpX8QE23C8V1',10000.0000),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',343761.0000),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000),(28,'JCol','$1$Ct4og4ez$Wl/.wohMOEbVzVazDK7Qi1',10000.0000);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-05-04 12:43:06
