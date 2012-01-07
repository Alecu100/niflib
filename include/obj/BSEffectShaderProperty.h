/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BSEFFECTSHADERPROPERTY_H_
#define _BSEFFECTSHADERPROPERTY_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiProperty.h"
namespace Niflib {

class BSEffectShaderProperty;
typedef Ref<BSEffectShaderProperty> BSEffectShaderPropertyRef;

/*!  */
class BSEffectShaderProperty : public NiProperty {
public:
	/*! Constructor */
	NIFLIB_API BSEffectShaderProperty();

	/*! Destructor */
	NIFLIB_API virtual ~BSEffectShaderProperty();

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

	// Shader options, will use SkyrimEffectShaderFlags1
	// \return The current value.
	unsigned int GetEffectShaderFlags1() const;

	// Shader options, will use SkyrimEffectShaderFlags1
	// \param[in] value The new value.
	void SetEffectShaderFlags1( unsigned int value );

	// Offset UVs
	// \return The current value.
	TexCoord GetTextureTranslation1() const;

	// Offset UVs
	// \param[in] value The new value.
	void SetTextureTranslation1( const TexCoord & value );

	// Offset UV Scale to repeat tiling textures
	// \return The current value.
	TexCoord GetTextureRepeat() const;

	// Offset UV Scale to repeat tiling textures
	// \param[in] value The new value.
	void SetTextureRepeat( const TexCoord & value );

	// points to an external texture.
	// \return The current value.
	string GetSourceTexture() const;

	// points to an external texture.
	// \param[in] value The new value.
	void SetSourceTexture( const string & value );

	// hader options, will use SkyrimEffectShaderFlags12
	// \return The current value.
	unsigned short GetEffectShaderFlags2() const;

	// hader options, will use SkyrimEffectShaderFlags12
	// \param[in] value The new value.
	void SetEffectShaderFlags2( unsigned short value );

	// Color
	// \return The current value.
	Color3 GetDiffuseColor() const;

	// Color
	// \param[in] value The new value.
	void SetDiffuseColor( const Color3 & value );

	// The material's transparency
	// \return The current value.
	float GetAlpha() const;

	// The material's transparency
	// \param[in] value The new value.
	void SetAlpha( float value );

	// Adds a glow effect
	// \return The current value.
	float GetEmissive() const;

	// Adds a glow effect
	// \param[in] value The new value.
	void SetEmissive( float value );

	// points to an external texture.
	// \return The current value.
	string GetGradientTexture() const;

	// points to an external texture.
	// \param[in] value The new value.
	void SetGradientTexture( const string & value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
protected:
	/*! 8/16? (nope, also 122,atronachflame) */
	byte unknownByte1;
	/*!  */
	unsigned short unknownShort1;
	/*! always 80? */
	byte unknownByte2;
	/*! Shader options, will use SkyrimEffectShaderFlags1 */
	unsigned int effectShaderFlags1;
	/*! Offset UVs */
	TexCoord textureTranslation1;
	/*! Offset UV Scale to repeat tiling textures */
	TexCoord textureRepeat;
	/*! points to an external texture. */
	string sourceTexture;
	/*! hader options, will use SkyrimEffectShaderFlags12 */
	unsigned short effectShaderFlags2;
	/*! Unknown */
	unsigned short unknownShort2;
	/*! Unknown */
	float unknownFloat1;
	/*! Unknown */
	float unknownFloat2;
	/*! Unknown */
	float unknownFloat3;
	/*! Unknown */
	float unknownFloat4;
	/*! Color */
	Color3 diffuseColor;
	/*! The material's transparency */
	float alpha;
	/*! Adds a glow effect */
	float emissive;
	/*! Unknown */
	float unknownFloat5;
	/*! points to an external texture. */
	string gradientTexture;
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
