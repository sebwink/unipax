/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

DROP TABLE IF EXISTS `InteractionVocabulary`;

CREATE TABLE `InteractionVocabulary` (
  `unipaxId` BIGINT UNSIGNED NOT NULL PRIMARY KEY)
 ENGINE=InnoDB;

ALTER TABLE `InteractionVocabulary`
  ADD CONSTRAINT `InteractionVocabulary_unipaxId_fk`
    FOREIGN KEY (`unipaxId`)
    REFERENCES `ControlledVocabulary` (`unipaxId`)
    ON DELETE CASCADE;

