/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

SET FEEDBACK OFF;
WHENEVER SQLERROR EXIT FAILURE;
WHENEVER OSERROR EXIT FAILURE;

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Model_id_event" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Model_id_event_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Model_id_event_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Model_id_constraint" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Model_id_constraint_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Model_id_constraint_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Model_id_rule" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Model_id_rule_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Model_id_rule_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Model_id_initialAssignment" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Model_id_initialAssignment_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Model_id_initialAssignment_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Model_id_parameter" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Model_id_parameter_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Model_id_parameter_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Model_id_unitDefinition" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Model_id_unitDefinition_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Model_id_unitDefinition_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Model_id_functionDefinition" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Model_id_functionDefinition_se"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Model_id_functionDefinition_tr"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/

BEGIN
  BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE "Model" CASCADE CONSTRAINTS';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -942 THEN RAISE; END IF;
  END;  BEGIN
    EXECUTE IMMEDIATE 'DROP SEQUENCE "Model_seq"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -2289 THEN RAISE; END IF;
  END;
  BEGIN
    EXECUTE IMMEDIATE 'DROP TRIGGER "Model_trg"';
  EXCEPTION
    WHEN OTHERS THEN
      IF SQLCODE != -4080 THEN RAISE; END IF;
  END;
END;
/


CREATE TABLE "Model" (
  "unipaxId" NUMBER(20) NOT NULL PRIMARY KEY,
  "unipaxSource" NUMBER(20),
  "metaId" VARCHAR2(512),
  "sboTerm" VARCHAR2(512),
  "notes" VARCHAR2(512),
  "annotation" VARCHAR2(512),
  "id" VARCHAR2(512),
  "name" VARCHAR2(512),
  "substanceUnits" VARCHAR2(512),
  "timeUnits" VARCHAR2(512),
  "volumeUnits" VARCHAR2(512),
  "areaUnits" VARCHAR2(512),
  "lengthUnits" VARCHAR2(512),
  "extentUnit" VARCHAR2(512),
  "conversionFactor" VARCHAR2(512));

CREATE TABLE "Model_id_functionDefinition" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Model_id_functionDefinition_ob"
    FOREIGN KEY ("object_id")
    REFERENCES "Model" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Model_id_functionDefinition_ob"
  ON "Model_id_functionDefinition" ("object_id");

CREATE INDEX "Model_id_functionDefinition_in"
  ON "Model_id_functionDefinition" ("index");

CREATE TABLE "Model_id_unitDefinition" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Model_id_unitDefinition_object"
    FOREIGN KEY ("object_id")
    REFERENCES "Model" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Model_id_unitDefinition_object"
  ON "Model_id_unitDefinition" ("object_id");

CREATE INDEX "Model_id_unitDefinition_index_"
  ON "Model_id_unitDefinition" ("index");

CREATE TABLE "Model_id_parameter" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Model_id_parameter_object_id_f"
    FOREIGN KEY ("object_id")
    REFERENCES "Model" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Model_id_parameter_object_id_i"
  ON "Model_id_parameter" ("object_id");

CREATE INDEX "Model_id_parameter_index_i"
  ON "Model_id_parameter" ("index");

CREATE TABLE "Model_id_initialAssignment" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Model_id_initialAssignment_obj"
    FOREIGN KEY ("object_id")
    REFERENCES "Model" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Model_id_initialAssignment_obj"
  ON "Model_id_initialAssignment" ("object_id");

CREATE INDEX "Model_id_initialAssignment_ind"
  ON "Model_id_initialAssignment" ("index");

CREATE TABLE "Model_id_rule" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Model_id_rule_object_id_fk"
    FOREIGN KEY ("object_id")
    REFERENCES "Model" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Model_id_rule_object_id_i"
  ON "Model_id_rule" ("object_id");

CREATE INDEX "Model_id_rule_index_i"
  ON "Model_id_rule" ("index");

CREATE TABLE "Model_id_constraint" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Model_id_constraint_object_id_"
    FOREIGN KEY ("object_id")
    REFERENCES "Model" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Model_id_constraint_object_id_"
  ON "Model_id_constraint" ("object_id");

CREATE INDEX "Model_id_constraint_index_i"
  ON "Model_id_constraint" ("index");

CREATE TABLE "Model_id_event" (
  "object_id" NUMBER(20) NOT NULL,
  "index" NUMBER(20) NOT NULL,
  "value" NUMBER(20) NOT NULL,
  CONSTRAINT "Model_id_event_object_id_fk"
    FOREIGN KEY ("object_id")
    REFERENCES "Model" ("unipaxId")
    ON DELETE CASCADE);

CREATE INDEX "Model_id_event_object_id_i"
  ON "Model_id_event" ("object_id");

CREATE INDEX "Model_id_event_index_i"
  ON "Model_id_event" ("index");

ALTER TABLE "Model" ADD
  CONSTRAINT "Model_unipaxSource_fk"
    FOREIGN KEY ("unipaxSource")
    REFERENCES "ImportSource" ("unipaxId")
    DEFERRABLE INITIALLY DEFERRED;

EXIT;
