/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

DROP TABLE IF EXISTS `Conversion_rightEntity`;

DROP TABLE IF EXISTS `Conversion_leftEntity`;

DROP TABLE IF EXISTS `Conversion_participantStoichiometry`;

DROP TABLE IF EXISTS `Conversion`;

CREATE TABLE `Conversion` (
  `unipaxId` BIGINT UNSIGNED NOT NULL PRIMARY KEY,
  `conversionDirection` TEXT NOT NULL,
  `spontaneous` TINYINT(1) NOT NULL,
  `kineticLaw` BIGINT UNSIGNED NULL)
 ENGINE=InnoDB;

CREATE TABLE `Conversion_participantStoichiometry` (
  `object_id` BIGINT UNSIGNED NOT NULL,
  `index` BIGINT UNSIGNED NOT NULL,
  `value` BIGINT UNSIGNED NULL,
  CONSTRAINT `Conversion_participantStoichiometry_object_id_fk`
    FOREIGN KEY (`object_id`)
    REFERENCES `Conversion` (`unipaxId`)
    ON DELETE CASCADE)
 ENGINE=InnoDB;

CREATE INDEX `object_id_i`
  ON `Conversion_participantStoichiometry` (`object_id`);

CREATE INDEX `index_i`
  ON `Conversion_participantStoichiometry` (`index`);

CREATE TABLE `Conversion_leftEntity` (
  `object_id` BIGINT UNSIGNED NOT NULL,
  `index` BIGINT UNSIGNED NOT NULL,
  `value` BIGINT UNSIGNED NULL,
  CONSTRAINT `Conversion_leftEntity_object_id_fk`
    FOREIGN KEY (`object_id`)
    REFERENCES `Conversion` (`unipaxId`)
    ON DELETE CASCADE)
 ENGINE=InnoDB;

CREATE INDEX `object_id_i`
  ON `Conversion_leftEntity` (`object_id`);

CREATE INDEX `index_i`
  ON `Conversion_leftEntity` (`index`);

CREATE TABLE `Conversion_rightEntity` (
  `object_id` BIGINT UNSIGNED NOT NULL,
  `index` BIGINT UNSIGNED NOT NULL,
  `value` BIGINT UNSIGNED NULL,
  CONSTRAINT `Conversion_rightEntity_object_id_fk`
    FOREIGN KEY (`object_id`)
    REFERENCES `Conversion` (`unipaxId`)
    ON DELETE CASCADE)
 ENGINE=InnoDB;

CREATE INDEX `object_id_i`
  ON `Conversion_rightEntity` (`object_id`);

CREATE INDEX `index_i`
  ON `Conversion_rightEntity` (`index`);

ALTER TABLE `Conversion`
  ADD CONSTRAINT `Conversion_unipaxId_fk`
    FOREIGN KEY (`unipaxId`)
    REFERENCES `Interaction` (`unipaxId`)
    ON DELETE CASCADE
  /*
  ADD CONSTRAINT `Conversion_kineticLaw_fk`
    FOREIGN KEY (`kineticLaw`)
    REFERENCES `KineticLaw` (`unipaxId`)
  */;

/*
ALTER TABLE `Conversion_participantStoichiometry`
  ADD CONSTRAINT `Conversion_participantStoichiometry_value_fk`
    FOREIGN KEY (`value`)
    REFERENCES `Stoichiometry` (`unipaxId`)
*/

/*
ALTER TABLE `Conversion_leftEntity`
  ADD CONSTRAINT `Conversion_leftEntity_value_fk`
    FOREIGN KEY (`value`)
    REFERENCES `PhysicalEntity` (`unipaxId`)
*/

/*
ALTER TABLE `Conversion_rightEntity`
  ADD CONSTRAINT `Conversion_rightEntity_value_fk`
    FOREIGN KEY (`value`)
    REFERENCES `PhysicalEntity` (`unipaxId`)
*/

