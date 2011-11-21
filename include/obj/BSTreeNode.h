/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BSTREENODE_H_
#define _BSTREENODE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiAVObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiAVObject;
class NiNode;
class BSTreeNode;
typedef Ref<BSTreeNode> BSTreeNodeRef;

/*! Node for handling Trees, Switches branch configurations for variation? */
class BSTreeNode : public NiAVObject {
public:
	/*! Constructor */
	NIFLIB_API BSTreeNode();

	/*! Destructor */
	NIFLIB_API virtual ~BSTreeNode();

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

	// List of child node object indices.
	// \return The current value.
	vector<Ref<NiAVObject > > GetChildren() const;

	// List of child node object indices.
	// \param[in] value The new value.
	void SetChildren( const vector<Ref<NiAVObject > >& value );

	// Unknown
	// \return The current value.
	vector<Ref<NiNode > > GetBones1() const;

	// Unknown
	// \param[in] value The new value.
	void SetBones1( const vector<Ref<NiNode > >& value );

	// Unknown
	// \return The current value.
	vector<Ref<NiNode > > GetBones() const;

	// Unknown
	// \param[in] value The new value.
	void SetBones( const vector<Ref<NiNode > >& value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
protected:
	/*! The number of child objects. */
	mutable unsigned int numChildren;
	/*! List of child node object indices. */
	vector<Ref<NiAVObject > > children;
	/*! Unknown */
	unsigned int unknownInt1;
	/*! Unknown */
	mutable unsigned int numBones1;
	/*! Unknown */
	vector<Ref<NiNode > > bones1;
	/*! Unknown */
	mutable unsigned int numBones2;
	/*! Unknown */
	vector<Ref<NiNode > > bones;
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