/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for licence. */

#ifndef _NICOLLISIONOBJECT_H_
#define _NICOLLISIONOBJECT_H_

#include "xml_extract.h"
#include NI_COLLISION_OBJECT_INCLUDE
#include "NiAVObject.h"

/*
 * NiCollisionObject
 */

class NiCollisionObject;
typedef Ref<NiCollisionObject> NiCollisionObjectRef;

class NiCollisionObject : public NI_COLLISION_OBJECT_PARENT {
public:
	NiCollisionObject();
	~NiCollisionObject();
	//Run-Time Type Information
	static const Type TYPE;
	virtual void Read( istream& in, list<uint> link_stack, unsigned int version );
	virtual void Write( ostream& out, map<NiObjectRef,uint> link_map, unsigned int version ) const;
	virtual string asString( bool verbose = false ) const;
	virtual void FixLinks( const vector<NiObjectRef> & objects, list<uint> link_stack, unsigned int version );
	
	NiAVObject * Parent() const;
private:
	NI_COLLISION_OBJECT_MEMBERS
};
#endif