/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include <obj/BSSkin__BoneData.h>
#include <obj/BSSkin__Instance.h>
#include <obj/NiNode.h>
#include "../../include/nif_math.h"
#include <vector>
#include <algorithm>

typedef pair<Niflib::NiNodeRef, float> BoneWeight;
typedef  pair<int, vector<BoneWeight>> VertexWeights;

struct BoneWeightComparer
{
	bool operator() (const BoneWeight& struct1, const BoneWeight& struct2)
	{
		return (struct1.second < struct2.second);
	}
};

//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/BSTriShape.h"
#include "../../include/gen/SphereBV.h"
#include "../../include/gen/BSVertexData.h"
#include "../../include/gen/HalfVector3.h"
#include "../../include/gen/HalfTexCoord.h"
#include "../../include/gen/ByteVector3.h"
#include "../../include/gen/ByteVector3.h"
#include "../../include/gen/ByteColor4.h"
#include "../../include/obj/NiObject.h"
#include "../../include/obj/NiProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSTriShape::TYPE("BSTriShape", &BSShape::TYPE );

BSTriShape::BSTriShape() : skin(NULL), numTriangles((unsigned int)0), numVertices((unsigned short)0), dataSize((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

BSTriShape::~BSTriShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & BSTriShape::GetType() const {
	return TYPE;
}

NiObject * BSTriShape::Create() {
	return new BSTriShape;
}

void BSTriShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	BSShape::Read( in, link_stack, info );
	NifStream( bound.center, in, info );
	NifStream( bound.radius, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( vertexFlags[i1], in, info );
	};
	NifStream( numTriangles, in, info );
	NifStream( numVertices, in, info );
	NifStream( dataSize, in, info );
	if ( (dataSize > 0) ) {
		vertexData.resize(numVertices);
		for (unsigned int i2 = 0; i2 < vertexData.size(); i2++) {
			if ( (!(vertexFlags[6] & 64)) ) {
				NifStream( vertexData[i2].vertex.x, in, info );
				NifStream( vertexData[i2].vertex.y, in, info );
				NifStream( vertexData[i2].vertex.z, in, info );
			};
			if ( ((!(vertexFlags[6] & 64)) && ((vertexFlags[5] & 128) && (vertexFlags[2] & 64))) ) {
				NifStream( vertexData[i2].bitangentX, in, info );
			};
			if ( ((!(vertexFlags[6] & 64)) && (!((vertexFlags[5] & 128) && (vertexFlags[2] & 64)))) ) {
				NifStream( vertexData[i2].unknownShort1, in, info );
			};
			if ( (vertexFlags[6] & 64) ) {
				NifStream( vertexData[i2].vertex2, in, info );
				NifStream( vertexData[i2].bitangentX2, in, info );
			};
			if ( (vertexFlags[5] & 32) ) {
				NifStream( vertexData[i2].uv.u, in, info );
				NifStream( vertexData[i2].uv.v, in, info );
			};
			if ( (vertexFlags[5] & 128) ) {
				NifStream( vertexData[i2].normal.x, in, info );
				NifStream( vertexData[i2].normal.y, in, info );
				NifStream( vertexData[i2].normal.z, in, info );
				NifStream( vertexData[i2].bitangentY, in, info );
			};
			if ( (vertexFlags[2] & 64) ) {
				NifStream( vertexData[i2].tangent.x, in, info );
				NifStream( vertexData[i2].tangent.y, in, info );
				NifStream( vertexData[i2].tangent.z, in, info );
				NifStream( vertexData[i2].bitangentZ, in, info );
			};
			if ( (vertexFlags[6] & 2) ) {
				NifStream( vertexData[i2].vertexColors.r, in, info );
				NifStream( vertexData[i2].vertexColors.g, in, info );
				NifStream( vertexData[i2].vertexColors.b, in, info );
				NifStream( vertexData[i2].vertexColors.a, in, info );
			};
			if ( (vertexFlags[6] & 4) ) {
				for (unsigned int i4 = 0; i4 < 4; i4++) {
					NifStream( vertexData[i2].boneWeights[i4], in, info );
				};
				for (unsigned int i4 = 0; i4 < 4; i4++) {
					NifStream( vertexData[i2].boneIndices[i4], in, info );
				};
			};
			if ( (vertexFlags[6] & 16) ) {
				NifStream( vertexData[i2].unknownInt2, in, info );
			};
		};
		triangles.resize(numTriangles);
		for (unsigned int i2 = 0; i2 < triangles.size(); i2++) {
			NifStream( triangles[i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	for (unsigned int i2 = 0; i2 < vertexData.size(); i2++) {
		BSVertexData& vd = vertexData[i2];
		if (vertexFlags[6] & 64) {
			vd.vertex.x = ConvertFloatToHFloat(vd.vertex2.x);
			vd.vertex.y = ConvertFloatToHFloat(vd.vertex2.y);
			vd.vertex.z = ConvertFloatToHFloat(vd.vertex2.z);
			vd.bitangentX = ConvertFloatToHFloat(vd.bitangentX2);
		} else {
			vd.vertex2.x = ConvertHFloatToFloat(vd.vertex.x);
			vd.vertex2.y = ConvertHFloatToFloat(vd.vertex.y);
			vd.vertex2.z = ConvertHFloatToFloat(vd.vertex.z);
			vd.bitangentX2 = ConvertHFloatToFloat(vd.bitangentX);
		}
	}
	//--END CUSTOM CODE--//
}

void BSTriShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	BSShape::Write( out, link_map, missing_link_stack, info );
	dataSize = dataSizeCalc(info);
	numVertices = (unsigned short)(vertexData.size());
	numTriangles = (unsigned int)(triangles.size());
	NifStream( bound.center, out, info );
	NifStream( bound.radius, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*skin), out );
	} else {
		if ( skin != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(skin) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( skin );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*bsProperties[i1]), out );
		} else {
			if ( bsProperties[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(bsProperties[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( bsProperties[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( vertexFlags[i1], out, info );
	};
	NifStream( numTriangles, out, info );
	NifStream( numVertices, out, info );
	NifStream( dataSize, out, info );
	if ( (dataSize > 0) ) {
		for (unsigned int i2 = 0; i2 < vertexData.size(); i2++) {
			if ( (!(vertexFlags[6] & 64)) ) {
				NifStream( vertexData[i2].vertex.x, out, info );
				NifStream( vertexData[i2].vertex.y, out, info );
				NifStream( vertexData[i2].vertex.z, out, info );
			};
			if ( ((!(vertexFlags[6] & 64)) && ((vertexFlags[5] & 128) && (vertexFlags[2] & 64))) ) {
				NifStream( vertexData[i2].bitangentX, out, info );
			};
			if ( ((!(vertexFlags[6] & 64)) && (!((vertexFlags[5] & 128) && (vertexFlags[2] & 64)))) ) {
				NifStream( vertexData[i2].unknownShort1, out, info );
			};
			if ( (vertexFlags[6] & 64) ) {
				NifStream( vertexData[i2].vertex2, out, info );
				NifStream( vertexData[i2].bitangentX2, out, info );
			};
			if ( (vertexFlags[5] & 32) ) {
				NifStream( vertexData[i2].uv.u, out, info );
				NifStream( vertexData[i2].uv.v, out, info );
			};
			if ( (vertexFlags[5] & 128) ) {
				NifStream( vertexData[i2].normal.x, out, info );
				NifStream( vertexData[i2].normal.y, out, info );
				NifStream( vertexData[i2].normal.z, out, info );
				NifStream( vertexData[i2].bitangentY, out, info );
			};
			if ( (vertexFlags[2] & 64) ) {
				NifStream( vertexData[i2].tangent.x, out, info );
				NifStream( vertexData[i2].tangent.y, out, info );
				NifStream( vertexData[i2].tangent.z, out, info );
				NifStream( vertexData[i2].bitangentZ, out, info );
			};
			if ( (vertexFlags[6] & 2) ) {
				NifStream( vertexData[i2].vertexColors.r, out, info );
				NifStream( vertexData[i2].vertexColors.g, out, info );
				NifStream( vertexData[i2].vertexColors.b, out, info );
				NifStream( vertexData[i2].vertexColors.a, out, info );
			};
			if ( (vertexFlags[6] & 4) ) {
				for (unsigned int i4 = 0; i4 < 4; i4++) {
					NifStream( vertexData[i2].boneWeights[i4], out, info );
				};
				for (unsigned int i4 = 0; i4 < 4; i4++) {
					NifStream( vertexData[i2].boneIndices[i4], out, info );
				};
			};
			if ( (vertexFlags[6] & 16) ) {
				NifStream( vertexData[i2].unknownInt2, out, info );
			};
		};
		for (unsigned int i2 = 0; i2 < triangles.size(); i2++) {
			NifStream( triangles[i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string BSTriShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << BSShape::asString();
	numVertices = (unsigned short)(vertexData.size());
	numTriangles = (unsigned int)(triangles.size());
	out << "  Center:  " << bound.center << endl;
	out << "  Radius:  " << bound.radius << endl;
	out << "  Skin:  " << skin << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    BS Properties[" << i1 << "]:  " << bsProperties[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Vertex Flags[" << i1 << "]:  " << vertexFlags[i1] << endl;
		array_output_count++;
	};
	out << "  Num Triangles:  " << numTriangles << endl;
	out << "  Num Vertices:  " << numVertices << endl;
	out << "  Data Size:  " << dataSize << endl;
	if ( (dataSize > 0) ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < vertexData.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( (!(vertexFlags[6] & 64)) ) {
				out << "        x:  " << vertexData[i2].vertex.x << endl;
				out << "        y:  " << vertexData[i2].vertex.y << endl;
				out << "        z:  " << vertexData[i2].vertex.z << endl;
			};
			if ( ((!(vertexFlags[6] & 64)) && ((vertexFlags[5] & 128) && (vertexFlags[2] & 64))) ) {
				out << "        Bitangent x:  " << vertexData[i2].bitangentX << endl;
			};
			if ( ((!(vertexFlags[6] & 64)) && (!((vertexFlags[5] & 128) && (vertexFlags[2] & 64)))) ) {
				out << "        Unknown Short 1:  " << vertexData[i2].unknownShort1 << endl;
			};
			if ( (vertexFlags[6] & 64) ) {
				out << "        Vertex 2:  " << vertexData[i2].vertex2 << endl;
				out << "        Bitangent x 2:  " << vertexData[i2].bitangentX2 << endl;
			};
			if ( (vertexFlags[5] & 32) ) {
				out << "        u:  " << vertexData[i2].uv.u << endl;
				out << "        v:  " << vertexData[i2].uv.v << endl;
			};
			if ( (vertexFlags[5] & 128) ) {
				out << "        x:  " << vertexData[i2].normal.x << endl;
				out << "        y:  " << vertexData[i2].normal.y << endl;
				out << "        z:  " << vertexData[i2].normal.z << endl;
				out << "        Bitangent y:  " << vertexData[i2].bitangentY << endl;
			};
			if ( (vertexFlags[2] & 64) ) {
				out << "        x:  " << vertexData[i2].tangent.x << endl;
				out << "        y:  " << vertexData[i2].tangent.y << endl;
				out << "        z:  " << vertexData[i2].tangent.z << endl;
				out << "        Bitangent z:  " << vertexData[i2].bitangentZ << endl;
			};
			if ( (vertexFlags[6] & 2) ) {
				out << "        r:  " << vertexData[i2].vertexColors.r << endl;
				out << "        g:  " << vertexData[i2].vertexColors.g << endl;
				out << "        b:  " << vertexData[i2].vertexColors.b << endl;
				out << "        a:  " << vertexData[i2].vertexColors.a << endl;
			};
			if ( (vertexFlags[6] & 4) ) {
				array_output_count = 0;
				for (unsigned int i4 = 0; i4 < 4; i4++) {
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
						break;
					};
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						break;
					};
					out << "          Bone Weights[" << i4 << "]:  " << vertexData[i2].boneWeights[i4] << endl;
					array_output_count++;
				};
				array_output_count = 0;
				for (unsigned int i4 = 0; i4 < 4; i4++) {
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
						break;
					};
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						break;
					};
					out << "          Bone Indices[" << i4 << "]:  " << vertexData[i2].boneIndices[i4] << endl;
					array_output_count++;
				};
			};
			if ( (vertexFlags[6] & 16) ) {
				out << "        Unknown Int 2:  " << vertexData[i2].unknownInt2 << endl;
			};
		};
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < triangles.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Triangles[" << i2 << "]:  " << triangles[i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void BSTriShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	BSShape::FixLinks( objects, link_stack, missing_link_stack, info );
	skin = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		bsProperties[i1] = FixLink<NiProperty>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	// add propertylink1 and propertylink2 to properties so GetProperties continues to function
	if (bsProperties[0] != NULL)
		properties.push_back(bsProperties[0]);
	if (bsProperties[1] != NULL)
		properties.push_back(bsProperties[1]);

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSTriShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = BSShape::GetRefs();
	if ( skin != NULL )
		refs.push_back(StaticCast<NiObject>(skin));
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( bsProperties[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(bsProperties[i1]));
	};
	return refs;
}

std::list<NiObject *> BSTriShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = BSShape::GetPtrs();
	for (unsigned int i1 = 0; i1 < 2; i1++) {
	};
	return ptrs;
}

/***Begin Example Naive Implementation****

SphereBV BSTriShape::GetBound() const {
	return bound;
}

void BSTriShape::SetBound( const SphereBV & value ) {
	bound = value;
}

Ref<NiObject > BSTriShape::GetSkin() const {
	return skin;
}

void BSTriShape::SetSkin( Ref<NiObject > value ) {
	skin = value;
}

array<2,Ref<NiProperty > >  BSTriShape::GetBsProperties() const {
	return bsProperties;
}

void BSTriShape::SetBsProperties( const array<2,Ref<NiProperty > >&  value ) {
	bsProperties = value;
}

array<8,byte >  BSTriShape::GetVertexFlags() const {
	return vertexFlags;
}

void BSTriShape::SetVertexFlags( const array<8,byte >&  value ) {
	vertexFlags = value;
}

unsigned int BSTriShape::GetDataSize() const {
	return dataSize;
}

void BSTriShape::SetDataSize( unsigned int value ) {
	dataSize = value;
}

vector<BSVertexData > BSTriShape::GetVertexData() const {
	return vertexData;
}

void BSTriShape::SetVertexData( const vector<BSVertexData >& value ) {
	vertexData = value;
}

vector<Triangle > BSTriShape::GetTriangles() const {
	return triangles;
}

void BSTriShape::SetTriangles( const vector<Triangle >& value ) {
	triangles = value;
}

****End Example Naive Implementation***/

//--BEGIN MISC CUSTOM CODE--//


int BSTriShape::dataSizeCalc(const NifInfo & info) const
{
	BSVertexData *ptr = nullptr;
	size_t size = triangles.size() * sizeof(Triangle);
	size_t dataSize = 0;
	if (vertexFlags[6] & 0x40)
		dataSize += sizeof(ptr->vertex2) + sizeof(ptr->bitangentX2);
	else		
		dataSize += sizeof(ptr->vertex) + sizeof(ptr->bitangentX);
	if ((vertexFlags[5] & 32)) {
		dataSize += sizeof(ptr->uv);
	};
	if ((vertexFlags[5] & 128)) {
		dataSize += sizeof(ptr->normal);
		dataSize += sizeof(ptr->bitangentY);
	};
	if ((vertexFlags[2] & 64)) {
		dataSize += sizeof(ptr->tangent);
		dataSize += sizeof(ptr->bitangentZ);
	};
	if ((vertexFlags[6] & 2)) {
		dataSize += sizeof(ptr->vertexColors);
	};
	if ((vertexFlags[6] & 4)) {
		dataSize += sizeof(hfloat)*4 + sizeof(byte)*4;
	};
	if ((vertexFlags[6] & 16)) {
		dataSize += sizeof(ptr->unknownInt2);
	};
	size += dataSize * vertexData.size();
	return int(size);
}

#pragma region Property Management
// Synchronize PropertyLink 1 and Property Link 2 with Property List

void BSTriShape::AddProperty(NiProperty * obj) {
	if (obj == NULL)
		return;

	properties.push_back(obj);
	if (bsProperties[0] == NULL)
	{
		bsProperties[0] = obj;
		return;
	}
	if (bsProperties[1] == NULL)
	{
		bsProperties[1] = obj;
		return;
	}
}

void BSTriShape::RemoveProperty(NiProperty * obj) {
	//Search property list for the one to remove
	for (vector< NiPropertyRef >::iterator it = properties.begin(); it != properties.end(); ) {
		if (*it == obj) {
			it = properties.erase(it);
		}
		else {
			++it;
		}
	}
	if (bsProperties[0] == obj)
		bsProperties[0] = NULL;
	if (bsProperties[1] == obj)
		bsProperties[1] = NULL;
	if (bsProperties[0] == NULL && bsProperties[1] != NULL)
	{
		bsProperties[0] = bsProperties[1];
		bsProperties[1] = NULL;
	}
}

void BSTriShape::ClearProperties() {
	properties.clear();
	bsProperties[0] = NULL;
	bsProperties[1] = NULL;
}


NiPropertyRef BSTriShape::GetBSProperty(int index) const {
	return bsProperties[index];
}

void BSTriShape::SetBSProperty(int index, const NiPropertyRef&  value) {
	bsProperties[index] = value;
}

#pragma endregion

int BSTriShape::GetVertexCount() const {
	return int(vertexData.size());
}

Vector3 BSTriShape::GetCenter() const
{
	return Vector3();
}

float BSTriShape::GetRadius() const
{
	return 1.0f;
}

vector<Vector3> BSTriShape::GetVertices() const {
	vector<Vector3> vertices;
	vertices.reserve(vertexData.size());
	for (vector<BSVertexData>::const_iterator itr = vertexData.begin(); itr != vertexData.end(); ++itr)	{
		vertices.push_back(Vector3(ConvertHFloatToFloat(itr->vertex.x),
			ConvertHFloatToFloat(itr->vertex.y), ConvertHFloatToFloat(itr->vertex.z)));
	}
	return vertices;
}

vector<Vector3> BSTriShape::GetNormals() const {
	vector<Vector3> normals;
	normals.reserve(vertexData.size());
	for (vector<BSVertexData>::const_iterator itr = vertexData.begin(); itr != vertexData.end(); ++itr) {
		normals.push_back(Vector3(ConvertByteToFloat(itr->normal.x),
			ConvertByteToFloat(itr->normal.y), ConvertByteToFloat(itr->normal.z)));
	}
	return normals;
}

bool BSTriShape::HasColors() const {
	return (vertexFlags[5] & 0x20) != 0;
}

vector<Color4> BSTriShape::GetColors() const {
	vector<Color4> vertexColors;
	vertexColors.reserve(vertexData.size());
	for (vector<BSVertexData>::const_iterator itr = vertexData.begin(); itr != vertexData.end(); ++itr) {
		vertexColors.push_back(Color4(ConvertByteToFloat(itr->vertexColors.r), ConvertByteToFloat(itr->vertexColors.b),
			ConvertByteToFloat(itr->vertexColors.g), ConvertByteToFloat(itr->vertexColors.a)));
	}
	return vertexColors;
}

vector<TexCoord> BSTriShape::GetUVSet() const {
	vector<TexCoord> tcs;
	tcs.reserve(vertexData.size());
	for (vector<BSVertexData>::const_iterator itr = vertexData.begin(); itr != vertexData.end(); ++itr) {
		tcs.push_back(TexCoord(ConvertHFloatToFloat(itr->uv.u),ConvertHFloatToFloat(itr->uv.v)));
	}
	return tcs;
}

bool BSTriShape::HasNormals() const {
	return (vertexFlags[5] & 0x80) != 0;
}

bool BSTriShape::HasTangentSpace() const {
	return (vertexFlags[2] & 0x40) != 0;
}


vector<Vector3> BSTriShape::GetBitangents() const
{
	vector<Vector3> bt;
	return bt;
}

vector<Vector3> BSTriShape::GetTangents() const
{
	vector<Vector3> tangents;
	tangents.reserve(vertexData.size());
	for (vector<BSVertexData>::const_iterator itr = vertexData.begin(); itr != vertexData.end(); ++itr) {
		tangents.push_back(Vector3(ConvertByteToFloat(itr->tangent.x), ConvertByteToFloat(itr->tangent.y),
			ConvertByteToFloat(itr->tangent.z)));
	}
	return tangents;
}

// Do we have bone weights?
// \return Whether skinning data is present
bool BSTriShape::HasSkin() const {
	return (vertexFlags[6] & 0x04) != 0;
}

Ref<NiObject > BSTriShape::GetSkin() const {
	return skin;
}

void BSTriShape::SetSkin(Ref<NiObject > value) {
	skin = value;
}

SphereBV BSTriShape::GetBounds() const {
	return bound;
}

void BSTriShape::SetBounds(const SphereBV & value) {
	bound = value;
}

int BSTriShape::GetBoneWeights(unsigned int vertexIdx, float weights[4], int bones[4]) const {
	if (vertexIdx < 0 || vertexIdx >= vertexData.size()) return 0;
	const auto& vert = vertexData[vertexIdx];
	for (int i = 0; i < 4; ++i )
	{
		if (vert.boneIndices[i] == 0 && vert.boneWeights[i] == 0) return i;
		bones[i] = vert.boneIndices[i];
		weights[i] = ConvertHFloatToFloat(vert.boneWeights[i]);
	}
	return 4;
}

// Unknown.
// \return The current value.
const vector<BSVertexData>& BSTriShape::GetVertexData() const {
	return vertexData;
}

// Unknown.
// \param[in] value The new value.
void BSTriShape::SetVertexData(const vector<BSVertexData >& value) {
	vertexData = value;
}

// Unknown.
// \return The current value.
const vector<Triangle>& BSTriShape::GetTriangles() const {
	return triangles;
}

// Unknown.
// \param[in] value The new value.
void BSTriShape::SetTriangles(const vector<Triangle >& value) {
	triangles = value;
}

void BSTriShape::SetVertexFlags(bool uv, bool vc, bool normal, bool tangent, bool skin, bool fullfloat)
{
	// sorted by usage frequency in the Fallout 4
	typedef union { char flags[8]; unsigned long long ull; } VFlags;
	VFlags flags[] = {
		{ 0x05, 0x02, 0x43, 0x00, 0x00, 0xb0, 0x01, 0x00 },
		{ 0x06, 0x02, 0x43, 0x05, 0x00, 0xb0, 0x03, 0x00 },
		{ 0x03, 0x02, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00 },
		{ 0x08, 0x02, 0x43, 0x50, 0x20, 0xb0, 0x05, 0x00 },
		{ 0x09, 0x02, 0x43, 0x65, 0x20, 0xb0, 0x07, 0x00 },
		{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00 },
		{ 0x08, 0x02, 0x43, 0x50, 0x00, 0xb0, 0x05, 0x00 },
		{ 0x09, 0x02, 0x43, 0x65, 0x00, 0xb0, 0x07, 0x00 },
		{ 0x03, 0x00, 0x02, 0x00, 0x00, 0x90, 0x00, 0x00 },
		{ 0x0a, 0x02, 0x43, 0x65, 0x90, 0xb0, 0x17, 0x00 },
		{ 0x04, 0x00, 0x02, 0x03, 0x00, 0x90, 0x02, 0x00 },
		{ 0x07, 0x02, 0x00, 0x43, 0x00, 0x30, 0x06, 0x00 },
		{ 0x06, 0x02, 0x00, 0x30, 0x00, 0x30, 0x04, 0x00 },
		{ 0x04, 0x02, 0x03, 0x00, 0x00, 0xb0, 0x00, 0x00 },
		{ 0x04, 0x02, 0x00, 0x03, 0x00, 0x30, 0x02, 0x00 },
		{ 0x05, 0x02, 0x03, 0x04, 0x00, 0xb0, 0x02, 0x00 },
		{ 0x08, 0x04, 0x65, 0x07, 0x00, 0xb0, 0x43, 0x00 },
		{ 0x07, 0x04, 0x65, 0x00, 0x00, 0xb0, 0x41, 0x00 },
		{ 0x0b, 0x04, 0x65, 0x87, 0x00, 0xb0, 0x47, 0x00 },
		{ 0x0a, 0x04, 0x65, 0x70, 0x00, 0xb0, 0x45, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	};
	VFlags mask;
	mask.ull = 0UL;
	if (fullfloat) mask.flags[6] |= 0x40;
	if (uv) mask.flags[5] |= 0x20;
	if (normal) mask.flags[5] |= 0x80;
	if (tangent) mask.flags[2] |= 0x40;
	if (skin) mask.flags[6] |= 0x04;
	if (vc) mask.flags[6] |= 0x02;
	for (int i = 0; i < _countof(flags); ++i)
	{
		if ((mask.ull & flags[i].ull) == mask.ull) {
			memcpy(&vertexFlags[0], flags[i].flags, sizeof(VFlags));
			break;
		}
	}
	//if (unk10) mask.flags[6] |= 0x10;
}

// Calculate bounding sphere using minimum-volume axis-align bounding box.  Its fast but not a very good fit.
static void CalcAxisAlignedBox(const vector<SkinWeight> & n, const vector<Vector3>& vertices, Vector3& center, float& radius)
{
	//--Calculate center & radius--//

	//Set lows and highs to first vertex
	Vector3 lows = vertices[n[0].index];
	Vector3 highs = vertices[n[0].index];

	//Iterate through the vertices, adjusting the stored values
	//if a vertex with lower or higher values is found
	for (unsigned int i = 0; i < n.size(); ++i) {
		const Vector3 & v = vertices[n[i].index];

		if (v.x > highs.x) highs.x = v.x;
		else if (v.x < lows.x) lows.x = v.x;

		if (v.y > highs.y) highs.y = v.y;
		else if (v.y < lows.y) lows.y = v.y;

		if (v.z > highs.z) highs.z = v.z;
		else if (v.z < lows.z) lows.z = v.z;
	}

	//Now we know the extent of the shape, so the center will be the average
	//of the lows and highs
	center = (highs + lows) / 2.0f;

	//The radius will be the largest distance from the center
	Vector3 diff;
	float dist2(0.0f), maxdist2(0.0f);
	for (unsigned int i = 0; i < n.size(); ++i) {
		const Vector3 & v = vertices[n[i].index];

		diff = center - v;
		dist2 = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
		if (dist2 > maxdist2) maxdist2 = dist2;
	};
	radius = sqrt(maxdist2);
}

void BSTriShape::GenSkinData(const map<Ref<NiNode>, vector<SkinWeight>>& shape_weights)
{
	BSSkin__BoneDataRef bone_data = new BSSkin__BoneData;
	BSSkin__InstanceRef skin_instance = new BSSkin__Instance;
	skin_instance->SetBoneData(bone_data);

	this->SetSkin(DynamicCast<NiObject>(skin_instance));

	map<int, VertexWeights> vertex_weights;
	map<int, VertexWeights> vertex_weights_4weights;
	map<NiNodeRef, int> used_bones_indices;
	vector<NiNodeRef> used_bones;

	for (int vertex_index = 0; vertex_index < vertexData.size(); vertex_index++)
	{
		VertexWeights vertex_weight(vertex_index, vector<BoneWeight>());
		vertex_weights[vertex_index] = vertex_weight;

		VertexWeights vertex_weight2(vertex_index, vector<BoneWeight>());
		vertex_weights_4weights[vertex_index] = vertex_weight2;
	}

	for (map<Ref<NiNode>, vector<SkinWeight>>::const_iterator iterator = shape_weights.begin(); iterator != shape_weights.end(); ++iterator)
	{
		for (int vertex_weight_index = 0; vertex_weight_index < iterator->second.size(); vertex_weight_index++)
		{
			BoneWeight weight(iterator->first, iterator->second[vertex_weight_index].weight);

			vertex_weights[iterator->second[vertex_weight_index].index].second.push_back(weight);
		}
	}

	for (map<int, VertexWeights>::const_iterator iterator = vertex_weights.begin(); iterator != vertex_weights.end(); ++iterator)
	{
		vector<BoneWeight> sorted_weights = iterator->second.second;

		sort(sorted_weights.begin(), sorted_weights.end(), BoneWeightComparer());

		for (int weight_index = 0; weight_index < sorted_weights.size() && weight_index < 4; weight_index++)
		{
			vertex_weights_4weights[iterator->first].second.push_back(sorted_weights[weight_index]);
		}
	}

	for (int vertex_index = 0; vertex_index < vertexData.size(); vertex_index++)
	{
		vertexData[vertex_index].SetBoneWeight(0, 0, 0);
		vertexData[vertex_index].SetBoneWeight(1, 0, 0);
		vertexData[vertex_index].SetBoneWeight(2, 0, 0);
		vertexData[vertex_index].SetBoneWeight(3, 0, 0);
	}

	vector<Vector3> vertices = this->GetVertices();
	Vector3 center;
	float radius;
	vector<BSSkinBoneTrans> bone_transforms;

	int bone_index = 0;
	for (map<Ref<NiNode>, vector<SkinWeight>>::const_iterator iterator = shape_weights.begin(); iterator != shape_weights.end(); ++iterator, bone_index++)
	{
		bool is_used = false;
		NiNodeRef current_bone = iterator->first;

		for (int vertex_index = 0; vertex_index < vertex_weights_4weights.size(); vertex_index++)
		{
			for (int weight_index = 0; weight_index < vertex_weights_4weights[vertex_index].second.size(); weight_index++)
			{
				if (vertex_weights_4weights[vertex_index].second[weight_index].first == current_bone)
				{
					is_used = true;
					break;
				}
			}

			if (is_used)
			{
				break;
			}
		}

		if (is_used)
		{
			used_bones_indices[current_bone] = bone_index;
			used_bones.push_back(current_bone);

			CalcAxisAlignedBox(iterator->second, vertices, center, radius);

			BSSkinBoneTrans current_bone_transform;
			current_bone_transform.scale = 1;
			current_bone_transform.rotation = Matrix33::IDENTITY;
			current_bone_transform.translation = Vector3(0,0,0);
			current_bone_transform.SetBoundingSphere(center, radius);
			bone_transforms.push_back(current_bone_transform);

			bone_index++;
		}
	}

	bone_data->SetBoneTransforms(bone_transforms);
	skin_instance->SetBones(used_bones);

	for (int vertex_index = 0; vertex_index < vertex_weights_4weights.size(); vertex_index++)
	{
		for (int weight_index = 0; weight_index < vertex_weights_4weights[vertex_index].second.size(); weight_index++)
		{
			NiNodeRef current_bone = vertex_weights_4weights[vertex_index].second[weight_index].first;
			float current_weight = vertex_weights_4weights[vertex_index].second[weight_index].second;
			int current_bone_index = used_bones_indices[current_bone];

			vertexData[vertex_index].SetBoneWeight(weight_index, current_bone_index, current_weight);
		}
	}
}



bool BSTriShape::IsSkin() {
	return HasSkin();
}




//--END CUSTOM CODE--//
