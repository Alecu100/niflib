/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/BSProceduralLightningController.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSProceduralLightningController::TYPE("BSProceduralLightningController", &NiFloatInterpController::TYPE );

BSProceduralLightningController::BSProceduralLightningController() : target___((unsigned int)0), target___1((unsigned int)0), target___2((unsigned int)0), target___3((unsigned int)0), target___4((unsigned int)0), target___5((unsigned int)0), target___6((unsigned int)0), target___7((unsigned int)0), unknownShort1((unsigned short)0), unknownShort2((unsigned short)0), unknownShort3((unsigned short)0), float1(0.0f), float2(0.0f), float3(0.0f), float4(0.0f), float5(0.0f), byte1((byte)0), byte2((byte)0), byte3((byte)0), target___8((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSProceduralLightningController::~BSProceduralLightningController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSProceduralLightningController::GetType() const {
	return TYPE;
}

NiObject * BSProceduralLightningController::Create() {
	return new BSProceduralLightningController;
}

void BSProceduralLightningController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiFloatInterpController::Read( in, link_stack, info );
	NifStream( target___, in, info );
	NifStream( target___1, in, info );
	NifStream( target___2, in, info );
	NifStream( target___3, in, info );
	NifStream( target___4, in, info );
	NifStream( target___5, in, info );
	NifStream( target___6, in, info );
	NifStream( target___7, in, info );
	NifStream( unknownShort1, in, info );
	NifStream( unknownShort2, in, info );
	NifStream( unknownShort3, in, info );
	NifStream( float1, in, info );
	NifStream( float2, in, info );
	NifStream( float3, in, info );
	NifStream( float4, in, info );
	NifStream( float5, in, info );
	NifStream( byte1, in, info );
	NifStream( byte2, in, info );
	NifStream( byte3, in, info );
	NifStream( target___8, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSProceduralLightningController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiFloatInterpController::Write( out, link_map, missing_link_stack, info );
	NifStream( target___, out, info );
	NifStream( target___1, out, info );
	NifStream( target___2, out, info );
	NifStream( target___3, out, info );
	NifStream( target___4, out, info );
	NifStream( target___5, out, info );
	NifStream( target___6, out, info );
	NifStream( target___7, out, info );
	NifStream( unknownShort1, out, info );
	NifStream( unknownShort2, out, info );
	NifStream( unknownShort3, out, info );
	NifStream( float1, out, info );
	NifStream( float2, out, info );
	NifStream( float3, out, info );
	NifStream( float4, out, info );
	NifStream( float5, out, info );
	NifStream( byte1, out, info );
	NifStream( byte2, out, info );
	NifStream( byte3, out, info );
	NifStream( target___8, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSProceduralLightningController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiFloatInterpController::asString();
	out << "  Target(?):  " << target___ << endl;
	out << "  Target(?)1:  " << target___1 << endl;
	out << "  Target(?)2:  " << target___2 << endl;
	out << "  Target(?)3:  " << target___3 << endl;
	out << "  Target(?)4:  " << target___4 << endl;
	out << "  Target(?)5:  " << target___5 << endl;
	out << "  Target(?)6:  " << target___6 << endl;
	out << "  Target(?)7:  " << target___7 << endl;
	out << "  Unknown Short 1:  " << unknownShort1 << endl;
	out << "  Unknown Short 2:  " << unknownShort2 << endl;
	out << "  Unknown Short 3:  " << unknownShort3 << endl;
	out << "  Float 1:  " << float1 << endl;
	out << "  Float 2:  " << float2 << endl;
	out << "  Float 3:  " << float3 << endl;
	out << "  Float 4:  " << float4 << endl;
	out << "  Float 5:  " << float5 << endl;
	out << "  Byte 1:  " << byte1 << endl;
	out << "  Byte 2:  " << byte2 << endl;
	out << "  Byte 3:  " << byte3 << endl;
	out << "  Target(?)8:  " << target___8 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSProceduralLightningController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiFloatInterpController::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSProceduralLightningController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiFloatInterpController::GetRefs();
	return refs;
}

std::list<NiObject *> BSProceduralLightningController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiFloatInterpController::GetPtrs();
	return ptrs;
}

/***Begin Example Naive Implementation****

unsigned int BSProceduralLightningController::GetTarget___() const {
	return target___;
}

void BSProceduralLightningController::SetTarget___( unsigned int value ) {
	target___ = value;
}

unsigned int BSProceduralLightningController::GetTarget___1() const {
	return target___1;
}

void BSProceduralLightningController::SetTarget___1( unsigned int value ) {
	target___1 = value;
}

unsigned int BSProceduralLightningController::GetTarget___2() const {
	return target___2;
}

void BSProceduralLightningController::SetTarget___2( unsigned int value ) {
	target___2 = value;
}

unsigned int BSProceduralLightningController::GetTarget___3() const {
	return target___3;
}

void BSProceduralLightningController::SetTarget___3( unsigned int value ) {
	target___3 = value;
}

unsigned int BSProceduralLightningController::GetTarget___4() const {
	return target___4;
}

void BSProceduralLightningController::SetTarget___4( unsigned int value ) {
	target___4 = value;
}

unsigned int BSProceduralLightningController::GetTarget___5() const {
	return target___5;
}

void BSProceduralLightningController::SetTarget___5( unsigned int value ) {
	target___5 = value;
}

unsigned int BSProceduralLightningController::GetTarget___6() const {
	return target___6;
}

void BSProceduralLightningController::SetTarget___6( unsigned int value ) {
	target___6 = value;
}

unsigned int BSProceduralLightningController::GetTarget___7() const {
	return target___7;
}

void BSProceduralLightningController::SetTarget___7( unsigned int value ) {
	target___7 = value;
}

float BSProceduralLightningController::GetFloat1() const {
	return float1;
}

void BSProceduralLightningController::SetFloat1( float value ) {
	float1 = value;
}

float BSProceduralLightningController::GetFloat2() const {
	return float2;
}

void BSProceduralLightningController::SetFloat2( float value ) {
	float2 = value;
}

float BSProceduralLightningController::GetFloat3() const {
	return float3;
}

void BSProceduralLightningController::SetFloat3( float value ) {
	float3 = value;
}

float BSProceduralLightningController::GetFloat4() const {
	return float4;
}

void BSProceduralLightningController::SetFloat4( float value ) {
	float4 = value;
}

float BSProceduralLightningController::GetFloat5() const {
	return float5;
}

void BSProceduralLightningController::SetFloat5( float value ) {
	float5 = value;
}

byte BSProceduralLightningController::GetByte1() const {
	return byte1;
}

void BSProceduralLightningController::SetByte1( byte value ) {
	byte1 = value;
}

byte BSProceduralLightningController::GetByte2() const {
	return byte2;
}

void BSProceduralLightningController::SetByte2( byte value ) {
	byte2 = value;
}

byte BSProceduralLightningController::GetByte3() const {
	return byte3;
}

void BSProceduralLightningController::SetByte3( byte value ) {
	byte3 = value;
}

unsigned int BSProceduralLightningController::GetTarget___8() const {
	return target___8;
}

void BSProceduralLightningController::SetTarget___8( unsigned int value ) {
	target___8 = value;
}

****End Example Naive Implementation***/

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
