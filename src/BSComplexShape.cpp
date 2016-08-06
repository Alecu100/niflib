/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#include "../include/BSComplexShape.h"
#include "../include/obj/NiNode.h"
#include "../include/obj/NiProperty.h"
#include "../include/obj/NiAVObject.h"
#include "../include/obj/NiTriBasedGeom.h"
#include "../include/obj/NiTriShape.h"
#include "../include/obj/NiTriStrips.h"
#include "../include/obj/NiTriStripsData.h"
#include "../include/obj/NiTriShapeData.h"
#include "../include/obj/NiTexturingProperty.h"
#include "../include/obj/NiSkinInstance.h"
#include "../include/obj/NiSkinData.h"
#include "../include/obj/NiTextureProperty.h"
#include "../include/gen/SkinWeight.h"
#include "../include/obj/NiSkinPartition.h"
#include "../include/gen/BodyPartList.h"
#include "../include/obj/BSShaderTextureSet.h"
#include "../include/obj/BSLightingShaderProperty.h"
#include "../include/obj/NiAlphaProperty.h"

#include <stdlib.h>
#include <array>
#include <obj/BSTriShape.h>
#include <obj/BSSkin__Instance.h>
#include <obj/BSSubIndexTriShape.h>
#include <obj/BSSkin__BoneData.h>


using namespace Niflib;

//Wrape these in the Niflib namespace so they don't polute the Class View
namespace Niflib
{
	struct VertNorm
	{
		Vector3 position;
		Vector3 normal;
		map<NiNodeRef, float> weights;

		VertNorm()
		{
		}

		~VertNorm()
		{
		}

		VertNorm(const VertNorm& n)
		{
			*this = n;
		}

		VertNorm& operator=(const VertNorm& n)
		{
			position = n.position;
			normal = n.normal;
			weights = n.weights;
			return *this;
		}

		bool operator==(const VertNorm& n)
		{
			if (abs(position.x - n.position.x) > 0.001 || abs(position.y - n.position.y) > 0.001 || abs(position.z - n.position.z) > 0.001)
			{
				return false;
			}
			if (abs(normal.x - n.normal.x) > 0.001 || abs(normal.y - n.normal.y) > 0.001 || abs(normal.z - n.normal.z) > 0.001)
			{
				return false;
			}
			//if ( weights != n.weights ) {
			//	return false;
			//}

			return true;
		}
	};


	struct CompoundVertex
	{
		Vector3 position;
		Vector3 normal;
		Color4 color;
		map<TexType, TexCoord> texCoords;
		map<NiNodeRef, float> weights;

		CompoundVertex()
		{
		}

		~CompoundVertex()
		{
		}

		CompoundVertex(const CompoundVertex& n)
		{
			*this = n;
		}

		CompoundVertex& operator=(const CompoundVertex& n)
		{
			position = n.position;
			normal = n.normal;
			color = n.color;
			texCoords = n.texCoords;
			weights = n.weights;
			return *this;
		}

		bool operator==(const CompoundVertex& n)
		{
			if (position != n.position)
			{
				return false;
			}
			if (normal != n.normal)
			{
				return false;
			}
			if (color != n.color)
			{
				return false;
			}
			if (texCoords != n.texCoords)
			{
				return false;
			}
			if (weights != n.weights)
			{
				return false;
			}

			return true;
		}
	};

	struct MergeLookUp
	{
		unsigned int vertIndex;
		unsigned int normIndex;
		unsigned int colorIndex;
		map<unsigned int, unsigned int> uvIndices; //TexCoordSet Index, TexCoord Index
	};
} //End namespace

void BSComplexShape::SetName(const string& n)
{
	name = n;
}

void BSComplexShape::SetVertices(const vector<WeightedVertex>& n)
{
	vertices = n;
}

void BSComplexShape::SetColors(const vector<Color4>& n)
{
	colors = n;
}

void BSComplexShape::SetNormals(const vector<Vector3>& n)
{
	normals = n;
}

void BSComplexShape::SetFaces(const vector<ComplexFace>& n)
{
	faces = n;
}

void BSComplexShape::SetPropGroups(const vector<vector<Ref<NiProperty>>>& n)
{
	propGroups = n;
}

void BSComplexShape::SetSkinInfluences(const vector<Ref<NiNode>>& n)
{
	skinInfluences = n;
}

string BSComplexShape::GetName() const
{
	return name;
}

vector<WeightedVertex> BSComplexShape::GetVertices() const
{
	return vertices;
}

vector<Color4> BSComplexShape::GetColors() const
{
	return colors;
}

vector<Vector3> BSComplexShape::GetNormals() const
{
	return normals;
}

vector<ComplexFace> BSComplexShape::GetFaces() const
{
	return faces;
}

vector<vector<Ref<NiProperty>>> BSComplexShape::GetPropGroups() const
{
	return propGroups;
}

vector<Ref<NiNode>> BSComplexShape::GetSkinInfluences() const
{
	return skinInfluences;
}

vector<Segment> BSComplexShape::GetSegments() const
{
	return segments;
}

void BSComplexShape::SetSegments(const vector<Segment>& s)
{
	segments = s;
}

vector<TexCoord> BSComplexShape::GetTexCoordSet() const
{
	return texCoordSet;
}

void BSComplexShape::SetTexCoordSet(vector<TexCoord> set)
{
	texCoordSet = set;
}

void BSComplexShape::Clear()
{
	vertices.clear();
	colors.clear();
	normals.clear();
	faces.clear();
	propGroups.clear();
	skinInfluences.clear();
	name.clear();
}

void BSComplexShape::Merge(NiAVObject* root)
{
	if (root == NULL)
	{
		throw runtime_error("Called ComplexShape::Merge with a null root reference.");
	}

	vector<BSTriShapeRef> shapes;

	//Determine root type
	if (root->IsDerivedType(BSTriShape::TYPE))
	{
		//The function was called on a single shape.
		//Add it to the list
		shapes.push_back(DynamicCast<BSTriShape>(root));
	}
	else if (root->IsDerivedType(NiNode::TYPE))
	{
		//The function was called on a NiNode.  Search for
		//shape children
		NiNodeRef nodeRoot = DynamicCast<NiNode>(root);
		vector<NiAVObjectRef> children = nodeRoot->GetChildren();
		for (unsigned int child = 0; child < children.size(); ++child)
		{
			if (children[child]->IsDerivedType(BSTriShape::TYPE))
			{
				shapes.push_back(DynamicCast<BSTriShape>(children[child]));
			}
		}

		if (shapes.size() == 0)
		{
			throw runtime_error("The NiNode passed to ComplexShape::Merge has no shape children.");
		}
	}
	else
	{
		throw runtime_error(" The ComplexShape::Merge function requies either a NiNode or a NiTriBasedGeom AVObject.");
	}

	//The vector of VertNorm struts allows us to to refuse
	//to merge vertices that have different normals.
	vector<VertNorm> vns;

	//Clear all existing data
	Clear();

	//Merge in data from each shape
	bool has_any_verts = false;
	bool has_any_norms = false;
	propGroups.resize(shapes.size());
	unsigned int prop_group_index = 0;
	for (int shape_index = 0; shape_index < shapes.size(); shape_index++)
	{
		BSTriShapeRef bs_tri_shape = shapes[shape_index];

		vector<NiPropertyRef> current_property_group = bs_tri_shape->GetProperties();

		//Special code to handle the Bethesda Skyrim properties
		NiPropertyRef property = bs_tri_shape->GetBSProperty(0);
		if (property != nullptr)
		{
			current_property_group.push_back(property);
			property = bs_tri_shape->GetBSProperty(1);
			if (property != nullptr)
			{
				current_property_group.push_back(property);
			}
		}

		//Get properties of this shape
		propGroups[prop_group_index] = current_property_group;

		vector<Color4> shapeColors;
		vector<Vector3> shapeNorms;
		vector<Vector3> shapeVerts = bs_tri_shape->GetVertices();
		vector<TexCoord> shapeUV = bs_tri_shape->GetUVSet();
		vector<Triangle> shapeTris = bs_tri_shape->GetTriangles();
		vector<MergeLookUp> merged_vertex_indexes(bs_tri_shape->GetVertexCount());

		//Vertices and normals
		if (shapeVerts.size() != 0)
		{
			has_any_verts = true;
		}

		if (bs_tri_shape->HasNormals())
		{
			shapeNorms = bs_tri_shape->GetNormals();

			for (unsigned int v = 0; v < shapeVerts.size(); ++v)
			{
				VertNorm newVert;

				newVert.position = shapeVerts[v];
				newVert.normal = shapeNorms[v];

				//Search for matching vert/norm
				bool match_found = false;
				for (unsigned int vn_index = 0; vn_index < vns.size(); ++vn_index)
				{
					if (vns[vn_index] == newVert)
					{
						//Match found, use existing index
						merged_vertex_indexes[v].vertIndex = vn_index;
						if (shapeNorms.size() != 0)
						{
							merged_vertex_indexes[v].normIndex = vn_index;
						}
						match_found = true;
						//Stop searching
						break;
					}
				}

				if (match_found == false)
				{
					//No match found, add this vert/norm to the list
					vns.push_back(newVert);
					//Record new index
					merged_vertex_indexes[v].vertIndex = (unsigned int)(vns.size()) - 1;
					if (shapeNorms.size() != 0)
					{
						merged_vertex_indexes[v].normIndex = (unsigned int)(vns.size()) - 1;
					}
				}
			}
		}

		//Colors
		if (bs_tri_shape->HasColors())
		{
			shapeColors = bs_tri_shape->GetColors();

			for (unsigned int c = 0; c < shapeColors.size(); ++c)
			{
				Color4 newColor;

				newColor = shapeColors[c];

				//Search for matching color
				bool match_found = false;
				for (unsigned int c_index = 0; c_index < colors.size(); ++c_index)
				{
					if (colors[c_index].r == newColor.r && colors[c_index].g == newColor.g && colors[c_index].b == newColor.b && colors[c_index].a == newColor.a)
					{
						//Match found, use existing index
						merged_vertex_indexes[c].colorIndex = c_index;
						match_found = true;
						//Stop searching
						break;
					}
				}

				if (match_found == false)
				{
					//No match found, add this color to the list
					colors.push_back(newColor);
					//Record new index
					merged_vertex_indexes[c].colorIndex = (unsigned int)(colors.size()) - 1;
				}
			}
		}

		BSShaderTextureSetRef bs_shader_texture_set = nullptr;
		NiPropertyRef niProp = bs_tri_shape->GetBSProperty(0);
		if (niProp != nullptr && niProp->GetType().IsSameType(BSLightingShaderProperty::TYPE))
		{
			BSLightingShaderPropertyRef bs_shader = DynamicCast<BSLightingShaderProperty>(niProp);
			if (bs_shader->GetTextureSet() != nullptr)
			{
				bs_shader_texture_set = bs_shader->GetTextureSet();
			}
		}

		niProp = bs_tri_shape->GetBSProperty(1);
		if (niProp != nullptr && niProp->GetType().IsSameType(BSLightingShaderProperty::TYPE))
		{
			BSLightingShaderPropertyRef bs_shader = DynamicCast<BSLightingShaderProperty>(niProp);
			if (bs_shader->GetTextureSet() != nullptr)
			{
				bs_shader_texture_set = bs_shader->GetTextureSet();
			}
		}

		if (bs_shader_texture_set != nullptr)
		{
			for (unsigned int v = 0; v < shapeUV.size(); ++v)
			{
				TexCoord newCoord;

				newCoord = shapeUV[v];

				//Search for matching texture coordinate
				bool match_found = false;
				for (unsigned int tc_index = 0; tc_index < texCoordSet.size(); ++tc_index)
				{
					if (texCoordSet[tc_index] == newCoord)
					{
						//Match found, use existing index
						merged_vertex_indexes[v].uvIndices[0] = tc_index;
						match_found = true;
						//Stop searching
						break;
					}
				}

				//Done with loop, check if match was found
				if (match_found == false)
				{
					//No match found, add this texture coordinate to the list
					texCoordSet.push_back(newCoord);
					//Record new index
					merged_vertex_indexes[v].uvIndices[0] = (unsigned int)texCoordSet.size() - 1;
				}
			}
		}

		//Use look up table to build list of faces
		for (unsigned int t = 0; t < shapeTris.size(); ++t)
		{
			ComplexFace newFace;
			newFace.propGroupIndex = prop_group_index;
			newFace.points.resize(3);
			const Triangle& tri = shapeTris[t];
			for (unsigned int p = 0; p < 3; ++p)
			{
				if (shapeVerts.size() != 0)
				{
					newFace.points[p].vertexIndex = merged_vertex_indexes[tri[p]].vertIndex;
				}
				if (shapeNorms.size() != 0)
				{
					newFace.points[p].normalIndex = merged_vertex_indexes[tri[p]].normIndex;
				}
				if (shapeColors.size() != 0)
				{
					newFace.points[p].colorIndex = merged_vertex_indexes[tri[p]].colorIndex;
				}
				for (map<unsigned int, unsigned int>::iterator set = merged_vertex_indexes[tri[p]].uvIndices.begin(); set != merged_vertex_indexes[tri[p]].uvIndices.end(); ++set)
				{
					TexCoordIndex tci;
					tci.texCoordSetIndex = set->first;
					tci.texCoordIndex = set->second;
					newFace.points[p].texCoordIndices.push_back(tci);
				}
			}
			faces.push_back(newFace);
		}


		if (bs_tri_shape->HasSkin())
		{
			BSSkin__InstanceRef skinInst = DynamicCast<BSSkin__Instance>(bs_tri_shape->GetSkin());
			vector<BSVertexData> bs_vertex_datas = bs_tri_shape->GetVertexData();
			vector<NiNodeRef> shapeBones = skinInst->GetBones();

			for (int vertex_index = 0; vertex_index < bs_vertex_datas.size(); vertex_index++)
			{
				int merged_vertex_index = merged_vertex_indexes[vertex_index].vertIndex;

				for (int influence_index = 0; influence_index < 4; influence_index++)
				{
					NiNodeRef boneRef = shapeBones[bs_vertex_datas[vertex_index].GetBoneIndex(influence_index)];
					float weight = bs_vertex_datas[vertex_index].GetBoneWeight(influence_index);
					vns[merged_vertex_index].weights[boneRef] = weight;
				}
			}
		}

		if (bs_tri_shape->IsDerivedType(BSSubIndexTriShape::TYPE))
		{
			BSSubIndexTriShapeRef bs_sub_index_tri_shape = DynamicCast<BSSubIndexTriShape>(bs_tri_shape);
			const vector<BSSITSSegment> bssits_segments = bs_sub_index_tri_shape->GetSegments();

			unsigned int previous_polygon_offset = 0;

			if (segments.size() > 0)
			{
				previous_polygon_offset = segments[segments.size() - 1].polygonCount + segments[segments.size() - 1].polygonOffset;
			}

			for (int segment_index = 0; segment_index < bssits_segments.size(); segment_index++)
			{
				Segment current_segment;
				current_segment.polygonCount = bssits_segments[segment_index].triangleCount;
				current_segment.polygonOffset = bssits_segments[segment_index].triangleOffset / 3 + previous_polygon_offset;


				for (int sub_segment_index = 0; sub_segment_index < bssits_segments[segment_index].subIndexRecord.size(); sub_segment_index++)
				{
					SubSegment current_subsegment;
					current_subsegment.polygonOffset = bssits_segments[segment_index].subIndexRecord[sub_segment_index].triangleOffset / 3 + previous_polygon_offset;
					current_subsegment.polygonCount = bssits_segments[segment_index].subIndexRecord[sub_segment_index].triangleCount;

					current_segment.subSegments.push_back(current_subsegment);
				}

				segments.push_back(current_segment);
			}
		}

		//Next Shape
		++prop_group_index;
	}

	//Finished with all shapes.  Build up a list of influences
	map<NiNodeRef, unsigned int> boneLookUp;
	for (unsigned int v = 0; v < vns.size(); ++v)
	{
		for (map<NiNodeRef, float>::iterator w = vns[v].weights.begin(); w != vns[v].weights.end(); ++w)
		{
			boneLookUp[w->first] = 0; //will change later
		}
	}

	skinInfluences.resize(boneLookUp.size());
	unsigned int si_index = 0;
	for (map<NiNodeRef, unsigned int>::iterator si = boneLookUp.begin(); si != boneLookUp.end(); ++si)
	{
		si->second = si_index;
		skinInfluences[si_index] = si->first;
		++si_index;
	}

	//Copy vns data to vertices and normals
	if (has_any_verts)
	{
		vertices.resize(vns.size());
	}
	if (has_any_norms)
	{
		normals.resize(vns.size());
	}

	for (unsigned int v = 0; v < vns.size(); ++v)
	{
		if (has_any_verts)
		{
			vertices[v].position = vns[v].position;
			vertices[v].weights.resize(vns[v].weights.size());
			unsigned int weight_index = 0;
			for (map<NiNodeRef, float>::iterator w = vns[v].weights.begin(); w != vns[v].weights.end(); ++w)
			{
				vertices[v].weights[weight_index].influenceIndex = boneLookUp[w->first];
				vertices[v].weights[weight_index].weight = w->second;
				++weight_index;
			}
		}
		if (has_any_norms)
		{
			normals[v] = vns[v].normal;
		}
	}
	//Done Merging
}

Ref<NiAVObject> BSComplexShape::Split(NiNode* parent, Matrix44& transform, int max_bones_per_partition, bool tangent_space, float min_vertex_weight) const
{
	//Make sure parent is not NULL
	if (parent == NULL)
	{
		throw runtime_error("A parent is necessary to split a complex shape.");
	}

	//There will be one NiTriShape per property group
	//with a minimum of 1
	unsigned int num_shapes = (unsigned int)(propGroups.size());
	if (num_shapes == 0)
	{
		num_shapes = 1;
	}

	vector<BSTriShapeRef> shapes(num_shapes);

	//Loop through each shape slot and create a NiTriShape
	for (unsigned int shape_num = 0; shape_num < shapes.size(); ++shape_num)
	{
		if (segments.size() > 0)
		{
			shapes[shape_num] = new BSSubIndexTriShape;
		}
		else 
		{
			shapes[shape_num] = new BSTriShape;
		}
	}

	NiAVObjectRef root;

	//If there is just one shape, return it.  Otherwise
	//create a node, parent all shapes to it, and return
	// that
	if (shapes.size() == 1)
	{
		//One shape
		shapes[0]->SetName(name);
		root = StaticCast<NiAVObject>(shapes[0]);
	}
	else
	{
		//Multiple shapes
		NiNodeRef niNode = new NiNode;
		niNode->SetName(name);
		for (unsigned int i = 0; i < shapes.size(); ++i)
		{
			niNode->AddChild(StaticCast<NiAVObject>(shapes[i]));

			//Set Shape Name
			stringstream shapeName;
			shapeName << name << " " << i;
			shapes[i]->SetName(shapeName.str());
		}
		root = StaticCast<NiAVObject>(niNode);
	}

	parent->AddChild(root);

	//Set transform of root
	root->SetLocalTransform(transform);

	//Create NiTriShapeData and fill it out with all data that is relevant
	//to this shape based on the material.
	for (unsigned int shape_index = 0; shape_index < shapes.size(); ++shape_index)
	{
		//Create a list of CompoundVertex to make it easier to
		//test for the need to clone a vertex
		vector<CompoundVertex> compVerts;

		//List of triangles for the final shape to use
		vector<Triangle> shapeTriangles;

		//since we might have dismember partitions the face index is also required
		int current_face_index = 0;

		//Loop through all faces, and all points on each face
		//to set the vertices in the CompoundVertex list
		for (vector<ComplexFace>::const_iterator face = faces.begin(); face != faces.end(); ++face)
		{
			//Ignore faces with less than 3 vertices
			if (face->points.size() < 3)
			{
				continue;
			}

			//Skip this face if the material does not relate to this shape
			if (face->propGroupIndex != shape_index)
			{
				continue;
			}

			vector<unsigned short> shapeFacePoints;
			for (vector<ComplexPoint>::const_iterator point = face->points.begin(); point != face->points.end(); ++point)
			{
				//--Set up Compound vertex--//
				CompoundVertex cv;

				if (vertices.size() > 0)
				{
					const WeightedVertex& wv = vertices[point->vertexIndex];
					cv.position = wv.position;

					if (skinInfluences.size() > 0)
					{
						for (unsigned int i = 0; i < wv.weights.size(); ++i)
						{
							const SkinInfluence& inf = wv.weights[i];

							cv.weights[skinInfluences[inf.influenceIndex]] = inf.weight;
						}
					}
				}

				if (normals.size() > 0)
				{
					cv.normal = normals[point->normalIndex];
				}

				if (colors.size() > 0)
				{
					cv.color = colors[point->colorIndex];
				}

				if (texCoordSet.size() > 0) 
				{
					cv.texCoords[BASE_MAP] = texCoordSet[point->texCoordIndices[0].texCoordIndex];
				}

				bool found_match = false;
				//Search for an identical vertex in the list
				for (unsigned short cv_index = 0; cv_index < compVerts.size(); ++cv_index)
				{
					if (compVerts[cv_index] == cv)
					{
						//We found a match, push its index into the face list
						found_match = true;
						shapeFacePoints.push_back(cv_index);
						break;
					}
				}

				//If no match was found, append this vertex to the list
				if (found_match == false)
				{
					compVerts.push_back(cv);
					//put the new vertex into the face point list
					shapeFacePoints.push_back((unsigned int)(compVerts.size()) - 1);
				}

				//Next Point
			}


			//Starting from vertex 0, create a fan of triangles to fill
			//in non-triangle polygons
			Triangle new_face;
			for (unsigned int i = 0; i < shapeFacePoints.size() - 2; ++i)
			{
				new_face[0] = shapeFacePoints[0];
				new_face[1] = shapeFacePoints[i + 1];
				new_face[2] = shapeFacePoints[i + 2];

				//Push the face into the face list
				shapeTriangles.push_back(new_face);
			}

			//Next Face

			current_face_index++;
		}

		//Attatch properties if any
		//Check if the properties are skyrim specific in which case attach them in the 2 special slots called bs_properties
		if (propGroups.size() > 0)
		{
			BSLightingShaderPropertyRef shader_property = NULL;

			for (vector<NiPropertyRef>::const_iterator prop = propGroups[shape_index].begin(); prop != propGroups[shape_index].end(); ++prop)
			{
				NiPropertyRef current_property = *prop;
				if (current_property->GetType().IsSameType(BSLightingShaderProperty::TYPE))
				{
					shader_property = DynamicCast<BSLightingShaderProperty>(current_property);
					break;
				}
			}

			if (shader_property == NULL)
			{
				for (vector<NiPropertyRef>::const_iterator prop = propGroups[shape_index].begin(); prop != propGroups[shape_index].end(); ++prop)
				{
					shapes[shape_index]->AddProperty(*prop);
				}
			}
			else
			{
				NiAlphaPropertyRef alpha_property = NULL;
				for (vector<NiPropertyRef>::const_iterator prop = propGroups[shape_index].begin(); prop != propGroups[shape_index].end(); ++prop)
				{
					if ((*prop)->GetType().IsSameType(NiAlphaProperty::TYPE))
					{
						alpha_property = DynamicCast<NiAlphaProperty>((*prop));
					}
				}
				shapes[shape_index]->SetBSProperty(0, DynamicCast<NiProperty>(shader_property));
				shapes[shape_index]->SetBSProperty(1, DynamicCast<NiProperty>(alpha_property));
			}
		}
		//--Set Shape Data--//

		//lists to hold data
		vector<Vector3> shapeVerts(compVerts.size());
		vector<Vector3> shapeNorms(compVerts.size());
		vector<Color4> shapeColors(compVerts.size());
		vector<TexCoord> tex_coords(compVerts.size());
		map<NiNodeRef, vector<SkinWeight>> shapeWeights;
		map<NiNodeRef, int> bone_used_indices;
		vector<NiNodeRef> bones_used;

		//Search for a NiTexturingProperty to build list of
		//texture coordinates sets to create
		NiPropertyRef niProp = shapes[shape_index]->GetPropertyByType(BSLightingShaderProperty::TYPE);
		NiTexturingPropertyRef niTexProp;

		//Loop through all compound vertices, adding the data
		//to the correct arrays.
		unsigned int vert_index = 0;
		for (vector<CompoundVertex>::iterator cv = compVerts.begin(); cv != compVerts.end(); ++cv)
		{
			shapeVerts[vert_index] = cv->position;
			shapeColors[vert_index] = cv->color;
			shapeNorms[vert_index] = cv->normal;
			shapeNorms[vert_index] = cv->normal;
			tex_coords[vert_index] = cv->texCoords[BASE_MAP];
	
			SkinWeight sk;
			for (map<NiNodeRef, float>::iterator wt = cv->weights.begin(); wt != cv->weights.end(); ++wt)
			{
				//Only record influences that make a noticable contribution
				if (wt->second > min_vertex_weight)
				{
					sk.index = vert_index;
					sk.weight = wt->second;
					if (shapeWeights.find(wt->first) == shapeWeights.end())
					{
						shapeWeights[wt->first] = vector<SkinWeight>();
					}
					shapeWeights[wt->first].push_back(sk);
				}
			}

			++vert_index;
		}

		shapes[shape_index]->SetTriangles(shapeTriangles);

		//Finally, set the data into the BSTriShape
		if (vertices.size() > 0)
		{
			vector<BSVertexData> vertex_datas;

			for (int vertex_index = 0; vertex_index < shapeVerts.size(); vertex_index++)
			{
				BSVertexData vertex_data;
				vertex_data.SetVertex(shapeVerts[vertex_index]);
				vertex_data.SetNormal(shapeNorms[vertex_index]);
				vertex_data.SetVertexColor(shapeColors[vertex_index]);
				vertex_data.SetUV(tex_coords[vertex_index]);

				vertex_datas.push_back(vertex_data);
			}

			shapes[shape_index]->SetVertexData(vertex_datas);
		}

		if (shapeWeights.size() > 0)
		{
			shapes[shape_index]->GenSkinData(shapeWeights);
		}

		shapes[shape_index]->SetVertexFlags(tex_coords.size() > 0, vertices.size() > 0, false, false, true, false);

		//if (normals.size() > 0)
		//{
		//	niData->SetNormals(shapeNorms);
		//}
		//if (colors.size() > 0)
		//{
		//	niData->SetVertexColors(shapeColors);
		//}

		////If there are any skin influences, bind the skin
		//if (shapeWeights.size() > 0)
		//{
		//	vector<NiNodeRef> shapeInfluences;
		//	for (map<NiNodeRef, vector<SkinWeight>>::iterator inf = shapeWeights.begin(); inf != shapeWeights.end(); ++inf)
		//	{
		//		shapeInfluences.push_back(inf->first);
		//	}

		//	shapes[shape_num]->BindSkin(shapeInfluences);

		//	for (unsigned int inf = 0; inf < shapeInfluences.size(); ++inf)
		//	{
		//		shapes[shape_num]->SetBoneWeights(inf, shapeWeights[shapeInfluences[inf]]);
		//	}

		//	shapes[shape_num]->NormalizeSkinWeights();


		//	shapes[shape_num]->GenHardwareSkinInfo(max_bones_per_partition, 4, stripify);
		//}

		////If tangent space was requested, generate it
		//if (tangent_space)
		//{
		//	if (tspace_flags == 0)
		//	{
		//		shapes[shape_num]->UpdateTangentSpace();
		//	}
		//	else
		//	{
		//		if (shapes[shape_num]->GetData() != NULL)
		//		{
		//			shapes[shape_num]->GetData()->SetUVSetCount(1);
		//			shapes[shape_num]->GetData()->SetTspaceFlag(tspace_flags);
		//			shapes[shape_num]->UpdateTangentSpace(1);
		//		}
		//	}
		//}

		//Next Shape
	}

	return root;
}
