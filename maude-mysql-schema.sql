-- The database consists of three tables foi_device, mdrfoi and fiotext defined below
-- phpMyAdmin SQL Dump
-- version 3.4.11.1deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Oct 21, 2013 at 09:47 AM
-- Server version: 5.5.32
-- PHP Version: 5.4.6-1ubuntu1.4

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

CREATE database IF NOT EXISTS maude;
 
--
-- Database: `maude`

use maude;

-- --------------------------------------------------------

-- 
-- Table structure for table `foi_device`

CREATE TABLE IF NOT EXISTS `devicefoi` (
  `mdr_report_key` int(11) unsigned NOT NULL,
  `device_product_code` char(3) NOT NULL,
  PRIMARY KEY(mdr_report_key, device_product_code) 
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

CREATE TABLE IF NOT EXISTS `mdrfoi` (
  `mdr_report_key` int(11) unsigned NOT NULL,
  `report_source_code` CHAR(1) NOT NULL,
  `date_received` DATE NOT NULL,
  FOREIGN KEY (mdr_report_key) REFERENCES devicefoi (mdr_report_key),
  PRIMARY KEY (mdr_report_key)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;

CREATE TABLE IF NOT EXISTS `textfoi` (
  mdr_report_key int(11) unsigned NOT NULL,
  text_report TEXT,
  FOREIGN KEY (mdr_report_key) REFERENCES devicefoi (mdr_report_key),
  PRIMARY KEY (mdr_report_key)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;


CREATE TABLE IF NOT EXISTS medwatch_report (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `mdr_report_key` int(11) unsigned NOT NULL,
  `text_report` longtext NOT NULL,
  `date_received` date NOT NULL,
  `report_source_code` char(1) NOT NULL,
  `word_cnt` INT NOT NULL,
   UNIQUE(mdr_report_key),
   PRIMARY KEY(id)
) ENGINE=MyIsam DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;

/* 1. MDR Report Key */
/* 2. MDR Text Key */
/* 3. Text Type Code (D=B5, E=H3, N=H10 from mdr_text table) */
/* 4. Patient Sequence Number (from mdr_text table) */
/* 5. Date Report (from mdr_text table) */
/* 6. Text (B5, or H3 or H10 from mdr_text table) */
