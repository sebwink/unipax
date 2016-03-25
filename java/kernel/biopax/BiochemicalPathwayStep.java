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
public class BiochemicalPathwayStep extends PathwayStep {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected String stepDirection;

	/** 
	 * @return the stepDirection
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String getStepDirection() {
		// begin-user-code
		return stepDirection;
		// end-user-code
	}

	/** 
	 * @param stepDirection the stepDirection to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setStepDirection(String stepDirection) {
		// begin-user-code
		this.stepDirection = stepDirection;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Conversion stepConversion;

	/** 
	 * @return the stepConversion
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Conversion getStepConversion() {
		// begin-user-code
		return stepConversion;
		// end-user-code
	}
}