/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIMESH_H_
#define _NIMESH_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiRenderObject.h"

// Include structures
#include "../gen/SphereBV.h"
#include "../gen/MeshData.h"
#include "../Ref.h"
#include "../gen/ExtraMeshDataEpicMickey.h"
#include "../gen/ExtraMeshDataEpicMickey2.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiMeshModifier;
class NiMesh;
typedef Ref<NiMesh> NiMeshRef;

/*!  */
class NiMesh : public NiRenderObject {
public:
	/*! Constructor */
	NIFLIB_API NiMesh();

	/*! Destructor */
	NIFLIB_API virtual ~NiMesh();

	/*!
	 * A constant value which uniquly identifies objects of this type.
	 */
	NIFLIB_API static const Type TYPE;

	/*!
	 * A factory function used during file reading to create an instance of this type of object.
	 * \return A pointer to a newly allocated instance of this type of object.
	 */
	NIFLIB_API static NiObject * Create();

	/*!
	 * Summarizes the information contained in this object in English.
	 * \param[in] verbose Determines whether or not detailed information about large areas of data will be printed out.
	 * \return A string containing a summary of the information within the object in English.  This is the function that Niflyze calls to generate its analysis, so the output is the same.
	 */
	NIFLIB_API virtual string asString( bool verbose = false ) const;

	/*!
	 * Used to determine the type of a particular instance of this object.
	 * \return The type constant for the actual type of the object.
	 */
	NIFLIB_API virtual const Type & GetType() const;

	/***Begin Example Naive Implementation****

	// The primitive type of the mesh, such as triangles or lines.
	// \return The current value.
	MeshPrimitiveType GetPrimitiveType() const;

	// The primitive type of the mesh, such as triangles or lines.
	// \param[in] value The new value.
	void SetPrimitiveType( const MeshPrimitiveType & value );

	// The number of submeshes contained in this mesh.
	// \return The current value.
	unsigned short GetNumSubmeshes() const;

	// The number of submeshes contained in this mesh.
	// \param[in] value The new value.
	void SetNumSubmeshes( unsigned short value );

	// Sets whether hardware instancing is being used.
	// \return The current value.
	bool GetInstancingEnabled() const;

	// Sets whether hardware instancing is being used.
	// \param[in] value The new value.
	void SetInstancingEnabled( bool value );

	// The combined bounding volume of all submeshes.
	// \return The current value.
	SphereBV GetBound() const;

	// The combined bounding volume of all submeshes.
	// \param[in] value The new value.
	void SetBound( const SphereBV & value );

	// Unknown.
	// \return The current value.
	vector<MeshData > GetDatas() const;

	// Unknown.
	// \param[in] value The new value.
	void SetDatas( const vector<MeshData >& value );

	// Unknown.
	// \return The current value.
	vector<Ref<NiMeshModifier > > GetModifiers() const;

	// Unknown.
	// \param[in] value The new value.
	void SetModifiers( const vector<Ref<NiMeshModifier > >& value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
protected:
	/*! The primitive type of the mesh, such as triangles or lines. */
	MeshPrimitiveType primitiveType;
	/*! Unknown. */
	int unknown51;
	/*! Unknown. */
	int unknown52;
	/*! Unknown. */
	int unknown53;
	/*! Unknown. */
	int unknown54;
	/*! Unknown. */
	float unknown55;
	/*! Unknown. */
	int unknown56;
	/*! The number of submeshes contained in this mesh. */
	unsigned short numSubmeshes;
	/*! Sets whether hardware instancing is being used. */
	bool instancingEnabled;
	/*! The combined bounding volume of all submeshes. */
	SphereBV bound;
	/*! Unknown. */
	mutable unsigned int numDatas;
	/*! Unknown. */
	vector<MeshData > datas;
	/*! Unknown. */
	mutable unsigned int numModifiers;
	/*! Unknown. */
	vector<Ref<NiMeshModifier > > modifiers;
	/*! Unknown. */
	byte unknown100;
	/*! Unknown. */
	int unknown101;
	/*! Size of additional data. */
	mutable unsigned int unknown102;
	/*! Unknown. */
	vector<float > unknown103;
	/*! Unknown. */
	mutable int unknown200;
	/*! Unknown. */
	vector<ExtraMeshDataEpicMickey > unknown201;
	/*! Unknown. */
	mutable int unknown250;
	/*! Unknown. */
	vector<int > unknown251;
	/*! Unknown. */
	int unknown300;
	/*! Unknown. */
	short unknown301;
	/*! Unknown. */
	mutable int unknown302;
	/*! Unknown. */
	vector<byte > unknown303;
	/*! Unknown. */
	mutable int unknown350;
	/*! Unknown. */
	vector<ExtraMeshDataEpicMickey2 > unknown351;
	/*! Unknown. */
	int unknown400;
public:
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info );
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info );
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list<NiObjectRef> GetRefs() const;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list<NiObject *> GetPtrs() const;
};

//--BEGIN FILE FOOT CUSTOM CODE--//

//--END CUSTOM CODE--//

} //End Niflib namespace
#endif
