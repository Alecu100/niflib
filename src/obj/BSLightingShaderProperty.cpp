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
#include "../../include/obj/BSLightingShaderProperty.h"
#include "../../include/obj/BSShaderTextureSet.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSLightingShaderProperty::TYPE("BSLightingShaderProperty", &NiProperty::TYPE );

BSLightingShaderProperty::BSLightingShaderProperty() : shaderFlags1((unsigned int)2185233153), shaderFlags2((unsigned int)32801), textureTranslation1(0.0,0.0), textureRepeat(1.0,1.0), textureSet(NULL), emissiveColor(0.0,0.0,0.0), emissiveSaturation(1.0f), unknownInt7((unsigned int)3), alpha(1.0f), unknownFloat2(0.0f), glossiness(30.0f), specularColor(1.0,1.0,1.0), specularStrength(3.0f), lightingEffect1(0.4f), lightingEffect2(2.0f), environmentMapStrength(0.0f), unknownFloatSet1(1.0,1.0,1.0), unknownFloat9(0.0f), eyeCubemapScale(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSLightingShaderProperty::~BSLightingShaderProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSLightingShaderProperty::GetType() const {
	return TYPE;
}

NiObject * BSLightingShaderProperty::Create() {
	return new BSLightingShaderProperty;
}

void BSLightingShaderProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiProperty::Read( in, link_stack, info );
	if ( (info.userVersion == 12) ) {
		NifStream( shaderFlags1, in, info );
		NifStream( shaderFlags2, in, info );
	};
	NifStream( textureTranslation1, in, info );
	NifStream( textureRepeat, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( emissiveColor, in, info );
	NifStream( emissiveSaturation, in, info );
	NifStream( unknownInt7, in, info );
	NifStream( alpha, in, info );
	NifStream( unknownFloat2, in, info );
	NifStream( glossiness, in, info );
	NifStream( specularColor, in, info );
	NifStream( specularStrength, in, info );
	NifStream( lightingEffect1, in, info );
	NifStream( lightingEffect2, in, info );
	if ( (skyrimShaderType == 1) ) {
		NifStream( environmentMapStrength, in, info );
	};
	if ( (skyrimShaderType == 5) ) {
		NifStream( unknownFloatSet1, in, info );
	};
	if ( (skyrimShaderType == 6) ) {
		NifStream( unknownColor1, in, info );
	};
	if ( (skyrimShaderType == 7) ) {
		for (unsigned int i2 = 0; i2 < 2; i2++) {
			NifStream( unknownFloatSet3[i2], in, info );
		};
	};
	if ( (skyrimShaderType == 11) ) {
		NifStream( unknownFloat9, in, info );
		NifStream( unknownColor2, in, info );
	};
	if ( (skyrimShaderType == 14) ) {
		NifStream( unknownFloatSet5, in, info );
	};
	if ( (skyrimShaderType == 16) ) {
		NifStream( eyeCubemapScale, in, info );
		NifStream( leftEyeReflectionCenter, in, info );
		NifStream( rightEyeReflectionCenter, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSLightingShaderProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiProperty::Write( out, link_map, missing_link_stack, info );
	if ( (info.userVersion == 12) ) {
		NifStream( shaderFlags1, out, info );
		NifStream( shaderFlags2, out, info );
	};
	NifStream( textureTranslation1, out, info );
	NifStream( textureRepeat, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*textureSet), out );
	} else {
		if ( textureSet != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(textureSet) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( textureSet );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( emissiveColor, out, info );
	NifStream( emissiveSaturation, out, info );
	NifStream( unknownInt7, out, info );
	NifStream( alpha, out, info );
	NifStream( unknownFloat2, out, info );
	NifStream( glossiness, out, info );
	NifStream( specularColor, out, info );
	NifStream( specularStrength, out, info );
	NifStream( lightingEffect1, out, info );
	NifStream( lightingEffect2, out, info );
	if ( (skyrimShaderType == 1) ) {
		NifStream( environmentMapStrength, out, info );
	};
	if ( (skyrimShaderType == 5) ) {
		NifStream( unknownFloatSet1, out, info );
	};
	if ( (skyrimShaderType == 6) ) {
		NifStream( unknownColor1, out, info );
	};
	if ( (skyrimShaderType == 7) ) {
		for (unsigned int i2 = 0; i2 < 2; i2++) {
			NifStream( unknownFloatSet3[i2], out, info );
		};
	};
	if ( (skyrimShaderType == 11) ) {
		NifStream( unknownFloat9, out, info );
		NifStream( unknownColor2, out, info );
	};
	if ( (skyrimShaderType == 14) ) {
		NifStream( unknownFloatSet5, out, info );
	};
	if ( (skyrimShaderType == 16) ) {
		NifStream( eyeCubemapScale, out, info );
		NifStream( leftEyeReflectionCenter, out, info );
		NifStream( rightEyeReflectionCenter, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSLightingShaderProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiProperty::asString();
	out << "  Shader Flags 1:  " << shaderFlags1 << endl;
	out << "  Shader Flags 2:  " << shaderFlags2 << endl;
	out << "  Texture Translation 1:  " << textureTranslation1 << endl;
	out << "  Texture Repeat:  " << textureRepeat << endl;
	out << "  Texture Set:  " << textureSet << endl;
	out << "  Emissive Color:  " << emissiveColor << endl;
	out << "  Emissive Saturation:  " << emissiveSaturation << endl;
	out << "  Unknown Int 7:  " << unknownInt7 << endl;
	out << "  Alpha:  " << alpha << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Glossiness:  " << glossiness << endl;
	out << "  Specular Color:  " << specularColor << endl;
	out << "  Specular Strength:  " << specularStrength << endl;
	out << "  Lighting Effect 1:  " << lightingEffect1 << endl;
	out << "  Lighting Effect 2:  " << lightingEffect2 << endl;
	if ( (skyrimShaderType == 1) ) {
		out << "    Environment Map Strength:  " << environmentMapStrength << endl;
	};
	if ( (skyrimShaderType == 5) ) {
		out << "    Unknown Float Set 1:  " << unknownFloatSet1 << endl;
	};
	if ( (skyrimShaderType == 6) ) {
		out << "    Unknown Color 1:  " << unknownColor1 << endl;
	};
	if ( (skyrimShaderType == 7) ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < 2; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Float Set 3[" << i2 << "]:  " << unknownFloatSet3[i2] << endl;
			array_output_count++;
		};
	};
	if ( (skyrimShaderType == 11) ) {
		out << "    Unknown Float 9:  " << unknownFloat9 << endl;
		out << "    Unknown Color 2:  " << unknownColor2 << endl;
	};
	if ( (skyrimShaderType == 14) ) {
		out << "    Unknown Float Set 5:  " << unknownFloatSet5 << endl;
	};
	if ( (skyrimShaderType == 16) ) {
		out << "    Eye Cubemap Scale:  " << eyeCubemapScale << endl;
		out << "    Left Eye Reflection Center:  " << leftEyeReflectionCenter << endl;
		out << "    Right Eye Reflection Center:  " << rightEyeReflectionCenter << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSLightingShaderProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiProperty::FixLinks( objects, link_stack, missing_link_stack, info );
	textureSet = FixLink<BSShaderTextureSet>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSLightingShaderProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiProperty::GetRefs();
	if ( textureSet != NULL )
		refs.push_back(StaticCast<NiObject>(textureSet));
	return refs;
}

std::list<NiObject *> BSLightingShaderProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiProperty::GetPtrs();
	return ptrs;
}

/***Begin Example Naive Implementation****

unsigned int BSLightingShaderProperty::GetShaderFlags1() const {
	return shaderFlags1;
}

void BSLightingShaderProperty::SetShaderFlags1( unsigned int value ) {
	shaderFlags1 = value;
}

unsigned int BSLightingShaderProperty::GetShaderFlags2() const {
	return shaderFlags2;
}

void BSLightingShaderProperty::SetShaderFlags2( unsigned int value ) {
	shaderFlags2 = value;
}

TexCoord BSLightingShaderProperty::GetTextureTranslation1() const {
	return textureTranslation1;
}

void BSLightingShaderProperty::SetTextureTranslation1( const TexCoord & value ) {
	textureTranslation1 = value;
}

TexCoord BSLightingShaderProperty::GetTextureRepeat() const {
	return textureRepeat;
}

void BSLightingShaderProperty::SetTextureRepeat( const TexCoord & value ) {
	textureRepeat = value;
}

Ref<BSShaderTextureSet > BSLightingShaderProperty::GetTextureSet() const {
	return textureSet;
}

void BSLightingShaderProperty::SetTextureSet( Ref<BSShaderTextureSet > value ) {
	textureSet = value;
}

Color3 BSLightingShaderProperty::GetEmissiveColor() const {
	return emissiveColor;
}

void BSLightingShaderProperty::SetEmissiveColor( const Color3 & value ) {
	emissiveColor = value;
}

float BSLightingShaderProperty::GetEmissiveSaturation() const {
	return emissiveSaturation;
}

void BSLightingShaderProperty::SetEmissiveSaturation( float value ) {
	emissiveSaturation = value;
}

float BSLightingShaderProperty::GetAlpha() const {
	return alpha;
}

void BSLightingShaderProperty::SetAlpha( float value ) {
	alpha = value;
}

float BSLightingShaderProperty::GetGlossiness() const {
	return glossiness;
}

void BSLightingShaderProperty::SetGlossiness( float value ) {
	glossiness = value;
}

Color3 BSLightingShaderProperty::GetSpecularColor() const {
	return specularColor;
}

void BSLightingShaderProperty::SetSpecularColor( const Color3 & value ) {
	specularColor = value;
}

float BSLightingShaderProperty::GetSpecularStrength() const {
	return specularStrength;
}

void BSLightingShaderProperty::SetSpecularStrength( float value ) {
	specularStrength = value;
}

float BSLightingShaderProperty::GetLightingEffect1() const {
	return lightingEffect1;
}

void BSLightingShaderProperty::SetLightingEffect1( float value ) {
	lightingEffect1 = value;
}

float BSLightingShaderProperty::GetLightingEffect2() const {
	return lightingEffect2;
}

void BSLightingShaderProperty::SetLightingEffect2( float value ) {
	lightingEffect2 = value;
}

float BSLightingShaderProperty::GetEnvironmentMapStrength() const {
	return environmentMapStrength;
}

void BSLightingShaderProperty::SetEnvironmentMapStrength( float value ) {
	environmentMapStrength = value;
}

float BSLightingShaderProperty::GetEyeCubemapScale() const {
	return eyeCubemapScale;
}

void BSLightingShaderProperty::SetEyeCubemapScale( float value ) {
	eyeCubemapScale = value;
}

Vector3 BSLightingShaderProperty::GetLeftEyeReflectionCenter() const {
	return leftEyeReflectionCenter;
}

void BSLightingShaderProperty::SetLeftEyeReflectionCenter( const Vector3 & value ) {
	leftEyeReflectionCenter = value;
}

Vector3 BSLightingShaderProperty::GetRightEyeReflectionCenter() const {
	return rightEyeReflectionCenter;
}

void BSLightingShaderProperty::SetRightEyeReflectionCenter( const Vector3 & value ) {
	rightEyeReflectionCenter = value;
}

****End Example Naive Implementation***/

//--BEGIN MISC CUSTOM CODE--//
int BSLightingShaderProperty::GetSkyrimShaderType() const {
	return skyrimShaderType;
}

void BSLightingShaderProperty::SetSkyrimShaderType( int value ) {
	skyrimShaderType = value;
}

unsigned int BSLightingShaderProperty::GetShaderFlags1() const {
	return shaderFlags1;
}

void BSLightingShaderProperty::SetShaderFlags1( unsigned int value ) {
	shaderFlags1 = value;
}

unsigned int BSLightingShaderProperty::GetShaderFlags2() const {
	return shaderFlags2;
}

void BSLightingShaderProperty::SetShaderFlags2( unsigned int value ) {
	shaderFlags2 = value;
}

TexCoord BSLightingShaderProperty::GetTextureTranslation1() const {
	return textureTranslation1;
}

void BSLightingShaderProperty::SetTextureTranslation1( const TexCoord & value ) {
	textureTranslation1 = value;
}

TexCoord BSLightingShaderProperty::GetTextureRepeat() const {
	return textureRepeat;
}

void BSLightingShaderProperty::SetTextureRepeat( const TexCoord & value ) {
	textureRepeat = value;
}

Ref<BSShaderTextureSet > BSLightingShaderProperty::GetTextureSet() const {
	return textureSet;
}

void BSLightingShaderProperty::SetTextureSet( Ref<BSShaderTextureSet > value ) {
	textureSet = value;
}

Color3 BSLightingShaderProperty::GetEmissiveColor() const {
	return emissiveColor;
}

void BSLightingShaderProperty::SetEmissiveColor( const Color3 & value ) {
	emissiveColor = value;
}

float BSLightingShaderProperty::GetEmissiveSaturation() const {
	return emissiveSaturation;
}

void BSLightingShaderProperty::SetEmissiveSaturation( float value ) {
	emissiveSaturation = value;
}

float BSLightingShaderProperty::GetAlpha() const {
	return alpha;
}

void BSLightingShaderProperty::SetAlpha( float value ) {
	alpha = value;
}

float BSLightingShaderProperty::GetGlossiness() const {
	return glossiness;
}

void BSLightingShaderProperty::SetGlossiness( float value ) {
	glossiness = value;
}

Color3 BSLightingShaderProperty::GetSpecularColor() const {
	return specularColor;
}

void BSLightingShaderProperty::SetSpecularColor( const Color3 & value ) {
	specularColor = value;
}

float BSLightingShaderProperty::GetSpecularStrength() const {
	return specularStrength;
}

void BSLightingShaderProperty::SetSpecularStrength( float value ) {
	specularStrength = value;
}

float BSLightingShaderProperty::GetLightingEffect1() const {
	return lightingEffect1;
}

void BSLightingShaderProperty::SetLightingEffect1( float value ) {
	lightingEffect1 = value;
}

float BSLightingShaderProperty::GetLightingEffect2() const {
	return lightingEffect2;
}

void BSLightingShaderProperty::SetLightingEffect2( float value ) {
	lightingEffect2 = value;
}

float BSLightingShaderProperty::GetEnvironmentMapStrength() const {
	return environmentMapStrength;
}

void BSLightingShaderProperty::SetEnvironmentMapStrength( float value ) {
	environmentMapStrength = value;
}

float BSLightingShaderProperty::GetEyeCubemapScale() const {
	return eyeCubemapScale;
}

void BSLightingShaderProperty::SetEyeCubemapScale( float value ) {
	eyeCubemapScale = value;
}

Vector3 BSLightingShaderProperty::GetLeftEyeReflectionCenter() const {
	return leftEyeReflectionCenter;
}

void BSLightingShaderProperty::SetLeftEyeReflectionCenter( const Vector3 & value ) {
	leftEyeReflectionCenter = value;
}

Vector3 BSLightingShaderProperty::GetRightEyeReflectionCenter() const {
	return rightEyeReflectionCenter;
}

void BSLightingShaderProperty::SetRightEyeReflectionCenter( const Vector3 & value ) {
	rightEyeReflectionCenter = value;
}

//--END CUSTOM CODE--//
