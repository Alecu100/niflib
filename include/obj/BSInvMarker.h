/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BSINVMARKER_H_
#define _BSINVMARKER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiExtraData.h"
namespace Niflib {

class BSInvMarker;
typedef Ref<BSInvMarker> BSInvMarkerRef;

/*!
 * Orientation marker for Skyrim's inventory view.
 *     How to show the nif in the player's inventory.
 *     Typically attached to the root node of the nif tree.
 *     If not present, then Skyrim will still show the nif in inventory,
 *     using the default values.
 *     Name should be 'INV' (without the quotes).
 */
class BSInvMarker : public NiExtraData {
public:
	/*! Constructor */
	NIFLIB_API BSInvMarker();

	/*! Destructor */
	NIFLIB_API virtual ~BSInvMarker();

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

	// Up-down rotation, in radians * 1000.
	// \return The current value.
	unsigned int GetRotation1() const;

	// Up-down rotation, in radians * 1000.
	// \param[in] value The new value.
	void SetRotation1( unsigned int value );

	// Left-right rotation, in radians * 1000.
	// \return The current value.
	unsigned int GetRotation2() const;

	// Left-right rotation, in radians * 1000.
	// \param[in] value The new value.
	void SetRotation2( unsigned int value );

	// Zoom factor. 16000 is really far away, 16600 is really close by.
	// \return The current value.
	unsigned short GetZoom() const;

	// Zoom factor. 16000 is really far away, 16600 is really close by.
	// \param[in] value The new value.
	void SetZoom( unsigned short value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
protected:
	/*! Up-down rotation, in radians * 1000. */
	unsigned int rotation1;
	/*! Left-right rotation, in radians * 1000. */
	unsigned int rotation2;
	/*! Zoom factor. 16000 is really far away, 16600 is really close by. */
	unsigned short zoom;
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
