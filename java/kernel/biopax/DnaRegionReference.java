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
public class DnaRegionReference extends EntityReference {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected String sequence;

	/** 
	 * @return the sequence
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String getSequence() {
		// begin-user-code
		return sequence;
		// end-user-code
	}

	/** 
	 * @param sequence the sequence to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setSequence(String sequence) {
		// begin-user-code
		this.sequence = sequence;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public SequenceRegionVocabulary regionType;

	/** 
	 * @return the regionType
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public SequenceRegionVocabulary getRegionType() {
		// begin-user-code
		return regionType;
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
	public SequenceLocation absoluteRegion;

	/** 
	 * @return the absoluteRegion
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public SequenceLocation getAbsoluteRegion() {
		// begin-user-code
		return absoluteRegion;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected EntityReference subRegion;

	/** 
	 * @return the subRegion
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public EntityReference getSubRegion() {
		// begin-user-code
		return subRegion;
		// end-user-code
	}

	/** 
	 * @param subRegion the subRegion to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setSubRegion(EntityReference subRegion) {
		// begin-user-code
		this.subRegion = subRegion;
		// end-user-code
	}
}