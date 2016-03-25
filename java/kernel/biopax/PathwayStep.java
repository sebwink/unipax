/**
 * 
 */
package unipax;

/** 
 * <!-- begin-UML-doc -->
 * <!-- end-UML-doc -->
 * @author niermann
 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
 */
public class PathwayStep extends UtilityClass {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Evidence evidence;

	/** 
	 * @return the evidence
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Evidence getEvidence() {
		// begin-user-code
		return evidence;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public PathwayStep nextStep;

	/** 
	 * @return the nextStep
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public PathwayStep getNextStep() {
		// begin-user-code
		return nextStep;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Entity processStep;

	/** 
	 * @return the processStep
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Entity getProcessStep() {
		// begin-user-code
		return processStep;
		// end-user-code
	}

	/** 
	 * @param processStep the processStep to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setProcessStep(Entity processStep) {
		// begin-user-code
		this.processStep = processStep;
		// end-user-code
	}
}