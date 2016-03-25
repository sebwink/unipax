/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

DROP TABLE IF EXISTS `RateRule`;

CREATE TABLE `RateRule` (
  `unipaxId` BIGINT UNSIGNED NOT NULL PRIMARY KEY,
  `variable` TEXT NOT NULL)
 ENGINE=InnoDB;

ALTER TABLE `RateRule`
  ADD CONSTRAINT `RateRule_unipaxId_fk`
    FOREIGN KEY (`unipaxId`)
    REFERENCES `Rule` (`unipaxId`)
    ON DELETE CASCADE;
