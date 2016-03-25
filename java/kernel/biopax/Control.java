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
public class Control extends Interaction {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected String controlType;

	/** 
	 * @return the controlType
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String getControlType() {
		// begin-user-code
		return controlType;
		// end-user-code
	}

	/** 
	 * @param controlType the controlType to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setControlType(String controlType) {
		// begin-user-code
		this.controlType = controlType;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Set<Entity> controller;

	/** 
	 * @return the controller
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<Entity> getController() {
		// begin-user-code
		return controller;
		// end-user-code
	}

	/** 
	 * @param controller the controller to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setController(Set<Entity> controller) {
		// begin-user-code
		this.controller = controller;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Entity controlled;

	/** 
	 * @return the controlled
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Entity getControlled() {
		// begin-user-code
		return controlled;
		// end-user-code
	}

	/** 
	 * @param controlled the controlled to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setControlled(Entity controlled) {
		// begin-user-code
		this.controlled = controlled;
		// end-user-code
	}
}