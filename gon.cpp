// convert_standard_string_to_system_string.cpp
// compile with: /clr
#include "gon.h"
#include <string>
#include <iostream>
using namespace System;
using namespace std;
using namespace System::Runtime::InteropServices;

static const char* string_to_char_array(String^ string)
{
	const char* str = (const char*)(Marshal::StringToHGlobalAnsi(string)).ToPointer();
	return str;
}

String^ string_to_managed_string(std::string str)
{
	return gcnew String(str.c_str());
}

namespace GonWrapper
{
	GonWObject::GonWObject()
	{
		m_Instance = new GonObject();
	}

	GonWObject::GonWObject(GonObject obj)
	{
		m_Instance = new GonObject();
		m_Instance->children_map = obj.children_map;
		m_Instance->children_array = obj.children_array;
		m_Instance->int_data = obj.int_data;
		m_Instance->float_data = obj.float_data;
		m_Instance->bool_data = obj.bool_data;
		m_Instance->string_data = obj.string_data;
		m_Instance->name = obj.name;
		this->Name = string_to_managed_string(obj.name);
		m_Instance->type = obj.type;
	}

	GonWObject^ GonWObject::Load(String^ filename)
	{
		std::string str = string_to_char_array(filename);
		GonObject obj = GonObject::Load(str);
		GonWObject^ res = gcnew GonWObject(obj);
		return res;
	}

	String^ GonWObject::GetString()
	{
		std::string res = m_Instance->String();
		return string_to_managed_string(res);
	}

	const char* GonWObject::GetCharArray()
	{
		return m_Instance->CString();
	}

	int GonWObject::GetInt()
	{
		return m_Instance->Int();
	}

	double GonWObject::GetNumber()
	{
		return m_Instance->Number();
	}

	bool GonWObject::GetBool()
	{
		return m_Instance->Bool();
	}

	String^ GonWObject::GetString(String^ _default)
	{
		std::string str = string_to_char_array(_default);
		std::string res = m_Instance->String(str);
		return string_to_managed_string(res);
	}

	const char* GonWObject::GetCharArray(const char* _default)
	{
		return m_Instance->CString(_default);
	}

	int GonWObject::GetInt(int _default)
	{
		return m_Instance->Int(_default);
	}

	double GonWObject::GetNumber(double _default)
	{
		return m_Instance->Number(_default);
	}

	bool GonWObject::GetBool(bool _default)
	{
		return m_Instance->Bool(_default);
	}

	bool GonWObject::Contains(String^ child)
	{
		std::string str = string_to_char_array(child);
		return m_Instance->Contains(str);
	}

	bool GonWObject::Contains(int child)
	{
		return m_Instance->Contains(child);
	}

	bool GonWObject::Exists()
	{
		return m_Instance->Exists();
	}

	GonWObject^ GonWObject::operator[](String^ child)
	{
		std::string str = string_to_char_array(child);
		return gcnew GonWObject((*m_Instance)[str]);
	}

	GonWObject^ GonWObject::Get(String^ child)
	{
		std::string str = string_to_char_array(child);
		return gcnew GonWObject((*m_Instance)[str]);
	}

	GonWObject^ GonWObject::ChildOrSelf(String^ child)
	{
		std::string str = string_to_char_array(child);
		return gcnew GonWObject(m_Instance->ChildOrSelf(str));
	}

	GonWObject^ GonWObject::operator[](int childindex)
	{
		return gcnew GonWObject((*m_Instance)[childindex]);
	}

	GonWObject^ GonWObject::Get(int childindex)
	{
		return gcnew GonWObject((*m_Instance)[childindex]);
	}

	int GonWObject::Size()
	{
		return m_Instance->Size();
	}

	void GonWObject::Save(String^ outfilename)
	{
		std::string str = string_to_char_array(outfilename);
		m_Instance->Save(str);
	}

	void GonWObject::InsertChild(GonWObject^ other)
	{
		m_Instance->InsertChild(*other->m_Instance);
	}

	void GonWObject::InsertChild(String^ name, GonWObject^ other)
	{
		std::string str = string_to_char_array(name);
		m_Instance->InsertChild(str, *other->m_Instance);
	}

	void GonWObject::Append(GonWObject^ other)
	{
		m_Instance->Append(*other->m_Instance);
	}

	String^ GonWObject::GetFieldTypeAsString()
	{
		switch (m_Instance->type)
		{
		case GonObject::FieldType::ARRAY:
			return "ARRAY";
		case GonObject::FieldType::BOOL:
			return "BOOL";
		case GonObject::FieldType::NULLGON:
			return "NULLGON";
		case GonObject::FieldType::NUMBER:
			return "NUMBER";
		case GonObject::FieldType::OBJECT:
			return "OBJECT";
		case GonObject::FieldType::STRING:
			return "STRING";
		default:
			return "what";
		}
	}

	GonWObject^ GonWObject::FromInt(int value)
	{
		GonObject* obj = new GonObject();
		obj->string_data = string_to_char_array(value.ToString());
		obj->int_data = value;
		obj->type = GonObject::FieldType::NUMBER;
		return gcnew GonWObject(*obj);
	}

	GonWObject^ GonWObject::FromNumber(double value)
	{
		GonObject* obj = new GonObject();
		obj->string_data = string_to_char_array(value.ToString());
		obj->float_data = value;
		obj->type = GonObject::FieldType::NUMBER;
		return gcnew GonWObject(*obj);
	}

	GonWObject^ GonWObject::FromBool(bool value)
	{
		GonObject* obj = new GonObject();
		obj->string_data = string_to_char_array(value.ToString());
		obj->bool_data = value;
		obj->type = GonObject::FieldType::BOOL;
		return gcnew GonWObject(*obj);
	}

	GonWObject^ GonWObject::FromString(String^ value)
	{
		GonObject* obj = new GonObject();
		obj->string_data = string_to_char_array(value);
		obj->type = GonObject::FieldType::STRING;
		return gcnew GonWObject(*obj);
	}

	GonWObject^ GonWObject::MakeEmptyObject()
	{
		GonObject* obj = new GonObject();
		obj->type = GonObject::FieldType::OBJECT;
		return gcnew GonWObject(*obj);
	}

	GonWObject^ GonWObject::MakeEmptyArray()
	{
		GonObject* obj = new GonObject();
		obj->type = GonObject::FieldType::ARRAY;
		return gcnew GonWObject(*obj);
	}
}