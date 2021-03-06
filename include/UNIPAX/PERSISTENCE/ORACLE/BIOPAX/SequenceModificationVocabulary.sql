/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

SET FEEDBACK OFF;
WHENEVER SQLERROR EXIT FAILURE;
WHENEVER OSERROR EXIT FAILURE;

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SequenceModificationVocabulary_id_xref" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SequenceModificationVocabulary_id_xref_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SequenceModificationVocabulary_id_xref_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SequenceModificationVocabulary_comment" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SequenceModificationVocabulary_comment_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SequenceModificationVocabulary_comment_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "SequenceModificationVocabulary" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "SequenceModificationVocabulary_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "SequenceModificationVocabulary_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/


CREATE TABLE "SequenceModificationVocabulary" (
  "unipaxId" NUMBER(20) NOT NULL PRIMARY KEY,
  "unipaxSource" NUMBER(20),
  "term" VARCHAR2(512));

CREATE TABLE "SequenceModificationVocabulary_comment" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" VARCHAR2(512),
  CONSTRAINT "SequenceModificationVocabulary_comment_object_"
    FOREIGN KEY ("object_id")
    REFERENCES "SequenceModificationVocabulary" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "SequenceModificationVocabulary_comment_object_"
  ON "SequenceModificationVocabulary_comment" ("object_id");

CREATE INDEX "SequenceModificationVocabulary_comment_index_i"
  ON "SequenceModificationVocabulary_comment" ("index");

CREATE TABLE "SequenceModificationVocabulary_id_xref" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "SequenceModificationVocabulary_id_xref_object_"
    FOREIGN KEY ("object_id")
    REFERENCES "SequenceModificationVocabulary" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "SequenceModificationVocabulary_id_xref_object_"
  ON "SequenceModificationVocabulary_id_xref" ("object_id");

CREATE INDEX "SequenceModificationVocabulary_id_xref_index_i"
  ON "SequenceModificationVocabulary_id_xref" ("index");

ALTER TABLE "SequenceModificationVocabulary" ADD
  CONSTRAINT "SequenceModificationVocabulary_unipaxSource_fk"
    FOREIGN KEY ("unipaxSource")
    REFERENCES "ImportSource" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

EXIT;
