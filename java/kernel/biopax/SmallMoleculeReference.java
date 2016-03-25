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
public class SmallMoleculeReference extends EntityReference {
	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected String chemicalFormula;

	/** 
	 * @return the chemicalFormula
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public String getChemicalFormula() {
		// begin-user-code
		return chemicalFormula;
		// end-user-code
	}

	/** 
	 * @param chemicalFormula the chemicalFormula to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setChemicalFormula(String chemicalFormula) {
		// begin-user-code
		this.chemicalFormula = chemicalFormula;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	protected double molecularWeight;

	/** 
	 * @return the molecularWeight
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public double getMolecularWeight() {
		// begin-user-code
		return molecularWeight;
		// end-user-code
	}

	/** 
	 * @param molecularWeight the molecularWeight to set
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public void setMolecularWeight(double molecularWeight) {
		// begin-user-code
		this.molecularWeight = molecularWeight;
		// end-user-code
	}

	/** 
	 * <!-- begin-UML-doc -->
	 * <!-- end-UML-doc -->
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ChemicalStructure structure;

	/** 
	 * @return the structure
	 * @generated "UML to Java (com.ibm.xtools.transform.uml2.java5.internal.UML2JavaTransform)"
	 */
	public ChemicalStructure getStructure() {
		// begin-user-code
		return structure;
		// end-user-code
	}
}