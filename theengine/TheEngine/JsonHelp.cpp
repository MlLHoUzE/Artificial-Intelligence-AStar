#include "JsonHelp.h"
#include <iostream>
#include <fstream>

namespace JsonHelp
{
	bool Load(const char* fileName, Json::Value& jsonOut)
	{
		std::string errors;
		if (Load(fileName, jsonOut, errors))
		{
			return true;
		}
		else
		{
			std::cout << "WARNING: json file '" << fileName << "' failed to load." << std::endl;
			std::cout << "\t" << "Errors: " << errors << std::endl;
			return false;
		}
	}
	bool Load(const char* fileName, Json::Value& jsonOut, std::string& errors)
	{
		std::ifstream jsonFile(fileName, std::ifstream::binary);
		Json::CharReaderBuilder charReaderBuilder;
		std::string errs;
		return Json::parseFromStream(charReaderBuilder, jsonFile, &jsonOut, &errors);
	}
	bool Load(const std::string& fileName, Json::Value& jsonOut)
	{
		return Load(fileName.c_str(), jsonOut);
	}
	bool Load(const std::string& fileName, Json::Value& jsonOut, std::string& errors)
	{
		return Load(fileName.c_str(), jsonOut, errors);
	}

	bool Set(Json::Value& json, glm::vec2& vec)
	{
		if (!ValidObject(json)) return false;
		Json::Value x = json["x"];
		Json::Value y = json["y"];
		if (!ValidNumeric(x, y)) return false;
		vec.x = x.asFloat();
		vec.y = y.asFloat();
		return true;
	}
	bool Set(Json::Value& json, float& value)
	{
		if (!ValidObject(json)) return false;
		Json::Value x = json["Value"];
		value = x.asFloat();
		return true;
	}
	bool Set(Json::Value& json, int& value)
	{
		if (!ValidObject(json)) return false;
		Json::Value x = json["Value"];
		value = x.asInt();
		return true;
	}
	bool Set(Json::Value& json, glm::vec3& vec)
	{
		if (!ValidObject(json)) return false;
		Json::Value x = json["x"];
		Json::Value y = json["y"];
		Json::Value z = json["z"];
		if (!ValidNumeric(x, y, z)) return false;
		vec.x = x.asFloat();
		vec.y = y.asFloat();
		vec.z = z.asFloat();
		return true;
	}
	bool Set(Json::Value& json, glm::vec4& vec)
	{
		if (!ValidObject(json)) return false;
		Json::Value x = json["x"];
		Json::Value y = json["y"];
		Json::Value z = json["z"];
		Json::Value w = json["w"];
		if (!ValidNumeric(x, y, z, w)) return false;
		vec.x = x.asFloat();
		vec.y = y.asFloat();
		vec.z = z.asFloat();
		vec.w = w.asFloat();
		return true;
	}
	bool Set(Json::Value& json, glm::quat& quat)
	{
		if (!ValidObject(json)) return false;
		Json::Value x = json["x"];
		Json::Value y = json["y"];
		Json::Value z = json["z"];
		Json::Value w = json["w"];
		if (!ValidNumeric(x, y, z)) return false;
		glm::quat outQuat = glm::quat(glm::vec3(x.asFloat(), y.asFloat(), z.asFloat()));
		quat = outQuat;
		/*quat.x = x.asFloat();
		quat.y = y.asFloat();
		quat.z = z.asFloat();
		quat.w = w.asFloat();*/
		return true;
	}
	bool Set(Json::Value& json, glm::vec4& vec, float defaultW)
	{
		if (!ValidObject(json)) return false;
		Json::Value x = json["x"];
		Json::Value y = json["y"];
		Json::Value z = json["z"];
		Json::Value w = json["w"];
		if (!ValidNumeric(x, y, z)) return false;
		vec.x = x.asFloat();
		vec.y = y.asFloat();
		vec.z = z.asFloat();
		if (ValidNumeric(w)) vec.w = w.asFloat();
		else vec.w = defaultW;
		return true;
	}
	bool Set(Json::Value& json, sRenderingInfo& comp)
	{
		if (!ValidObject(json)) return false;
		// name the mesh! that's really the only important thing here
		Json::Value meshName = json["meshName"];
		if (!ValidString(meshName)) return false;
		comp.meshName = meshName.asString();
		Json::Value textureName = json["textureName"];
		if (!ValidString(textureName)) return false;
		comp.texture00Name = textureName.asString();
		Json::Value scale = json["scale"];
		comp.scale = scale.asFloat();  // dun curr if it's not there
		Json::Value colour = json["color"];
		Set(colour, comp.color, 1.f); // hey that was useful!
		return true;
	}
	bool Set(Json::Value& json, sPhysicsInfo& comp)
	{
		if (!ValidObject(json)) return false;
		// position is the only absolutely necessary thing for me
		Json::Value position = json["position"];
		if (!Set(position, comp.position)) return false;
		Json::Value rotation = json["orientation"];
		Set(rotation, comp.orientation);
		Json::Value speed = json["speed"];
		comp.speed = speed.asFloat();
		Json::Value angSpeed = json["angularSpeed"];
		comp.angularSpeed = angSpeed.asFloat();
		// I'll assume here that acceleration is never set initially
		return true;
	}
	/*bool Set(Json::Value& json, cAreaInfo& area)
	{
		if (!ValidObject(json)) return false;
		Json::Value maxBounds = json["MaxBounds"];
		Json::Value minBounds = json["MinBounds"];
		return Set(maxBounds, area.Max) && Set(minBounds, area.Min);
	}*/
	bool Set(Json::Value& json, cPlayer& obj)
	{
		if (!ValidObject(json)) return false;
		// let's say physics aren't necesarily required
		Json::Value rendering = json["rendering"];
		sRenderingInfo renderingInfo;
		obj.GetRenderingInfo(renderingInfo);
		Set(rendering, renderingInfo);
		obj.SetRenderingInfo(renderingInfo);
		Json::Value physics = json["physics"];
		sPhysicsInfo physicsInfo;
		obj.GetPhysicsInfo(physicsInfo);
		Set(physics, physicsInfo); // we don't care about the result
		obj.SetPhysicsInfo(physicsInfo);
		
		return true;
	}
	bool Set(Json::Value& json, cCamera& obj)
	{
		if (!ValidObject(json)) return false;
		// let's say physics aren't necesarily required
		Json::Value offset = json["offset"];
		glm::vec3 offsetVec;
		Set(offset, offsetVec); // we don't care about the result
		obj.SetOffset(offsetVec);
		return true;
	}
	bool Set(Json::Value& json, sEntityDesc& obj)
	{
		if (!ValidObject(json)) return false;
		Json::Value entityType = json["entityType"];
		if (!ValidString(entityType))return false;
		obj.typeOfEntity = entityType.asString();
		Json::Value meshName = json["meshName"];
		if (!ValidString(meshName)) return false;
		obj.meshName = meshName.asString();
		Json::Value textureName = json["textureName"];
		if (!ValidString(textureName))return false;
		obj.texture00Name = textureName.asString();
		Json::Value alphaTextureName = json["alphaTextureName"];
		obj.alphaTextureName = alphaTextureName.asString();
		Json::Value textureName2 = json["textureName2"];
		obj.texture01Name = textureName2.asString();
		Json::Value color = json["color"];
		Set(color, obj.color, 1.f);
		Json::Value scale = json["scale"];
		if (!ValidNumeric(scale))return false;
		obj.scale = scale.asFloat();
		Json::Value position = json["position"];
		Set(position, obj.position);
		Json::Value orientation = json["orientation"];
		Set(orientation, obj.orientation);
		//obj.numberOfEnemies = numberToSpawn.asInt();
		//Json::Value minSpeed = json["MinSpeed"];
		//obj.minSpeed = minSpeed.asFloat();
		//Json::Value maxSpeed = json["MaxSpeed"];
		//obj.maxSpeed = maxSpeed.asFloat();

		return true;
	}
}