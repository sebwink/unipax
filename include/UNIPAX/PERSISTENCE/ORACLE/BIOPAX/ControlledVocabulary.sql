/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

SET FEEDBACK OFF;
WHENEVER SQLERROR EXIT FAILURE;
WHENEVER OSERROR EXIT FAILURE;

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "ControlledVocabulary_id_xref" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "ControlledVocabulary_id_xref_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "ControlledVocabulary_id_xref_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "ControlledVocabulary_comment" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "ControlledVocabulary_comment_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "ControlledVocabulary_comment_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "ControlledVocabulary" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "ControlledVocabulary_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "ControlledVocabulary_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/


CREATE TABLE "ControlledVocabulary" (
  "unipaxId" NUMBER(20) NOT NULL PRIMARY KEY,
  "unipaxSource" NUMBER(20),
  "term" VARCHAR2(512));

CREATE TABLE "ControlledVocabulary_comment" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" VARCHAR2(512),
  CONSTRAINT "ControlledVocabulary_comment_object_i"
    FOREIGN KEY ("object_id")
    REFERENCES "ControlledVocabulary" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "ControlledVocabulary_comment_object_i"
  ON "ControlledVocabulary_comment" ("object_id");

CREATE INDEX "ControlledVocabulary_comment_index_i"
  ON "ControlledVocabulary_comment" ("index");

CREATE TABLE "ControlledVocabulary_id_xref" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "ControlledVocabulary_id_xref_object_i"
    FOREIGN KEY ("object_id")
    REFERENCES "ControlledVocabulary" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "ControlledVocabulary_id_xref_object_i"
  ON "ControlledVocabulary_id_xref" ("object_id");

CREATE INDEX "ControlledVocabulary_id_xref_index_i"
  ON "ControlledVocabulary_id_xref" ("index");

ALTER TABLE "ControlledVocabulary" ADD
  CONSTRAINT "ControlledVocabulary_unipaxSource_fk"
    FOREIGN KEY ("unipaxSource")
    REFERENCES "ImportSource" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

EXIT;