/**
 * 
 */
package unipax;

import java.util.Set;

/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author niermann
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class Pathway extends Entity {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public PathwayStep pathwayOrder;

	/** 
	 * @return the pathwayOrder
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public PathwayStep getPathwayOrder() {
		// begin-user-code
		return pathwayOrder;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public BioSource organism;

	/** 
	 * @return the organism
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public BioSource getOrganism() {
		// begin-user-code
		return organism;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Set<FunctionDefinition> functionDefinition;

	/** 
	 * @return the functionDefinition
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<FunctionDefinition> getFunctionDefinition() {
		// begin-user-code
		return functionDefinition;
		// end-user-code
	}

	/** 
	 * @param functionDefinition the functionDefinition to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setFunctionDefinition(Set<FunctionDefinition> functionDefinition) {
		// begin-user-code
		this.functionDefinition = functionDefinition;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Set<UnitDefinition> unitDefinition;

	/** 
	 * @return the unitDefinition
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<UnitDefinition> getUnitDefinition() {
		// begin-user-code
		return unitDefinition;
		// end-user-code
	}

	/** 
	 * @param unitDefinition the unitDefinition to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setUnitDefinition(Set<UnitDefinition> unitDefinition) {
		// begin-user-code
		this.unitDefinition = unitDefinition;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Set<Parameter> parameter;

	/** 
	 * @return the parameter
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<Parameter> getParameter() {
		// begin-user-code
		return parameter;
		// end-user-code
	}

	/** 
	 * @param parameter the parameter to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setParameter(Set<Parameter> parameter) {
		// begin-user-code
		this.parameter = parameter;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Set<InitialAssignment> initialAssignment;

	/** 
	 * @return the initialAssignment
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<InitialAssignment> getInitialAssignment() {
		// begin-user-code
		return initialAssignment;
		// end-user-code
	}

	/** 
	 * @param initialAssignment the initialAssignment to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setInitialAssignment(Set<InitialAssignment> initialAssignment) {
		// begin-user-code
		this.initialAssignment = initialAssignment;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Set<Rule> rule;

	/** 
	 * @return the rule
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<Rule> getRule() {
		// begin-user-code
		return rule;
		// end-user-code
	}

	/** 
	 * @param rule the rule to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setRule(Set<Rule> rule) {
		// begin-user-code
		this.rule = rule;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Set<Constraint> constraint;

	/** 
	 * @return the constraint
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<Constraint> getConstraint() {
		// begin-user-code
		return constraint;
		// end-user-code
	}

	/** 
	 * @param constraint the constraint to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setConstraint(Set<Constraint> constraint) {
		// begin-user-code
		this.constraint = constraint;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Set<Event> event;

	/** 
	 * @return the event
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<Event> getEvent() {
		// begin-user-code
		return event;
		// end-user-code
	}

	/** 
	 * @param event the event to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setEvent(Set<Event> event) {
		// begin-user-code
		this.event = event;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Entity component;

	/** 
	 * @return the component
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Entity getComponent() {
		// begin-user-code
		return component;
		// end-user-code
	}

	/** 
	 * @param component the component to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setComponent(Entity component) {
		// begin-user-code
		this.component = component;
		// end-user-code
	}
}