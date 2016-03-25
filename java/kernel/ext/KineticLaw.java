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
public class KineticLaw extends SBase {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Set<LocalParameter> localParameter;

	/** 
	 * @return the localParameter
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Set<LocalParameter> getLocalParameter() {
		// begin-user-code
		return localParameter;
		// end-user-code
	}

	/** 
	 * @param localParameter the localParameter to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setLocalParameter(Set<LocalParameter> localParameter) {
		// begin-user-code
		this.localParameter = localParameter;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected Conversion conversion;

	/** 
	 * @return the conversion
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public Conversion getConversion() {
		// begin-user-code
		return conversion;
		// end-user-code
	}

	/** 
	 * @param conversion the conversion to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setConversion(Conversion conversion) {
		// begin-user-code
		this.conversion = conversion;
		// end-user-code
	}
}